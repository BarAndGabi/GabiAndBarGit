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
double waves[GSZ][GSZ] = { 0 };
double tmp[GSZ][GSZ];

double angle = 0;
double eyex = 2, eyey = 20, eyez=12;
double dx = 0, dy = 0, dz = 0; // speed in each direction
double dirx, diry, dirz;
double speed=0, angular_speed=0;
double sight_angle = PI;

double f35x = 0, f35y = 15, f35z = 0;
double f35dirx, f35diry, f35dirz;
double f35speed = 0, f35angular_speed = 0;
double f35sight_angle = PI/2;
double pitch = 0;
bool pitch_is_moving = false;

unsigned char* bmp;
bool isBuilding = false;

void UpdateTerrain1();
void UpdateTerrain2();

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
	for (int counter = 0; counter < 2000; counter++)
	{
		UpdateTerrain2();
	}
	
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

	glColor4d(0, 0.2, 0.6,0.8); // the 4-th parameter is opacity
/*	glBegin(GL_POLYGON);
	glVertex3d(-GSZ / 2, -0.1, -GSZ / 2);
	glVertex3d(GSZ / 2, -0.1, -GSZ / 2);
	glVertex3d(GSZ / 2, -0.1, GSZ / 2);
	glVertex3d(-GSZ / 2, -0.1, GSZ / 2);

	glEnd();
	*/
	for (i = 1; i < GSZ; i++)
		for (j = 1; j < GSZ; j++)
		{
			glBegin(GL_POLYGON);//GL_LINE_LOOP);//
			glVertex3d(j - GSZ / 2, waves[i][j], i - GSZ / 2);
			glVertex3d(j - 1 - GSZ / 2, waves[i][j - 1], i - GSZ / 2);
			glVertex3d(j - 1 - GSZ / 2, waves[i - 1][j - 1], i - 1 - GSZ / 2);
			glVertex3d(j - GSZ / 2, waves[i - 1][j], i - 1 - GSZ / 2);
			glEnd();
		}

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

void DrawColorCube()
{
	// top face
	glBegin(GL_POLYGON);
		glColor3d(1, 0, 0); // red
		glVertex3d(1, 1, 1);
		glColor3d(1, 0, 1); // magenta
		glVertex3d(1, 1, -1);
		glColor3d(0, 0, 1); // blue
		glVertex3d(-1, 1, -1);
		glColor3d(1, 1, 1); // white
		glVertex3d(-1, 1, 1);
	glEnd();
	// left face
	glBegin(GL_POLYGON);
		glColor3d(0, 0, 1); // blue
		glVertex3d(-1, 1, -1);
		glColor3d(1, 1, 1); // white
		glVertex3d(-1, 1, 1);
		glColor3d(0, 1, 0); // green
		glVertex3d(-1, -1, 1);
		glColor3d(0, 1, 1); // cyan
		glVertex3d(-1, -1, -1);

	glEnd();
	// bottom face
	glBegin(GL_POLYGON);
	glColor3d(0, 1, 0); // green
	glVertex3d(-1, -1, 1);
	glColor3d(0, 1, 1); // cyan
	glVertex3d(-1, -1, -1);
	glColor3d(0, 0, 0); // black
	glVertex3d(1, -1, -1);
	glColor3d(1, 1, 0); // yellow
	glVertex3d(1, -1, 1);
	glEnd();
	// right face
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 0); // black
	glVertex3d(1, -1, -1);
	glColor3d(1, 1, 0); // yellow
	glVertex3d(1, -1, 1);
	glColor3d(1, 0, 0); // red
	glVertex3d(1, 1, 1);
	glColor3d(1, 0, 1); // magenta
	glVertex3d(1, 1, -1);
	glEnd();
	// front face
	glBegin(GL_POLYGON);
	glColor3d(0, 1, 0); // green
	glVertex3d(-1, -1, 1);
	glColor3d(1, 1, 0); // yellow
	glVertex3d(1, -1, 1);
	glColor3d(1, 0, 0); // red
	glVertex3d(1, 1, 1);
	glColor3d(1, 1, 1); // white
	glVertex3d(-1, 1, 1);
	glEnd();

	// rear face
	glBegin(GL_POLYGON);
	glColor3d(1, 0, 1); // magenta
	glVertex3d(1, 1, -1);
	glColor3d(0, 0, 1); // blue
	glVertex3d(-1, 1, -1);
	glColor3d(0, 1, 1); // cyan
	glVertex3d(-1, -1, -1);
	glColor3d(0, 0, 0); // black
	glVertex3d(1, -1, -1);
	glEnd();

}

