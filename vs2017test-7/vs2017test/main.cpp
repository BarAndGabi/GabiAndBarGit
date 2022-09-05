#include "glut.h"
#include <math.h>

const int W = 600;
const int H = 600;
const double PI = 3.14;

double angle = 0;
double eyex = 2, eyey = 10, eyez=10;
double dx = 0, dy = 0, dz = 0; // speed in each direction
double dirx, diry, dirz;
double speed=0, angular_speed=0;
double sight_angle = PI;

void init()
{
	glClearColor(0.3, 0.6, 0.8, 0);// color of window background

}

void DrawFloor()
{
	glColor3d(0,0,0);
	for (int i = -10; i <= 10; i++)
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


void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT); // clean frame buffer and z-buffer

	glMatrixMode(GL_PROJECTION); // here we define working matrices of PROJECTIONS

	glLoadIdentity(); // start transformations here
	glFrustum(-1, 1, -1, 1, 1, 300);

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
	angle += 0.1;

	// simple motion
/*	eyex += dx;
	eyey += dy;
	eyez += dz;
	*/
	sight_angle += angular_speed;

	dirx = sin(sight_angle);
	diry = 0;
	dirz = cos(sight_angle);
	eyex += speed * dirx;
	eyez += speed * dirz;

	glutPostRedisplay(); // sends a message to the window to run display function
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
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