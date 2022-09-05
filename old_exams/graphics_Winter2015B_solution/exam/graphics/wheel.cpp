#include "glut.h"
#include <math.h>
#include <time.h>

const double PI = 3.14;
const int GSIZE = 150;

double ground[GSIZE][GSIZE]={0};

double eye[3] = {2,18,15};
double dx=0,dy=0,dz=0;
double sight_angle=PI;
double speed=0;
double angle_speed=0;
double delta=0;
double sight[3]={sin(sight_angle),-0.2,cos(sight_angle)};
bool isBuilding = true;
double angle=0.5;
double height = 0.5,width=0.5; // arrow


void init()
{
	int i,j;
	srand((unsigned int) time(NULL));

	glClearColor(1,1,1,0); // background color
}


void DrawCylinder1(int n,double topr,double bottomr)
{
	double alpha,teta = 2*PI/n;

	for(alpha=0;alpha<=2*PI;alpha+=teta)
	{
		glBegin(GL_POLYGON);	
			glColor3d(fabs(sin(alpha)),fabs(cos(alpha)),(1+sin(alpha))/2);
		glVertex3d(topr*sin(alpha),1,topr*cos(alpha));
			glColor3d(fabs(sin(alpha)),fabs(sin(alpha)),(1+sin(alpha))/2);
		glVertex3d(topr*sin(alpha+teta),1,topr*cos(alpha+teta));
			glColor3d(fabs(sin(alpha+teta))/2,fabs(cos(alpha+teta))/2,(1+sin(alpha+teta))/4);
		glVertex3d(bottomr*sin(alpha+teta),0,bottomr*cos(alpha+teta));
			glColor3d(fabs(cos(alpha))/2,fabs(cos(alpha))/2,(1+sin(alpha))/4);
		glVertex3d(bottomr*sin(alpha),0,bottomr*cos(alpha));
		glEnd();
	}
}

void DrawGround()
{
	glColor3d(0.5,0.8,0.4);
	glBegin(GL_POLYGON);
		glVertex3d(-30,0,-30);
		glVertex3d(30,0,-30);
		glVertex3d(30,0,30);
		glVertex3d(-30,0,30);
	glEnd();
}

void DrawArm()
{
	int i;
	glColor3d(0.5,0.5,0.5);
	glBegin(GL_POLYGON);
		glVertex3d(-2,0.2,-2); 		
		glVertex3d(2,0.2,-2); 		
		glVertex3d(2,0.2,2); 		
		glVertex3d(-2,0.2,2); 		
	glEnd();
	glBegin(GL_POLYGON);
		glVertex3d(-2,-1,-2); 		
		glVertex3d(2,-1,-2); 		
		glVertex3d(2,-1,2); 		
		glVertex3d(-2,-1,2); 		
	glEnd();

	glColor3d(0,0,0);

	glBegin(GL_LINES);
		glVertex3d(-1,-1,-1); 		glVertex3d(-1,15,-1);
		glVertex3d(1,-1,-1); 		glVertex3d(1,15,-1);
		glVertex3d(1,-1,1); 		glVertex3d(1,15,1);
		glVertex3d(-1,-1,1); 		glVertex3d(-1,15,1);
	glEnd();
	glBegin(GL_LINES);
		glVertex3d(-1,15,-1);	glVertex3d(0,18,0);
		glVertex3d(1,15,-1);	glVertex3d(0,18,0);
		glVertex3d(1,15,1);		glVertex3d(0,18,0);
		glVertex3d(-1,15,1);	glVertex3d(0,18,0);
	glEnd();
	for(i=1;i<=15;i+=2)
	{
	glBegin(GL_LINE_LOOP);
		glVertex3d(-1,i,-1);	
		glVertex3d(1,i,-1);	
		glVertex3d(1,i,1);		
		glVertex3d(-1,i,1);	
	glEnd();
	glBegin(GL_LINES);
		glVertex3d(-1,i,-1);	glVertex3d(1,i-2,1);
		glVertex3d(1,i,-1);		glVertex3d(-1,i-2,1);	
		glVertex3d(1,i,1);		glVertex3d(-1,i-2,-1);
		glVertex3d(-1,i,1);		glVertex3d(1,i-2,-1);
	glEnd();
	}

}
void DrawCrane()
{
	glPushMatrix();
		glScaled(0.7,1,0.7);
		DrawArm();
	glPopMatrix();
	glPushMatrix();
	glTranslated(-4,14,0);
		glRotated(-90,0,0,1);
		glScaled(0.5,0.8,0.5);
		DrawArm();
	glPopMatrix();
	glBegin(GL_LINE_STRIP);
		glVertex3d(-4,14.5,0);	
		glVertex3d(0,18,0);
		glVertex3d(8,14.5,0);	
	glEnd();
	// arrow
	double offset = 3+width*(15*0.7);
	glColor3d(1,0,0);
	glPushMatrix();
	glScaled(0.5,1,0.5);
	glBegin(GL_POLYGON);
		glVertex3d(offset-1,13.5,-1); 		
		glVertex3d(offset+1,13.5,-1); 		
		glVertex3d(offset+1,13.5,1); 		
		glVertex3d(offset-1,13.5,1); 		
	glEnd();
	glBegin(GL_LINE_STRIP);
		glVertex3d(offset,13.5,0); 		
		glVertex3d(offset,13.5-(1-height)*13.5,0); 	
		glColor3d(0,0,0);

		glVertex3d(offset+0.2,13.5-(1-height)*13.5-0.2,0); 		
		glVertex3d(offset,13.5-(1-height)*13.5-0.4,0); 		
		glVertex3d(offset-0.2,13.5-(1-height)*13.5-0.2,0); 		
	glEnd();
	glPopMatrix();


}