void DrawStairwayToHeaven()
{
	int num_stairs = 60;
	for (int i = 1; i <= num_stairs; i++)
	{
	glPushMatrix();
		glRotated(-20 * i, 0, 1, 0);
		glScaled(5, 0.8, 2);
		glTranslated(1, 1.6*i, 0);
		DrawColorCube();
	glPopMatrix();
	}
}

void DrawCilynder(int n)
{
	double alpha, teta = 2 * PI / n;

	for (alpha = 0; alpha < 2 * PI; alpha += teta)
	{
		glColor3d(fabs(sin(alpha)), 1 - fabs(sin(alpha)), (1 + sin(alpha)) / 2);
		glBegin(GL_POLYGON);
		glVertex3d(sin(alpha), 1, cos(alpha)); // 1
		glVertex3d(sin(alpha+teta), 1, cos(alpha+teta)); // 2 
		glVertex3d(sin(alpha + teta), 0, cos(alpha + teta )); // 3 
		glVertex3d(sin(alpha), 0, cos(alpha )); // 4
		glEnd();
	}

}

void DrawCilynder1(int n, double topr, double bottomr)
{
	double alpha, teta = 2 * PI / n;

	for (alpha = 0; alpha < 2 * PI; alpha += teta)
	{
		glColor3d(fabs(sin(alpha)), fabs(sin(alpha)), fabs(sin(alpha)));
		glBegin(GL_POLYGON);
		glVertex3d(topr*sin(alpha), 1, topr*cos(alpha)); // 1
		glVertex3d(topr*sin(alpha + teta), 1, topr*cos(alpha + teta)); // 2 
		glVertex3d(bottomr*sin(alpha + teta), 0, bottomr*cos(alpha + teta)); // 3 
		glVertex3d(bottomr*sin(alpha), 0, bottomr*cos(alpha)); // 4
		glEnd();
	}

}

void DrawSphere(int n, int slices)
{
	double beta, delta = PI / slices;
	double topr, bottomr;
	int i;
	for (beta = -PI / 2; beta <= PI / 2; beta += delta)
	{
		topr = cos(beta + delta);
		bottomr = cos(beta);
		glPushMatrix();
		glTranslated(0, sin(beta), 0);
		glScaled(1,sin(beta+delta)-sin(beta) , 1);
		DrawCilynder1(n, topr, bottomr);
		glPopMatrix();
	}
}


void DrawApple(int n, int slices)
{
	double beta, delta = PI / slices;
	double topr, bottomr;
	int i;
//	for (beta = 0, i = 0; beta <= 2*PI; beta += delta, i++)
	for(beta = -PI / 2; beta <= PI / 2; beta += delta)
	{
		topr =1+cos(beta + delta);
		bottomr = 1+cos(beta);
		glPushMatrix();
		glTranslated(0, sin(beta), 0);
		glScaled(1, sin(beta + delta) - sin(beta), 1);
		DrawCilynder1(n, topr, bottomr);
		glPopMatrix();
	}
}

