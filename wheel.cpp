#include "glut.h"
#include <math.h>
#include <time.h>
#include "wheel.h"

const double PI = 3.14;
const int GSIZE = 150;
double angle = 0;
double ground[GSIZE][GSIZE] = { 0 };
double sight_angle = PI;
double eye[3] = {1,5,10};
double sight[3]={sin(sight_angle),-0.2,cos(sight_angle)};
void init()
{
	int i, j;
	srand((unsigned int)time(NULL));
	glClearColor(0.7, 0, 0.3, 0); // background color
}


void DrawCylinder(int n)
{
	double alpha, teta = 2 * PI / n;

	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		glBegin(GL_POLYGON);
		glColor3d(fabs(sin(alpha)), fabs(cos(alpha)), (1 + sin(alpha)) / 2);
		glVertex3d(sin(alpha), 1, cos(alpha));
		glColor3d(fabs(sin(alpha)), fabs(sin(alpha)), (1 + sin(alpha)) / 2);
		glVertex3d(sin(alpha + teta), 1, cos(alpha + teta));
		glColor3d(fabs(sin(alpha + teta)) / 2, fabs(cos(alpha + teta)) / 2, (1 + sin(alpha + teta)) / 4);
		glVertex3d(sin(alpha + teta), 0, cos(alpha + teta));
		glColor3d(fabs(cos(alpha)) / 2, fabs(cos(alpha)) / 2, (1 + sin(alpha)) / 4);
		glVertex3d(sin(alpha), 0, cos(alpha));
		glEnd();
	}
}

void DrawCylinder1(int n, double topr, double bottomr)
{
	double alpha, teta = 2 * PI / n;

	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		glBegin(GL_POLYGON);
		glColor3d(fabs(sin(alpha)), fabs(cos(alpha)), (1 + sin(alpha)) / 2);
		glVertex3d(topr*sin(alpha), 1, topr*cos(alpha));
		glColor3d(fabs(sin(alpha)), fabs(sin(alpha)), (1 + sin(alpha)) / 2);
		glVertex3d(topr*sin(alpha + teta), 1, topr*cos(alpha + teta));
		glColor3d(fabs(sin(alpha + teta)) / 2, fabs(cos(alpha + teta)) / 2, (1 + sin(alpha + teta)) / 4);
		glVertex3d(bottomr*sin(alpha + teta), 0, bottomr*cos(alpha + teta));
		glColor3d(fabs(cos(alpha)) / 2, fabs(cos(alpha)) / 2, (1 + sin(alpha)) / 4);
		glVertex3d(bottomr*sin(alpha), 0, bottomr*cos(alpha));
		glEnd();
	}
}
void DrawCylinder3(int n, double topr, double bottomr)
{
	double alpha, teta = 2 * PI / n;
	int count = 0;
	for (alpha =0; alpha <= 2 * PI&&count<6; alpha += teta)
	{
		count++;
		glBegin(GL_POLYGON);
		glColor3d(fabs(sin(alpha)), fabs(cos(alpha)), (1 + sin(alpha)) / 2);
		glVertex3d(topr*sin(alpha), 1, topr*cos(alpha));
		glColor3d(fabs(sin(alpha)), fabs(sin(alpha)), (1 + sin(alpha)) / 2);
		glVertex3d(topr*sin(alpha + teta), 1, topr*cos(alpha + teta));
		glColor3d(fabs(sin(alpha + teta)) / 2, fabs(cos(alpha + teta)) / 2, (1 + sin(alpha + teta)) / 4);
		glVertex3d(bottomr*sin(alpha + teta), 0, bottomr*cos(alpha + teta));
		glColor3d(fabs(cos(alpha)) / 2, fabs(cos(alpha)) / 2, (1 + sin(alpha)) / 4);
		glVertex3d(bottomr*sin(alpha), 0, bottomr*cos(alpha));
		glEnd();
	}
}
void DrawCylinder2(int n, double topr, double bottomr, double start_angle, double stop_angle)
{
	double alpha, teta = 2 * PI / n;

	for (alpha = start_angle; alpha <= stop_angle; alpha += teta)
	{
		glBegin(GL_POLYGON);
		glColor3d(fabs(sin(alpha)), fabs(cos(alpha)), (1 + sin(alpha)) / 2);
		glVertex3d(topr*sin(alpha), 1, topr*cos(alpha));
		glColor3d(fabs(sin(alpha)), fabs(sin(alpha)), (1 + sin(alpha)) / 2);
		glVertex3d(topr*sin(alpha + teta), 1, topr*cos(alpha + teta));
		glColor3d(fabs(sin(alpha + teta)) / 2, fabs(cos(alpha + teta)) / 2, (1 + sin(alpha + teta)) / 4);
		glVertex3d(bottomr*sin(alpha + teta), 0, bottomr*cos(alpha + teta));
		glColor3d(fabs(cos(alpha)) / 2, fabs(cos(alpha)) / 2, (1 + sin(alpha)) / 4);
		glVertex3d(bottomr*sin(alpha), 0, bottomr*cos(alpha));
		glEnd();
	}
}
void DrawSphere(int n, int s)
{
	double  gamma, delta = PI / s;
	for (gamma = -PI / 2; gamma <= PI / 2; gamma += delta)
	{
		glPushMatrix();
		glTranslated(0, sin(gamma), 0);
		glScaled(1, fabs(sin(gamma) - sin(gamma + delta)), 1);
		DrawCylinder1(n, cos(gamma + delta), cos(gamma));
		glPopMatrix();
	}
}

