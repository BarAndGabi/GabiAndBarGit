#define _CRT_SECURE_NO_WARNINGS

#include "glut.h"
#include <math.h>
#include <stdio.h>
#include <time.h>

const int W = 600;
const int H = 600;
const double PI = 3.14;
const int GSZ = 200;

double ground[GSZ][GSZ] ; // y = f(x,z)
double tmp[GSZ][GSZ];

double angle = 0;
double eyex = 2, eyey = 40, eyez=90;
double dx = 0, dy = 0, dz = 0; // speed in each direction
double dirx, diry, dirz;
double speed=0, angular_speed=0;
double sight_angle = PI;

unsigned char* bmp;
bool isBuilding = false;

void UpdateTerrain1();


void ReadPicture(char* fname)
{
	int size;
	FILE* pf = fopen(fname, "rb");
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;

	fread(&bf, sizeof(bf), 1, pf);
	fread(&bi, sizeof(bi), 1, pf);

	size = bi.biHeight*bi.biWidth * 3;

	bmp = (unsigned char*)malloc(size);

	fread(bmp, 1, size, pf);

	fclose(pf);
}

void init()
{
	int i, j,k;
//	char name[20] = "flower.bmp";
	glClearColor(0.3, 0.6, 0.8, 0);// color of window background

	srand(time(0));

	glEnable(GL_DEPTH_TEST); // uses Z-buffer
/*
	for(i=0;i<GSZ;i++)
		for (j = 0; j < GSZ; j++)
		{
			ground[i][j] = 2*sin(i/10.0)+ 2 * sin(j / 10.0);
		}
*/
/*	for (int counter = 0; counter < 10000; counter++)
	{
		UpdateTerrain1();
	}
	*/
//	ReadPicture(name);

}

void SetColor(double h)
{
	double r, g, b;
//	r = fabs(h) / 4;
//	g = fabs(h) / 4;
//	b = fabs(h) / 4;
	if (fabs(h) < 0.2) // sand
	{
		r = 0.9;
		g = 0.8;
		b = 0.7;
	}
	else if (fabs(h) < 4) // grass
	{
		r = fabs(h) / 10;
		g = 0.3+ fabs(h) / 7;
		b = 0;
	}
	else if (fabs(h) < 7) // stones
	{
		r = fabs(h) / 10;
		g = fabs(h) / 12;
		b = fabs(h) / 15;
	}
	else // snow
	{
		r = fabs(h) / 10;
		g = fabs(h) / 10;
		b = fabs(h) / 9;
	}
	glColor3d(r, g, b);
}


void DrawFloor()
{
	int i, j;
	glColor3d(0,0,0);


	// sets height by green channel:   ground[i][j][1]
	for(i=1;i<GSZ;i++)
		for (j = 1; j < GSZ; j++)
		{
			glBegin(GL_POLYGON);//GL_LINE_LOOP);//
			SetColor(ground[i][j]);
			glVertex3d(j-GSZ/2, ground[i][j], i - GSZ / 2);
			SetColor(ground[i][j-1]);
			glVertex3d(j - 1 - GSZ / 2, ground[i][j-1], i - GSZ / 2);
			SetColor(ground[i-1][j-1]);
			glVertex3d(j - 1 - GSZ / 2, ground[i-1][j-1], i-1 - GSZ / 2);
			SetColor(ground[i-1][j]);
			glVertex3d(j - GSZ / 2, ground[i-1][j], i - 1 - GSZ / 2);
			glEnd();
		}
	glLineWidth(1);
	// transparent water

	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4d(0, 0.2, 0.6,0.7);
	glBegin(GL_POLYGON);
	glVertex3d(-GSZ / 2, -0.1, -GSZ / 2);
	glVertex3d(GSZ / 2, -0.1, -GSZ / 2);
	glVertex3d(GSZ / 2, -0.1, GSZ / 2);
	glVertex3d(-GSZ / 2, -0.1, GSZ / 2);

	glEnd();

	glDisable(GL_BLEND);

}

void Smooth()
{
	int i, j;

	for(i=1;i<GSZ-1;i++)
		for (j = 1; j < GSZ - 1; j++)
		{
			// the mask is of size 3x3
			tmp[i][j] = (ground[i-1][j-1]+ 2*ground[i - 1][j]+ ground[i - 1][j + 1]+
				2*ground[i ][j - 1]+ 4*ground[i ][j] + 2*ground[i ][j + 1]+
				ground[i + 1][j - 1]+ 2*ground[i + 1][j] + ground[i + 1][j + 1] ) / 16.0;
		}

	for (i = 1; i < GSZ - 1; i++)
		for (j = 1; j < GSZ - 1; j++)
			ground[i][j]= tmp[i][j];
}

void HPF()
{
	int i, j;
	int channel = 1; // green

	for (i = 1; i < GSZ - 1; i++)
		for (j = 1; j < GSZ - 1; j++)
		{
			// the mask is of size 3x3
			tmp[i][j] = (-ground[i - 1][j - 1]- 2 * ground[i - 1][j] + -ground[i - 1][j + 1]-
				2 * ground[i][j - 1] + 12 * ground[i][j] - 2 * ground[i][j + 1] 
				-ground[i + 1][j - 1] - 2 * ground[i + 1][j] - ground[i + 1][j + 1])/4.0 ;
		}

	for (i = 1; i < GSZ - 1; i++)
		for (j = 1; j < GSZ - 1; j++)
			ground[i][j] = fabs(tmp[i][j]);
}