void DrawAirplane()
{
	glPushMatrix();
	glRotated(-90, 0, 0, 1);
	// nose
	glPushMatrix();
	glTranslated(0, 5, 0);
	glScaled(1, 5, 1);
	DrawCilynder1(50, 0, 1);
	glPopMatrix();
	// body
	glPushMatrix();
	glScaled(1, 5, 1);
	DrawCilynder1(50, 1, 1.3);
	glPopMatrix();

	// cockpit
	glPushMatrix();
	glTranslated(-0.25, 3, 0);
	glScaled(1, 4, 1);
	glRotated(90, 0, 1, 0);
	DrawSphere(50, 30);
	glPopMatrix();

	// tail
	glPushMatrix();
	glTranslated(0, -10, 0);
	glScaled(1, 10, 1);
	DrawCilynder1(50, 1.3, 0.8);
	glPopMatrix();

	// Wings
	//left (z-axis)
	glColor3d(0, 0, 0.5);
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 0.5);
	glVertex3d(0, 2, 0);
	glVertex3d(0, -4, 6);
	glColor3d(0.7, 0.7, 0.7);
	glVertex3d(0, -6, 6);
	glVertex3d(0, -5, 0);
	glEnd();
	//right (z-axis)
	glColor3d(0, 0, 0.5);
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 0.5);
	glVertex3d(0, 2, 0);
	glVertex3d(0, -4, -6);
	glColor3d(0.7, 0.7, 0.7);
	glVertex3d(0, -6, -6);
	glVertex3d(0, -5, 0);
	glEnd();

	// rear wings
	//left (z-axis)
	glColor3d(0, 0, 0.5);
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 0.5);
	glVertex3d(0, -6, 0);
	glVertex3d(0, -9, 3);
	glColor3d(0.7, 0.7, 0.7);
	glVertex3d(0, -10, 3);
	glVertex3d(0, -11, 0);
	glEnd();
	//right (z-axis)
	glColor3d(0, 0, 0.5);
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 0.5);
	glVertex3d(0, -6, 0);
	glVertex3d(0, -9, -3);
	glColor3d(0.7, 0.7, 0.7);
	glVertex3d(0, -10, -3);
	glVertex3d(0, -11, 0);
	glEnd();

	// vertical wings
	
	glColor3d(0, 0, 0.5);
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 0.5);
	glVertex3d(0, -7, 1);
	glVertex3d(-3, -9, 2);
	glColor3d(0.7, 0.7, 0.7);
	glVertex3d(-3, -10, 2);
	glVertex3d(0, -11, 1);
	glEnd();
	glColor3d(0, 0, 0.5);
	glBegin(GL_POLYGON);
	glColor3d(0, 0, 0.5);
	glVertex3d(0, -7, -1);
	glVertex3d(-3, -9, -2);
	glColor3d(0.7, 0.7, 0.7);
	glVertex3d(-3, -10, -2);
	glVertex3d(0, -11, -1);
	glEnd();


	glPopMatrix();
}

void DrawPitchControl()
{
	glEnable(GL_BLEND);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glColor4d(1, 1, 0, 0.5); // the 4-th parameter is opacity

///	glColor3d(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex2d(0, 0);
	glVertex2d(0, 100);
	glVertex2d(100, 100);
	glVertex2d(100, 0);
	glEnd();

	glDisable(GL_BLEND);


	glLineWidth(2);
	glColor3d(0, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(50, 95);
	glVertex2d(50, 5);
	glEnd();
	glLineWidth(1);

	glColor3d(0.5, 0.5, 0.5);
	glBegin(GL_POLYGON);
	glVertex2d(40, 50+pitch-10);
	glVertex2d(40, 50 + pitch+10);
	glVertex2d(60, 50 + pitch + 10);
	glVertex2d(60, 50 + pitch - 10);
	glEnd();

}

void display() // regular view
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clean frame buffer and z-buffer

	glViewport(0, 0, W, H); // full window
	glMatrixMode(GL_PROJECTION); // here we define working matrices of PROJECTIONS

	glLoadIdentity(); // start transformations here
	glFrustum(-1, 1, -1, 1, 0.7, 350);

	// look to variable direction
	gluLookAt(eyex, eyey, eyez, 
		eyex+dirx, eyey - 1, eyez+dirz,  // this is the direction
		0, 1, 0);

	glMatrixMode(GL_MODELVIEW);// here we switch to working matrices of objects
	DrawFloor();

	glPushMatrix();
//	glRotated(30*angle, 0, 1, 0);
	// 3d shape
	glTranslated(f35x, f35y, f35z);
	glRotated(f35sight_angle*180/PI-90, 0, 1, 0);
	glRotated(f35angular_speed *5000 , -1, 0, 0);
	glRotated(pitch / 100 * 180 / PI, 0, 0, 1);
//	DrawAirplane();
	glPopMatrix();

	// lighting
	float l0amb[4] = { 0.2, 0.2, 0.2,0 };
	float l0dif[4] = { 0.9, 0.9, 0.9,0 };
	float l0sp[4] = { 0.5, 0.5, 0.5,0 };
	float l0pos[4] = { 0.5, 1, 0.3,0 };// if the 4-th parameter is 0 then the light is directional
	// if the 4-th parameter is 1 then the light is positional
	// material grass
	float m0amb[4] = { 0.2, 0.4, 0.2,0 };
	float m0dif[4] = { 0.2, 0.8, 0.2,0 };
	float m0sp[4] = { 0.7, 0.7, 0.7,0 };
	// material silver
	float m1amb[4] = { 0.4, 0.4, 0.4,0 };
	float m1dif[4] = { 0.8, 0.8, 0.8,0 };
	float m1sp[4] = { 0.6, 0.6, 0.6,0 };
	// material gold
	float m2amb[4] = { 0.25, 0.2, 0,0 };
	float m2dif[4] = { 0.75, 0.6, 0.23,0 };
	float m2sp[4] = { 0.62, 0.6, 0.3,0 };

	// Add lighting
	glEnable(GL_LIGHTING); // general lighting
	glEnable(GL_LIGHT0); // light source 0
	glEnable(GL_NORMALIZE);
	// definitions of ight source 0
	glLightfv(GL_LIGHT0, GL_AMBIENT, l0amb);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, l0dif);
	glLightfv(GL_LIGHT0, GL_SPECULAR, l0sp);
	glLightfv(GL_LIGHT0, GL_POSITION, l0pos);

	// cone
	// define material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m1amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m1dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m1sp);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 30);
	glPushMatrix();
	glTranslated(0, 15, 0);
	glRotated(-90, 1, 0, 0);
	glutSolidCone(2, 5, 30, 20);
	glPopMatrix();
	// sphere
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m0amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m0dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m0sp);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 100);
	glPushMatrix();
	glTranslated(9, 15, 0);

	glutSolidSphere(3,30, 20);
	glPopMatrix();
	// teapot
	// define material
	glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, m2amb);
	glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, m2dif);
	glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, m2sp);
	glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 125);
	glPushMatrix();
	glTranslated(-9, 15, 0);
	glRotated(angle * 20, 0, 1, 0);
	glutSolidTeapot(3);
	glPopMatrix();
	glDisable(GL_LIGHTING);



	// add pitch control
	glViewport(0, 0, 100, 100);
	glMatrixMode(GL_PROJECTION); // turn back to PROJECTION matrices
	glLoadIdentity();
	glOrtho(0, 100, 0, 100, -1, 1);
	glDisable(GL_DEPTH_TEST); // 2d
	glMatrixMode(GL_MODELVIEW);// here we switch to working matrices of objects

	DrawPitchControl();
	   
	glEnable(GL_DEPTH_TEST);

	glutSwapBuffers(); // show all
}