void DrawConus(int n, double h)
{
	double alpha, teta = 2 * PI / n;

	for (alpha = 0; alpha <= 2 * PI; alpha += teta)
	{
		glBegin(GL_POLYGON);
		glColor3d(fabs(sin(alpha)), fabs(cos(alpha)), (1 + sin(alpha)) / 2);
		glVertex3d(0, h, 0);
		glColor3d(fabs(sin(alpha + teta)) / 2, fabs(cos(alpha + teta)) / 2, (1 + sin(alpha + teta)) / 4);
		glVertex3d(sin(alpha + teta), 0, cos(alpha + teta));
		glColor3d(fabs(cos(alpha)) / 2, fabs(cos(alpha)) / 2, (1 + sin(alpha)) / 4);
		glVertex3d(sin(alpha), 0, cos(alpha));
		glEnd();
	}
}

void drawGround()
{
	glColor3d(0.5, 0.8, 0.4);
	glBegin(GL_POLYGON);
	glVertex3d(-30, 0, -30);
	glVertex3d(30, 0, -30);
	glVertex3d(30, 0, 30);
	glVertex3d(-30, 0, 30);
	glEnd();
}

void drawCarosela()
{
	glColor3d(0.5, 0.2, 0.1);
	glPushMatrix();//thewhole carosela
	glRotated(angle, 0, 1,0);
	glPushMatrix();//celing
	glScaled(1.3, 1, 1.3);
	glTranslated(0, 5, 0);
	DrawCylinder1(10, 1, 4);
	glPopMatrix();
	glPushMatrix();//center
	glScaled(1, 5, 1);
	DrawCylinder1(5, 2, 2);
	glPopMatrix();
	glPushMatrix();
	glScaled(7,0.01, 7);
	DrawCylinder1(25, 0, 1);
	glPopMatrix();
	glPopMatrix();

	
}

void DrawCarousel()
{
	glPushMatrix();
	glPushMatrix();//center
		glScaled(1,7,1);
		DrawCylinder1(12,1,1);
	glPopMatrix();
	glPushMatrix();//up
		glTranslated(0,6,0);
		glScaled(5,2,5);
		DrawCylinder1(12,0,1);
	glPopMatrix();
	glPushMatrix();
		glTranslated(0,1,0);
		glScaled(5,0.1,5);
		DrawCylinder1(12,0,1);
	glPopMatrix();
	
		glPopMatrix();
}

