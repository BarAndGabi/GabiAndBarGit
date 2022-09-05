#define _CRT_SECURE_NO_WARNINGS

#include "glut.h"
#include <math.h>
#include <stdio.h>

const int W = 600;
const int H = 600;
const double PI = 3.14;
const int GSZ = 200;

double ground[GSZ][GSZ][3] ; // y = f(x,z)
double tmp[GSZ][GSZ];

double angle = 0;
double eyex = 2, eyey = 40, eyez=10;
double dx = 0, dy = 0, dz = 0; // speed in each direction
double dirx, diry, dirz;
double speed=0, angular_speed=0;
double sight_angle = PI;

unsigned char* bmp;

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
	char name[20] = "flower.bmp";
	glClearColor(0.3, 0.6, 0.8, 0);// color of window background

	glEnable(GL_DEPTH_TEST); // uses Z-buffer

/*	for(i=0;i<GSZ;i++)
		for (j = 0; j < GSZ; j++)
		{
			ground[i][j] = 4*sin(i/4.0);
		}
		*/
	ReadPicture(name);

	for (i = 0,k=0; i < GSZ; i++)
		for (j = 0; j < GSZ; j++,k+=3)
		{
			ground[i][j][2] = bmp[k]; // blue
			ground[i][j][1] = bmp[k+1];//green
			ground[i][j][0] = bmp[k+2];// red
		}
}

void SetColor(double h)
{
	double r, g, b;
//	r = fabs(h) / 4;
//	g = fabs(h) / 4;
//	b = fabs(h) / 4;
//	r = (h + 4) / 8;
//	g = (h + 4) / 8;
//	b = (h + 4) / 8;
	r = h / 25;
	g = h / 25;
	b = h / 25;
	glColor3d(r, g, b);
}


void DrawFloor()
{
	int i, j;
	glColor3d(0,0,0);
/*	for (int i = -10; i <= 10; i++)
	{
		glBegin(GL_LINES);
		glVertex3d(-10, 0, i); // left point
		glVertex3d(10, 0, i); // right point
		glEnd();
	}
	for (int i = -10; i <= 10; i++)
	{
		glBegin(GL_LINES);
		glVertex3d(i, 0, -10); // near point
		glVertex3d(i, 0, 10); // far point
		glEnd();
	}
*/

	// sets height by green channel:   ground[i][j][1]
	for(i=1;i<GSZ;i++)
		for (j = 1; j < GSZ; j++)
		{
			glBegin(GL_POLYGON);//GL_LINE_LOOP);//
//			SetColor(ground[i][j]);
			glColor3d(ground[i][j][0] / 255, ground[i][j][1] / 255, ground[i][j][2] / 255);
			glVertex3d(j-GSZ/2, ground[i][j][1] /10, i - GSZ / 2);
//			SetColor(ground[i][j-1]);
			glColor3d(ground[i][j-1][0] / 255, ground[i][j-1][1] / 255, ground[i][j-1][2] / 255);
			glVertex3d(j - 1 - GSZ / 2, ground[i][j-1][1] /10, i - GSZ / 2);
//			SetColor(ground[i-1][j-1]);
			glColor3d(ground[i-1][j-1][0] / 255, ground[i-1][j-1][1] / 255, ground[i-1][j-1][2] / 255);
			glVertex3d(j - 1 - GSZ / 2, ground[i-1][j-1][1] /10, i-1 - GSZ / 2);
//			SetColor(ground[i-1][j]);
			glColor3d(ground[i-1][j][0] / 255, ground[i-1][j][1] / 255, ground[i-1][j][2] / 255);
			glVertex3d(j - GSZ / 2, ground[i-1][j][1] /10, i - 1 - GSZ / 2);
			glEnd();
		}


	// add axes
	glLineWidth(3);
	glBegin(GL_LINES);
	// x
	glColor3d(1, 0, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(11, 0, 0);
	// y
	glColor3d(0, 1, 0);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 5, 0);

	// z
	glColor3d(0, 0, 1);
	glVertex3d(0, 0, 0);
	glVertex3d(0, 0, 11);

	glEnd();


	glLineWidth(1);
}

void Smooth()
{
	int i, j;
	int channel = 1; // green

	for(i=1;i<GSZ-1;i++)
		for (j = 1; j < GSZ - 1; j++)
		{
			// the mask is of size 3x3
			tmp[i][j] = (ground[i-1][j-1][channel]+ 2*ground[i - 1][j][channel]+ ground[i - 1][j + 1][channel]+
				2*ground[i ][j - 1][channel] + 4*ground[i ][j][channel] + 2*ground[i ][j + 1][channel] +
				ground[i + 1][j - 1][channel] + 2*ground[i + 1][j][channel] + ground[i + 1][j + 1][channel] ) / 16.0;
		}

	for (i = 1; i < GSZ - 1; i++)
		for (j = 1; j < GSZ - 1; j++)
			ground[i][j][channel] = tmp[i][j];
}

void HPF()
{
	int i, j;
	int channel = 1; // green

	for (i = 1; i < GSZ - 1; i++)
		for (j = 1; j < GSZ - 1; j++)
		{
			// the mask is of size 3x3
			tmp[i][j] = (-ground[i - 1][j - 1][channel] - 2 * ground[i - 1][j][channel] + -ground[i - 1][j + 1][channel] -
				2 * ground[i][j - 1][channel] + 12 * ground[i][j][channel] - 2 * ground[i][j + 1][channel] 
				-ground[i + 1][j - 1][channel] - 2 * ground[i + 1][j][channel] - ground[i + 1][j + 1][channel])/4.0 ;
		}

	for (i = 1; i < GSZ - 1; i++)
		for (j = 1; j < GSZ - 1; j++)
			ground[i][j][channel] = fabs(tmp[i][j]);
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

void idle()
{
	int i, j;
	double dist;
	angle += 0.05;
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
		HPF();
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