void combineddisplay() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clean frame buffer and z-buffer
// regular view
	glViewport(0, H/2, W / 2, H / 2);
	glMatrixMode(GL_PROJECTION); // here we define working matrices of PROJECTIONS

	glLoadIdentity(); // start transformations here
	glFrustum(-1, 1, -1, 1, 0.7, 350);

	// look to variable direction
	gluLookAt(eyex, eyey, eyez,
		eyex + dirx, eyey - 1, eyez + dirz,  // this is the direction
		0, 1, 0);

	glMatrixMode(GL_MODELVIEW);// here we switch to working matrices of objects
	DrawFloor();

	glPushMatrix();
	//	glRotated(30*angle, 0, 1, 0);
		// 3d shape
	glTranslated(f35x, f35y, f35z);
	glRotated(f35sight_angle * 180 / PI - 90, 0, 1, 0);
	glRotated(f35angular_speed * 5000, -1, 0, 0);
	DrawAirplane();
	glPopMatrix();

	// top view
	glViewport(W/2, H / 2, W / 2, H / 2);
	glMatrixMode(GL_PROJECTION); // here we define working matrices of PROJECTIONS

	glLoadIdentity(); // start transformations here
	glFrustum(-1, 1, -1, 1, 0.7, 350);

	// look to variable direction
	gluLookAt(eyex, eyey + 50, eyez,
		eyex + dirx, eyey - 1, eyez + dirz,  // this is the direction
		0, 1, 0);

	glMatrixMode(GL_MODELVIEW);// here we switch to working matrices of objects
	DrawFloor();

	glPushMatrix();
	//	glRotated(30*angle, 0, 1, 0);
		// 3d shape
	glTranslated(f35x, f35y, f35z);
	glRotated(f35sight_angle * 180 / PI - 90, 0, 1, 0);
	glRotated(f35angular_speed * 5000, -1, 0, 0);
	DrawAirplane();
	glPopMatrix();

	// cockpit view
	glViewport(0, 0, W, H / 2);
	glMatrixMode(GL_PROJECTION); // here we define working matrices of PROJECTIONS

	glLoadIdentity(); // start transformations here
	glFrustum(-1, 1, -1, 1, 0.7, 350);

	// look to variable direction
	gluLookAt(f35x, f35y + 4, f35z,
		f35x + f35dirx, f35y + 3, f35z + f35dirz,  // this is the direction
		0, 1, 0);

	glMatrixMode(GL_MODELVIEW);// here we switch to working matrices of objects
	DrawFloor();

	glPushMatrix();
	//	glRotated(30*angle, 0, 1, 0);
		// 3d shape
	glTranslated(f35x, f35y, f35z);
	glRotated(f35sight_angle * 180 / PI - 90, 0, 1, 0);
	glRotated(f35angular_speed * 5000, -1, 0, 0);
	DrawAirplane();


	glPopMatrix();


	glutSwapBuffers(); // show all
}