void DrawWControl()
{
	glColor3d(0.6,0.6,0.6);
	glBegin(GL_POLYGON);
		glVertex2d(-0.9,0.15);
		glVertex2d(-0.2,0.15);
		glVertex2d(-0.2,-0.15);
		glVertex2d(-0.9,-0.15);
	glEnd();
	glLineWidth(2);
	glColor3d(0,0,0.3);
	glBegin(GL_LINES);
		glVertex2d(-0.9,0);
		glVertex2d(-0.2,0);
	glEnd();
	glColor3d(0.7,0.7,0.7);
	glBegin(GL_LINE_STRIP);
		glVertex2d(-0.9,0.15);
		glVertex2d(-0.2,0.15);
		glVertex2d(-0.2,-0.15);
	glEnd();
	glColor3d(0.5,0.5,0.5);
	glBegin(GL_LINE_STRIP);
		glVertex2d(-0.2,-0.15);
		glVertex2d(-0.9,-0.15);
		glVertex2d(-0.9,0.15);
	glEnd();

	// control

		glColor3d(0,1,0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(-0.9+width*0.7-0.02,-0.02);
		glVertex2d(-0.9+width*0.7,+0.03);
		glVertex2d(-0.9+width*0.7+0.02,-0.02);
	glEnd();
	glLineWidth(1);


}
void DrawHControl()
{
	glColor3d(0.6,0.6,0.6);
	glBegin(GL_POLYGON);
		glVertex2d(-0.1,0.25);
		glVertex2d(0.1,0.25);
		glVertex2d(0.1,-0.25);
		glVertex2d(-0.1,-0.25);
	glEnd();
	glLineWidth(2);
	glColor3d(0,0,0.25);
	glBegin(GL_LINES);
		glVertex2d(0,0.25);
		glVertex2d(0,-0.25);
	glEnd();
	glColor3d(0.7,0.7,0.7);
	glBegin(GL_LINE_STRIP);
		glVertex2d(-0.1,0.25);
		glVertex2d(0.1,0.25);
		glVertex2d(0.1,-0.25);
	glEnd();
	glColor3d(0.5,0.5,0.5);
	glBegin(GL_LINE_STRIP);
		glVertex2d(0.1,-0.25);
		glVertex2d(-0.1,-0.25);
		glVertex2d(-0.1,0.25);
	glEnd();

	// control

		glColor3d(0,1,0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(0.03,-0.25+height*0.5+0.02);
		glVertex2d(-0.03,-0.25+height*0.5);
		glVertex2d(0.03,-0.25+height*0.5-0.02);
	glEnd();
	glLineWidth(1);


}

void DrawAngleControl()
{
	glColor3d(0.6,0.6,0.6);
	glBegin(GL_POLYGON);
		glVertex2d(0.9,0.15);
		glVertex2d(0.2,0.15);
		glVertex2d(0.2,-0.15);
		glVertex2d(0.9,-0.15);
	glEnd();
	glLineWidth(2);
	glColor3d(0,0,0.3);
	glBegin(GL_LINES);
		glVertex2d(0.9,0);
		glVertex2d(0.2,0);
	glEnd();
	glColor3d(0.7,0.7,0.7);
	glBegin(GL_LINE_STRIP);
		glVertex2d(0.2,0.15);
		glVertex2d(0.9,0.15);
		glVertex2d(0.9,-0.15);
	glEnd();
	glColor3d(0.5,0.5,0.5);
	glBegin(GL_LINE_STRIP);
		glVertex2d(0.9,-0.15);
		glVertex2d(0.2,-0.15);
		glVertex2d(0.2,0.15);
	glEnd();

	// control

		glColor3d(0,1,0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(0.2+(angle/(2*PI))*0.7-0.02,-0.02);
		glVertex2d(0.2+(angle/(2*PI))*0.7,+0.03);
		glVertex2d(0.2+(angle/(2*PI))*0.7+0.02,-0.02);
	glEnd();
	glLineWidth(1);


}

void DrawControls()
{
	glColor3d(0.7,0.7,0.6);
	glBegin(GL_POLYGON);
		glVertex2d(-1,-0.3);
		glVertex2d(-1,0.3);
		glVertex2d(1,0.3);
		glVertex2d(1,-0.3);
	glEnd();
	DrawWControl();
	DrawHControl();
	DrawAngleControl();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glViewport(0,200,600,400);
	glEnable(GL_DEPTH_TEST);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // start transformations

	glFrustum(-1,1,-1,1,0.8,300);
	gluLookAt(eye[0],eye[1],eye[2],
		eye[0]+sight[0],eye[1]+sight[1],eye[2]+sight[2],
		0,1,0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // start transformations

	DrawGround();

	glPushMatrix();
	glRotated(angle*180/PI,0,1,0);
	DrawCrane();
	glPopMatrix();

	glViewport(0,0,600,200);
	glDisable(GL_DEPTH_TEST);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // start transformations

	glOrtho(-1,1,-0.4,0.4,-1,1);
	DrawControls();
	glutSwapBuffers();
}


void idle()
{
//	angle+=0.03;
	sight_angle+=angle_speed;
	// compute sight direction
	sight[0] = sin(sight_angle);
	sight[2] = cos(sight_angle);
	// update eye position
	eye[0]+=speed*sight[0];
//	eye[1]+=dy;
	eye[2]+=speed*sight[2];

	glutPostRedisplay();
}

void SpecialKeys(int key, int x ,int y)
{
	switch(key)
	{
		case GLUT_KEY_RIGHT:
			angle_speed-=0.001;
			break;
		case GLUT_KEY_LEFT:
			angle_speed+=0.001;
			break;
		case GLUT_KEY_UP:
			speed+=0.01;
			break;
		case GLUT_KEY_DOWN:
			speed-=0.01;
			break;
		case GLUT_KEY_PAGE_UP:
			eye[1]+=0.1;
			break;
		case GLUT_KEY_PAGE_DOWN:
			eye[1]-=0.1;
			break;
	}
}

void Motion(int x, int y)
{
	if(y>400)
	{
		if(x>30 && x<230)
			width = (x-30)/200.0;
		if(x>280 && x<320 && y>440 && y<560)
			height = 1-(y-440)/120.0;
		if(x>360 && x<570)
			angle =2*PI* (x-360)/210.0;

	}

}

void main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("EXAM");

	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMotionFunc(Motion);
	glutSpecialFunc(SpecialKeys);

	init();
	glutMainLoop();
}