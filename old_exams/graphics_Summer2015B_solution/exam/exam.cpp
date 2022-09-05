#include "glut.h"
#include <math.h>
#include <time.h>

const double PI = 4*atan(1.0);
const int MAX_POINTS=100;
double points[MAX_POINTS][2];
int npoints=0;

double eyex=1,eyey=4,eyez=12;
double offset =0;

void init()
{
	glClearColor(0.4,0.4,0.4,0);
}

void DrawCilynder(int n)
{
	double alpha,teta;

	teta = 2*PI/n;

	for(alpha = 0; alpha<2*PI;alpha+=teta)
	{
		glBegin(GL_POLYGON);
					glColor3d(fabs(sin(alpha)),fabs(cos(alpha)),(1+sin(alpha*3))/2);
			glVertex3d(sin(alpha),1,cos(alpha));
					glColor3d(fabs(cos(alpha-teta)),fabs(sin(alpha-teta)),(1+sin((alpha-teta)*3))/2);
			glVertex3d(sin(alpha+teta),1,cos(alpha+teta));
					glColor3d(fabs(cos(alpha-teta)),fabs(sin(alpha-teta)),(1+sin((alpha-teta)*3))/2);
		glVertex3d(sin(alpha+teta),0,cos(alpha+teta));
				glColor3d(fabs(sin(alpha)),fabs(cos(alpha)),(1+sin(alpha*3))/2);
		glVertex3d(sin(alpha),0,cos(alpha));
		glEnd();
	}
}
void DrawCilynder1(int n, double topr, double bottomr)
{
	double alpha,teta;

	teta = 2*PI/n;

	for(alpha = 0; alpha<2*PI;alpha+=teta)
	{
		glBegin(GL_POLYGON);
					glColor3d(fabs(sin(alpha)),fabs(cos(alpha)),(1+sin(alpha*3))/2);
			glVertex3d(topr*sin(alpha),1,topr*cos(alpha));
					glColor3d(1-fabs(sin(alpha))/2,fabs(cos(alpha))/2,fabs(1-sin(alpha*3))/2);
			glVertex3d(topr*sin(alpha+teta),1,topr*cos(alpha+teta));
					glColor3d(1-fabs(sin(alpha)),fabs(cos(alpha)),fabs(1-sin(alpha*3)));
			glVertex3d(bottomr*sin(alpha+teta),0,bottomr*cos(alpha+teta));
					glColor3d(0,fabs(cos(alpha-teta)),fabs(sin(alpha-teta)));
			glVertex3d(bottomr*sin(alpha),0,bottomr*cos(alpha));
		glEnd();
	}
}

void DrawSphere(int sectors, int slices)
{
	double phi = PI/slices,beta;
	double tr,br; // topr, bottomr
	double height;

	for(beta=-PI/2;beta<PI/2;beta+=phi)
	{
		br = cos(beta);
		tr = cos(beta+phi);
		height = fabs(sin(beta)-sin(beta+phi));
		glPushMatrix();
			glTranslated(0,sin(beta),0);
			glScaled(1,height,1);
			DrawCilynder1(sectors,tr,br);
		glPopMatrix();
	}
}

void Draw3DShape()
{	
	int i;
	double height=0;
	
	for(i=1;i<npoints;i++)
	{
	glPushMatrix();
		height += (points[i-1][1] - points[i][1]);
			glTranslated(0,-height,0);
			glScaled(1,points[i-1][1] - points[i][1],1);
			DrawCilynder1(40,points[i-1][0],points[i][0]);
	glPopMatrix();

	}


}
void Draw2DShape()
{	
	int i;

		glColor3d(0.5,0.5,0.7);
	glBegin(GL_POLYGON);
		glVertex2d(-1,-1);
		glVertex2d(-1,1);
		glVertex2d(1,1);
		glVertex2d(1,-1);
	glEnd();

	glColor3d(1,1,1);
	glBegin(GL_LINES);
		glVertex2d(0,1);
		glVertex2d(0,-1);
	glEnd();
	
	glPointSize(5);
	glColor3d(1,0,0);
	glBegin(GL_POINTS);
	for(i=0;i<npoints;i++)
	{
		glVertex2d(points[i][0],points[i][1]);
	}
	glEnd();
	glBegin(GL_POINTS);

	for(i=0;i<npoints;i++)
	{
		glVertex2d(-points[i][0],points[i][1]);
	}
	glEnd();

	glColor3d(1,1,0);
	glBegin(GL_LINE_STRIP);
	for(i=0;i<npoints;i++)
	{
		glVertex2d(points[i][0],points[i][1]);
	}
	glEnd();
	glBegin(GL_LINE_STRIP);
	for(i=0;i<npoints;i++)
	{
		glVertex2d(-points[i][0],points[i][1]);
	}
	glEnd();

}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0,0,300,600);
	glLoadIdentity();

	glFrustum(-1,1,-1,1,0.7,200);
	gluLookAt(eyex,eyey,eyez, 	0,2,0, 	0,1,0); 

	glPushMatrix();
	glRotated(offset,0,1,0);
	glTranslated(0,2,0);
	glScaled(6,3,6);
	Draw3DShape();
	glPopMatrix();

	//-------------------------------------------------------------------------------------------- 2D
	glDisable(GL_DEPTH_TEST);
	glViewport(300,0,300,600);
	glLoadIdentity();
	glOrtho(-1,1,-1,1,-1,1);
	Draw2DShape();
	glutSwapBuffers();
}

void idle()
{
	offset+=0.1;
	glutPostRedisplay();
}

void mouse(int button,int state,int x,int y)
{
	if(button==GLUT_LEFT_BUTTON && state == GLUT_DOWN && x>300 && npoints<MAX_POINTS) // add new point
	{
		points[npoints][0] = (x-450)/150.0;
		points[npoints][1] = ((600-y)-300)/300.0;
		npoints++;
	}
}


void main(int argc, char* argv[])
{
	glutInit(&argc,argv);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	glutInitWindowSize(600,600);
	glutInitWindowPosition(100,100);
	glutCreateWindow("exam");

	glutDisplayFunc(display);
	glutIdleFunc(idle);

	glutMouseFunc(mouse);
	
	init();
	glutMainLoop();
}