void topdisplay() // top view
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clean frame buffer and z-buffer

	glViewport(0, 0, W, H); // full window

	glMatrixMode(GL_PROJECTION); // here we define working matrices of PROJECTIONS

	glLoadIdentity(); // start transformations here
	glFrustum(-1, 1, -1, 1, 0.7, 350);

	// look to variable direction
	gluLookAt(eyex, eyey+50, eyez,
		eyex + dirx, eyey - 1, eyez + dirz,  // this is the direction
		0, 1, 0);

	glMatrixMode(GL_MODELVIEW);// here we switch to working matrices of objects
	DrawFloor();

	glPushMatrix();
	//	glRotated(30*angle, 0, 1, 0);
		// 3d shape
	glTranslated(f35x, f35y, f35z);
	glRotated(f35sight_angle * 180 / PI - 90, 0, 1, 0);
	glRotated(f35angular_speed * 5000, -1, 0, 0);
	DrawAirplane();


	glPopMatrix();

	glutSwapBuffers(); // show all
}

void cockpitdisplay() // regular view
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clean frame buffer and z-buffer

	glViewport(0, 0, W, H); // full window

	glMatrixMode(GL_PROJECTION); // here we define working matrices of PROJECTIONS

	glLoadIdentity(); // start transformations here
	glFrustum(-1, 1, -1, 1, 0.7, 350);

	// look to variable direction
	gluLookAt(f35x, f35y+4, f35z,
		f35x + f35dirx, f35y +3, f35z + f35dirz,  // this is the direction
		0, 1,0 );

	glMatrixMode(GL_MODELVIEW);// here we switch to working matrices of objects
	DrawFloor();

	glPushMatrix();
	//	glRotated(30*angle, 0, 1, 0);
		// 3d shape
	glTranslated(f35x, f35y, f35z);
	glRotated(f35sight_angle * 180 / PI - 90, 0, 1, 0);
	glRotated(f35angular_speed * 5000, -1, 0, 0);
	DrawAirplane();


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
	angle += 0.01;

	if(isBuilding)
		UpdateTerrain2();


	// aircraft motion
	f35sight_angle += f35angular_speed;

	f35dirx = sin(f35sight_angle);
	f35diry = sin(pitch/100);
	f35dirz = cos(f35sight_angle);

	f35x += f35speed * f35dirx;
	f35y += f35speed * f35diry;
	f35z += f35speed * f35dirz;

	// ego-motion

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
		if (x > 40 && x < 60 &&
			(H - y)>50 + pitch - 10 && (H - y) < 50 + pitch + 10) // start pitch drag
			pitch_is_moving = true;


//		Smooth();
	}
	if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		if (x > 40 && x < 60 &&
			(H - y)>50 + pitch - 10 && (H - y) < 50 + pitch + 10) // end pitch drag
			pitch_is_moving = false;

	}

}

void mouse_drag(int x, int y)
{
	if (pitch_is_moving && (H-y)<90 && (H - y)>10)
	{
		pitch = (H - y) - 50;
			
	}
}

void keyboard(unsigned char key, int  x, int y)
{
	switch (key)
	{
	case 'a':
		f35angular_speed += 0.002;
		break;
	case 'w':
		f35speed += 0.1;
		break;
	case 's':
		f35speed -= 0.1;
		break;
	case 'd':
		f35angular_speed -= 0.002;
		break;
	}
}

void specialKeys(int key, int x, int y)
{

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

void menu(int choice)
{
	switch(choice)
	{
	case 1: // regular view
		glutDisplayFunc(display);
		break;
	case 2: // top view
		glutDisplayFunc(topdisplay);		
		break;
	case 3: // cockpit view
		glutDisplayFunc(cockpitdisplay);
		break;
	case 4: //combined view
		glutDisplayFunc(combineddisplay);
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
	glutKeyboardFunc(keyboard); // this is for regular keys
	glutSpecialFunc(specialKeys);
	glutMotionFunc(mouse_drag);

	// menu
	glutCreateMenu(menu);
	glutAddMenuEntry("Regular View", 1);
	glutAddMenuEntry("Top View", 2);
	glutAddMenuEntry("Cockpit View", 3);
	glutAddMenuEntry("Combined View", 4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	init();

	glutMainLoop();
}