void drawAirplain()
{
	glPushMatrix();//plain
		glPushMatrix();//body
			glRotated(-40, 1, 0, 0);
				glPushMatrix();
					glTranslated(0, 2, 0);
					glScaled(1.5, 1.5, 1.5);
					glRotated(90, 0, 0,1);
					DrawConus(20, 5);
				glPopMatrix();
				glPushMatrix();
					glTranslated(0, 2, 0);
					glScaled(5, 1, 1);
					glRotated(270, 0, 0, 1);
					DrawCylinder3(7, 1.7, 1.5);
				glPopMatrix();
				glPushMatrix();
					glTranslated(5, 2, 0);
					glScaled(1.7, 1.7, 1.7);
					glRotated(270, 0, 0, 1);
					DrawConus(20, 3.5);
				glPopMatrix();
		glPopMatrix();
		glPushMatrix();
			drawPropelor();
		glPopMatrix();
			glPushMatrix();
				drawBigWings();
			glPopMatrix();
	glPopMatrix();


}
void drawBigWings()
{
	glColor3d(0, 0,1);
	glTranslated(1, 1, 0);
	glBegin(GL_POLYGON);
	glVertex3d(0, 1, 5);
	glVertex3d(0, 1, -5);
	glVertex3d(4, 1, 3);
	glVertex3d(4, 1, -3);
	glEnd();
}
void drawPropelor()
{
	glLineWidth(5);
	glColor3d(0, 0.2, 0);
	glTranslated(-6.2, 2, 0);
	glRotated(angle, 1, 0, 0);
	glBegin(GL_LINE_STRIP);
	glVertex3d(0, 2, 0);
	glVertex3d(0, -2, 0);
	glEnd();
}
void display()
{
	int i;
	double beta;

	glViewport(0, 100, 600, 500);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // start transformations

	glFrustum(-1, 1, -1, 1, 0.8, 300);
	gluLookAt(eye[0], eye[1], eye[2],
		eye[0] + sight[0], eye[1] + sight[1], eye[2] + sight[2],
		0, 1, 0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // start transformations
	drawGround();
	//drawCarosela();
	//DrawCarousel();
	drawAirplain();
	glutSwapBuffers();
}


void idle()
{

	angle = angle + 0.8;
	glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{

}

void SpecialKeys(int key, int x, int y)
{
	switch (key)
	{
	case GLUT_KEY_RIGHT:
		break;
	case GLUT_KEY_LEFT:
		break;
	case GLUT_KEY_UP:
		break;
	case GLUT_KEY_DOWN:
		break;
	case GLUT_KEY_PAGE_UP:
		break;
	case GLUT_KEY_PAGE_DOWN:
		break;
	}
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{

	}
}

void Motion(int x, int y)
{

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("EXAM");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMouseFunc(Mouse);
	glutMotionFunc(Motion);
	glutSpecialFunc(SpecialKeys);
	glutKeyboardFunc(keyboard);

	init();
	glutMainLoop();
}



//#include "glut.h"
//#include <math.h>
//#include <time.h>
//
//const double PI = 3.14;
//const int GSIZE = 150;
//
//double ground[GSIZE][GSIZE]={0};
//
//double eye[3] = {1,5,10};
//double dx=0,dy=0,dz=0;
//double sight_angle=PI;
//double speed=0;
//double angle_speed=0;
//double delta=0;
//double sight[3]={sin(sight_angle),-0.2,cos(sight_angle)};
//bool isBuilding = true;
//double angle=0;
//double speed_control=0;
//
//double airplane_speed = 0;
//double airplane_angle_speed = 0;
//double yaw = PI/2;
//double airplane_dir[3] = {1,0,0};
//double airplane_location[3] = {0,10,0};
//
//void Smooth();
//void UpdateTerrain1();
//void UpdateTerrain2();
//
//void init()
//{
//	int i,j;
//	srand((unsigned int) time(NULL));
//
//
//	glClearColor(1,1,1,0); // background color
//}
//
//
//void DrawCylinder(int n)
//{
//	double alpha,teta = 2*PI/n;
//
//	for(alpha=0;alpha<=2*PI;alpha+=teta)
//	{
//		glBegin(GL_POLYGON);	
//			glColor3d(fabs(sin(alpha)),fabs(cos(alpha)),(1+sin(alpha))/2);
//		glVertex3d(sin(alpha),1,cos(alpha));
//			glColor3d(fabs(sin(alpha)),fabs(sin(alpha)),(1+sin(alpha))/2);
//		glVertex3d(sin(alpha+teta),1,cos(alpha+teta));
//			glColor3d(fabs(sin(alpha+teta))/2,fabs(cos(alpha+teta))/2,(1+sin(alpha+teta))/4);
//		glVertex3d(sin(alpha+teta),0,cos(alpha+teta));
//			glColor3d(fabs(cos(alpha))/2,fabs(cos(alpha))/2,(1+sin(alpha))/4);
//		glVertex3d(sin(alpha),0,cos(alpha));
//		glEnd();
//	}
//}
//
//void DrawCylinder1(int n,double topr,double bottomr)
//{
//	double alpha,teta = 2*PI/n;
//
//	for(alpha=0;alpha<=2*PI;alpha+=teta)
//	{
//		glBegin(GL_POLYGON);	
//			glColor3d(fabs(sin(alpha)),fabs(cos(alpha)),(1+sin(alpha))/2);
//		glVertex3d(topr*sin(alpha),1,topr*cos(alpha));
//			glColor3d(fabs(sin(alpha)),fabs(sin(alpha)),(1+sin(alpha))/2);
//		glVertex3d(topr*sin(alpha+teta),1,topr*cos(alpha+teta));
//			glColor3d(fabs(sin(alpha+teta))/2,fabs(cos(alpha+teta))/2,(1+sin(alpha+teta))/4);
//		glVertex3d(bottomr*sin(alpha+teta),0,bottomr*cos(alpha+teta));
//			glColor3d(fabs(cos(alpha))/2,fabs(cos(alpha))/2,(1+sin(alpha))/4);
//		glVertex3d(bottomr*sin(alpha),0,bottomr*cos(alpha));
//		glEnd();
//	}
//}
//void DrawCylinder2(int n,double topr,double bottomr, double start_angle, double stop_angle)
//{
//	double alpha,teta = 2*PI/n;
//
//	for(alpha=start_angle;alpha<=stop_angle;alpha+=teta)
//	{
//		glBegin(GL_POLYGON);	
//			glColor3d(fabs(sin(alpha)),fabs(cos(alpha)),(1+sin(alpha))/2);
//		glVertex3d(topr*sin(alpha),1,topr*cos(alpha));
//			glColor3d(fabs(sin(alpha)),fabs(sin(alpha)),(1+sin(alpha))/2);
//		glVertex3d(topr*sin(alpha+teta),1,topr*cos(alpha+teta));
//			glColor3d(fabs(sin(alpha+teta))/2,fabs(cos(alpha+teta))/2,(1+sin(alpha+teta))/4);
//		glVertex3d(bottomr*sin(alpha+teta),0,bottomr*cos(alpha+teta));
//			glColor3d(fabs(cos(alpha))/2,fabs(cos(alpha))/2,(1+sin(alpha))/4);
//		glVertex3d(bottomr*sin(alpha),0,bottomr*cos(alpha));
//		glEnd();
//	}
//}
//void DrawSphere(int n, int s)
//{
//	double  gamma, delta = PI/s;
//	for(gamma = -PI/2;gamma<=PI/2;gamma+=delta)
//	{
//		glPushMatrix();
//			glTranslated(0,sin(gamma),0);
//			glScaled(1,fabs(sin(gamma)-sin(gamma+delta)),1);
//			DrawCylinder1(n,cos(gamma+delta),cos(gamma));
//		glPopMatrix();
//	}
//}
//
//void DrawConus(int n,double h)
//{
//	double alpha,teta = 2*PI/n;
//
//	for(alpha=0;alpha<=2*PI;alpha+=teta)
//	{
//		glBegin(GL_POLYGON);	
//			glColor3d(fabs(sin(alpha)),fabs(cos(alpha)),(1+sin(alpha))/2);
//		glVertex3d(0,h,0);
//			glColor3d(fabs(sin(alpha+teta))/2,fabs(cos(alpha+teta))/2,(1+sin(alpha+teta))/4);
//		glVertex3d(sin(alpha+teta),0,cos(alpha+teta));
//			glColor3d(fabs(cos(alpha))/2,fabs(cos(alpha))/2,(1+sin(alpha))/4);
//		glVertex3d(sin(alpha),0,cos(alpha));
//		glEnd();
//	}
//}
//
//void DrawGround()
//{
//	glColor3d(0.5,0.8,0.4);
//	glBegin(GL_POLYGON);
//		glVertex3d(-30,0,-30);
//		glVertex3d(30,0,-30);
//		glVertex3d(30,0,30);
//		glVertex3d(-30,0,30);
//	glEnd();
//}
//
//void DrawAirplane()
//{
//	// propeller
//	glPushMatrix();
//	glTranslated(4.5,0,0);
//		glRotated(90,0,0,1);
//		glRotated(40*angle,0,1,0);
//			glColor3d(0.3,0.2,0);
//		glBegin(GL_POLYGON);
//			glVertex3d(-0.1,0,-1);
//			glVertex3d(0.1,0,-1);
//			glVertex3d(-0.1,0,1);
//			glVertex3d(0.1,0,1);
//		glEnd();
//
//	glPopMatrix();
//	glPushMatrix();
//			glTranslated(2,0,0);
//			glRotated(-90,0,0,1);
//			glScaled(1,3,1);
//			DrawCylinder1(12,0,1);
//		glPopMatrix();
//		glPushMatrix();
//			glRotated(-90,0,0,1);
//			glScaled(1,2,1);
//			DrawCylinder2(12,1,1,-PI/4,5*PI/4);
//		glPopMatrix();
//		glPushMatrix();
//			glTranslated(-3,0,0);
//			glRotated(-90,0,0,1);
//			glScaled(1,3,1);
//			DrawCylinder1(12,1,0.2);
//		glPopMatrix();
//		// wings
//		glBegin(GL_POLYGON);
//		glColor3d(1,1,1);
//			glVertex3d(3.5,0,0);
//		glColor3d(1,0,0);
//			glVertex3d(1,0,2);
//			glVertex3d(0,0,2);
//			glVertex3d(0,0,-2);
//			glVertex3d(1,0,-2);
//		glEnd();
//
//		glBegin(GL_POLYGON);
//		glColor3d(1,1,1);
//			glVertex3d(0,0,0);
//		glColor3d(1,0,0);
//			glVertex3d(-1.5,0,1.5);
//			glVertex3d(-2.5,0,1.5);
//			glVertex3d(-2.5,0,-1.5);
//			glVertex3d(-1.5,0,-1.5);
//		glEnd();
//		// tail
//		glBegin(GL_POLYGON);
//		glColor3d(1,1,1);
//			glVertex3d(1,0,0);
//		glColor3d(1,0,0);
//			glVertex3d(-2,2,0);
//			glVertex3d(-3,2,0);
//			glVertex3d(-2.5,0,0);
//		glEnd();
//
//
//}
//
//void DrawCarousel()
//{
//	glPushMatrix();
//	glPushMatrix();
//		glScaled(1,7,1);
//		DrawCylinder1(12,1,1);
//	glPopMatrix();
//	glPushMatrix();
//		glTranslated(0,6,0);
//		glScaled(5,2,5);
//		DrawCylinder1(12,0,1);
//	glPopMatrix();
//	glPushMatrix();
//		glTranslated(0,1,0);
//		glScaled(5,0.1,5);
//		DrawCylinder1(12,0,1);
//	glPopMatrix();
//	glPushMatrix();
//		glScaled(5,1,5);
//		DrawCylinder1(12,1,1);
//	glPopMatrix();
//	// add airplanes
//
//	glPushMatrix();
//		glTranslated(0,2,3.5);
//		glScaled(0.3,0.3,0.3);
//		DrawAirplane();
//	glPopMatrix();
//
//	glPushMatrix();
//	glRotated(90,0,1,0);
//		glTranslated(0,2,3.5);
//		glScaled(0.3,0.3,0.3);
//		DrawAirplane();
//	glPopMatrix();
//	glPushMatrix();
//	glRotated(180,0,1,0);
//		glTranslated(0,2,3.5);
//		glScaled(0.3,0.3,0.3);
//		DrawAirplane();
//	glPopMatrix();
//	glPushMatrix();
//	glRotated(270,0,1,0);
//		glTranslated(0,2,3.5);
//		glScaled(0.3,0.3,0.3);
//		DrawAirplane();
//	glPopMatrix();
//		glPopMatrix();
//}
//
//void DrawSpeedControl()
//{
//	glColor3d(0.6,0.6,0.6);
//	glBegin(GL_POLYGON);
//		glVertex2d(-0.5,0.15);
//		glVertex2d(0.5,0.15);
//		glVertex2d(0.5,-0.15);
//		glVertex2d(-0.5,-0.15);
//	glEnd();
//	glLineWidth(2);
//	glColor3d(0,0,0.3);
//	glBegin(GL_LINES);
//		glVertex2d(-0.5,0);
//		glVertex2d(0.5,0);
//	glEnd();
//	glColor3d(0.7,0.7,0.7);
//	glBegin(GL_LINE_STRIP);
//		glVertex2d(-0.5,0.15);
//		glVertex2d(0.5,0.15);
//		glVertex2d(0.5,-0.15);
//	glEnd();
//	glColor3d(0.5,0.5,0.5);
//	glBegin(GL_LINE_STRIP);
//		glVertex2d(0.5,-0.15);
//		glVertex2d(-0.5,-0.15);
//		glVertex2d(-0.5,0.15);
//	glEnd();
//
//	// control
//
//		glColor3d(0,1,0);
//	glBegin(GL_LINE_LOOP);
//		glVertex2d(speed_control-0.02,-0.02);
//		glVertex2d(speed_control,+0.03);
//		glVertex2d(speed_control+0.02,-0.02);
//	glEnd();
//
//}
//
//void display()
//{
//	int i;
//	double beta;
//
//	glViewport(0,100,600,500);
//	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
//
//	glEnable(GL_DEPTH_TEST);
//
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity(); // start transformations
//
//	glFrustum(-1,1,-1,1,0.8,300);
//	gluLookAt(eye[0],eye[1],eye[2],
//		eye[0]+sight[0],eye[1]+sight[1],eye[2]+sight[2],
//		0,1,0);
//
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity(); // start transformations
//	DrawGround();
//
//	glPushMatrix();
//		glRotated(angle,0,1,0);
//	glTranslated(0,22,0);
////		glScaled(0.3,0.3,0.3);
//		DrawAirplane();
//	glPopMatrix();
//	
//	glPushMatrix();
//		glRotated(angle,0,1,0);
//		DrawCarousel();
//	glPopMatrix();
//
//	// control
//	glViewport(0,0,600,100);
//	glDisable(GL_DEPTH_TEST);
//	glMatrixMode(GL_PROJECTION);
//	glLoadIdentity(); // start transformations
//	glOrtho(-1,1,-0.2,0.2,-1,1);
//	glMatrixMode(GL_MODELVIEW);
//	glLoadIdentity(); // start transformations
//
//	DrawSpeedControl();
//
//	glutSwapBuffers();
//}
//
//
//void idle()
//{
//	angle+=speed_control;
//
//	sight_angle+=angle_speed;
//	// compute sight direction
//	sight[0] = sin(sight_angle);
//	sight[2] = cos(sight_angle);
//	// update eye position
//	eye[0]+=speed*sight[0];
////	eye[1]+=dy;
//	eye[2]+=speed*sight[2];
//
//	glutPostRedisplay();
//}
//
//void Mouse(int button, int state, int x ,int y)
//{
//
//}
//
//void SpecialKeys(int key, int x ,int y)
//{
//	switch(key)
//	{
//		case GLUT_KEY_RIGHT:
//			angle_speed-=0.001;
//			break;
//		case GLUT_KEY_LEFT:
//			angle_speed+=0.001;
//			break;
//		case GLUT_KEY_UP:
//			speed+=0.01;
//			break;
//		case GLUT_KEY_DOWN:
//			speed-=0.01;
//			break;
//		case GLUT_KEY_PAGE_UP:
//			eye[1]+=0.1;
//			break;
//		case GLUT_KEY_PAGE_DOWN:
//			eye[1]-=0.1;
//			break;
//	}
//}
//
//void keyboard(unsigned char key, int x, int y)
//{
//	switch(key)
//	{
//
//	}
//}
//
//void Motion(int x, int y)
//{
//	if(y>500 && x>150 && x<450)
//	{
//		speed_control = (x-300)/300.0;
//	}
//}
//
//void main(int argc, char** argv)
//{
//	glutInit(&argc, argv);
//	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
//	glutInitWindowSize(600,600);
//	glutInitWindowPosition(100,100);
//	glutCreateWindow("EXAM");
//
//	glutDisplayFunc(display);
//	glutIdleFunc(idle);
//	glutMouseFunc(Mouse);
//	glutMotionFunc(Motion);
//	glutSpecialFunc(SpecialKeys);
//	glutKeyboardFunc(keyboard);
//
//	init();
//	glutMainLoop();
//}