void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clean frame buffer and z-buffer

	glMatrixMode(GL_PROJECTION); // here we define working matrices of PROJECTIONS

	glLoadIdentity(); // start transformations here
	glFrustum(-1, 1, -1, 1, 0.7, 350);

	// look to variable direction
	gluLookAt(eyex, eyey, eyez, 
		eyex+dirx, eyey - 1, eyez+dirz,  // this is the direction
		0, 1, 0);
	// look to the specified direction
//	gluLookAt(eyex, eyey, eyez, eyex, eyey-2, eyez-5, 0, 1, 0);// eye, center and UP
	// look at specified point
//	gluLookAt(eyex, eyey, eyez, 0, 0, 0, 0, 1, 0);// eye, center and UP

	glMatrixMode(GL_MODELVIEW);// here we switch to working matrices of objects

	glPushMatrix();
//	glRotated(angle, 0, 1, 0);
	// 3d shape

	DrawFloor();


	glPopMatrix();

	glutSwapBuffers(); // show all
}

void 	UpdateTerrain1()
{
	int i, j;
	double delta = 0.1;

	if (rand() % 2 == 0) delta = -delta;

	for (int counter = 0; counter < 100; counter++)
	{
		i = rand() % GSZ;
		j = rand() % GSZ;

		ground[i][j] += delta;
	}
}

void 	UpdateTerrain2()
{
	int x1, y1, x2, y2;
	double a, b;
	int i, j;
	double delta = 0.1;

	if (rand() % 2 == 0)
		delta = -delta;
	
	x1 = rand() % GSZ;
	y1 = rand() % GSZ;
	x2 = rand() % GSZ;
	y2 = rand() % GSZ;
	if (x1 != x2)
	{
		a = (y2 - y1) / double(x2 - x1);
		b = y1 - a * x1;
		for (i = 0; i < GSZ; i++)
			for (j = 0; j < GSZ; j++)
				if (i < a*j + b) // y = ax+b
					ground[i][j] += delta;
				else
					ground[i][j] -= delta;

	}

}

void 	UpdateTerrain3()
{
	int x, y;
	double delta = 0.1;
	int total = 5000;

	if (rand() % 2 == 0)
		delta = -delta;

	x = rand() % GSZ;
	y = rand() % GSZ;

	for (int i = 0; i < total; i++)
	{
		ground[y][x] += delta;
		switch (rand() % 4)
		{
		case 0: // UP
			y++;
			break;
		case 1: // LEFT
			x--;
			break;
		case 2: // RIGHT
			x++;
			break;
		case 3: // DOWN
			y--;
			break;
		}
		x = (x + GSZ) % GSZ;
		y = (y + GSZ) % GSZ;
	}

}

void idle()
{
	int i, j;
	double dist;
	angle += 0.05;

	if(isBuilding)
		UpdateTerrain3();

/*
	for (i = 0; i < GSZ; i++)
		for (j = 0; j < GSZ; j++)
		{
			dist = sqrt(pow(i-GSZ/2,2) + pow(j-GSZ/2,2));
			ground[i][j] = 3 * sin(dist / 4.0-angle)+1*sin(j*1.5);
//			ground[i][j] = sqrt(dist) + 1 * sin(j*1.5);

		}
		*/

	sight_angle += angular_speed;

	dirx = sin(sight_angle);
	diry = 0;
	dirz = cos(sight_angle);
	eyex += speed * dirx;
	eyey += dy;
	eyez += speed * dirz;

	glutPostRedisplay(); // sends a message to the window to run display function
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		Smooth();
	}
	if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
//		HPF();
		isBuilding = !isBuilding;
	}

}

void keyboard(unsigned char key, int  x, int y)
{
}

void specialKeys(int key, int x, int y)
{
	/* // simple motion
	switch (key)
	{
	case GLUT_KEY_LEFT:
		dx -= 0.01;
		break;
	case GLUT_KEY_RIGHT:
		dx += 0.01;
		break;
	case GLUT_KEY_UP:
		dz -= 0.01;
		break;
	case GLUT_KEY_DOWN:
		dz += 0.01;
		break;
	case GLUT_KEY_PAGE_UP:
		dy += 0.01;
		break;
	case GLUT_KEY_PAGE_DOWN:
		dy -= 0.01;
		break;
	}
	*/
	// sets speed and angular speed
	switch (key)
	{
	case GLUT_KEY_LEFT:
		angular_speed += 0.001;
		break;
	case GLUT_KEY_RIGHT:
		angular_speed -= 0.001;
		break;
	case GLUT_KEY_UP:
		speed+=0.01;
		break;
	case GLUT_KEY_DOWN:
		speed -= 0.01;
		break;
	case GLUT_KEY_PAGE_UP:
		dy += 0.01;
		break;
	case GLUT_KEY_PAGE_DOWN:
		dy -= 0.01;
		break;
	}

}

void main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // GLUT_DEPTH is Z-buffer
	glutInitWindowSize(W, H);
	glutInitWindowPosition(500, 100);
	glutCreateWindow("3D");

	glutDisplayFunc(display); // display is a name of refresh function
	glutIdleFunc(idle);// idle is a function that runs in background

	glutMouseFunc(mouse);
	// glutKeyboardFunc(keyboard); // this is for regular keys
	glutSpecialFunc(specialKeys);


	init();

	glutMainLoop();
}