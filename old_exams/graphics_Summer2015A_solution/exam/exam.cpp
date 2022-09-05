#include "glut.h"
#include <math.h>
#include <time.h>

const double PI = 4*atan(1.0);
const int TH = 256;
const int TV = 256;

double eyex=1,eyey=8,eyez=8;
int cut_angle=180;
int show_angle=180;
int show,cut,height;
int show_low = 350,show_top = 580;
int cut_low = 20,cut_top = 250;
int knife_height = 100,height_low=20,height_top=80;
int start_angle=20, stop_angle = 322;
bool start=false,stop = false;
bool start_down=false,stop_down = false;
double offset=0;

unsigned char tx1[TV][TH][4]; // texture 1

void CreateTexture(int num);

void init()
{
	glClearColor(0.4,0.4,0.6,0);
	glEnable(GL_DEPTH_TEST);

		// setup textures
	CreateTexture(1);
	glBindTexture(GL_TEXTURE_2D,1);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,TH,TV,0,GL_RGBA, 
		GL_UNSIGNED_BYTE,tx1);

}

void CreateTexture(int num)
{
	int i,j,c;
	switch(num)
	{
	case 1: // road
		for(i=0;i<TV;i++)
			for(j=0;j<TH;j++)
			{
				c = (i/50)%2;
				if(c%2==0 && rand()%10>0) 
				{
				tx1[i][j][0] = 250;
				tx1[i][j][1] = 220;
				tx1[i][j][2] = 220;
				tx1[i][j][3] = 0;
				}
				else
				{
				tx1[i][j][0] = 100;
				tx1[i][j][1] = 70;
				tx1[i][j][2] = 0;
				tx1[i][j][3] = 0;
				}
			}
		break;
	}
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
					glColor3d(0.7,0.5,0.2);
			glVertex3d(topr*sin(alpha),1,topr*cos(alpha));
			glVertex3d(topr*sin(alpha+teta),1,topr*cos(alpha+teta));
					glColor3d(0.4,0.3,0);
			glVertex3d(bottomr*sin(alpha+teta),0,bottomr*cos(alpha+teta));
			glVertex3d(bottomr*sin(alpha),0,bottomr*cos(alpha));
		glEnd();
	}
}

void DrawCilynder2(int n, double topr, double bottomr,double start, double stop)
{
	double alpha,teta;

	teta = 2*PI/n;

	if(stop<start)
		stop+=2*PI;

	for(alpha = start; alpha<stop;alpha+=teta)
	{
		glBegin(GL_POLYGON);
					glColor3d(0.7,0.5,0.2);
			glVertex3d(topr*sin(alpha),1,topr*cos(alpha));
			glVertex3d(topr*sin(alpha+teta),1,topr*cos(alpha+teta));
					glColor3d(0.4,0.3,0);
			glVertex3d(bottomr*sin(alpha+teta),0,bottomr*cos(alpha+teta));
			glVertex3d(bottomr*sin(alpha),0,bottomr*cos(alpha));
		glEnd();
	}
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,1); // using texture 1
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
	glBegin(GL_POLYGON);
		glTexCoord2d(0,0);    glVertex3d(0,1,0);
		glTexCoord2d(1,0);    		glVertex3d(topr*sin(start),1,topr*cos(start));
		glTexCoord2d(1,1);    		glVertex3d(bottomr*sin(start),0,bottomr*cos(start));
		glTexCoord2d(0,1);    		glVertex3d(0,0,0);
	glEnd();
	glBegin(GL_POLYGON);
		glTexCoord2d(0,0);		 glVertex3d(0,1,0);
		glTexCoord2d(1,0);    		glVertex3d(topr*sin(stop),1,topr*cos(stop));
		glTexCoord2d(1,1);    		glVertex3d(bottomr*sin(stop),0,bottomr*cos(stop));
		glTexCoord2d(0,1);    		glVertex3d(0,0,0);
	glEnd();
	glDisable(GL_TEXTURE_2D);

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


void DrawCake()
{
	int ang = (stop_angle+start_angle)/2;
	bool small_piece = false;
	if(stop_angle > start_angle)
		small_piece = true;
	if(!stop)
		DrawCilynder1(80,1,1);
	else 
	{
		if(!small_piece)
		{
		DrawCilynder2(80,1,1,   start_angle*PI/180,stop_angle*PI/180);
		glPushMatrix();
			glTranslated(sin(ang*PI/180),0,cos(ang*PI/180));
			DrawCilynder2(80,1,1,stop_angle*PI/180,start_angle*PI/180);
		glPopMatrix();
		}
		else
		{
			DrawCilynder2(80,1,1,stop_angle*PI/180,start_angle*PI/180);
		glPushMatrix();
			glTranslated(sin(ang*PI/180),0,cos(ang*PI/180));
		DrawCilynder2(80,1,1,   start_angle*PI/180,stop_angle*PI/180);
		glPopMatrix();
		}
	}
	glPushMatrix();
		glTranslated(0,1,0);
		glScaled(1,0,1);
		if(!stop)	DrawCilynder1(80,0,1);
		else 
		{
			if(!small_piece)
			{
			DrawCilynder2(80,0,1,start_angle*PI/180,stop_angle*PI/180);
				glPushMatrix();
			glTranslated(sin(ang*PI/180),0,cos(ang*PI/180));
			DrawCilynder2(80,0,1,stop_angle*PI/180,start_angle*PI/180);
			}
			else
			{
			DrawCilynder2(80,0,1,stop_angle*PI/180,start_angle*PI/180);
				glPushMatrix();
			glTranslated(sin(ang*PI/180),0,cos(ang*PI/180));
			DrawCilynder2(80,0,1,start_angle*PI/180,stop_angle*PI/180);
			}
		glPopMatrix();
	}

	glPopMatrix();
	glPushMatrix();
		glScaled(1,0,1);
		if(!stop)	DrawCilynder1(80,0,1);
		else 
		{
			if(!small_piece)
			{
		DrawCilynder2(80,0,1,start_angle*PI/180,stop_angle*PI/180);
				glPushMatrix();
			glTranslated(sin(ang*PI/180),0,cos(ang*PI/180));
			DrawCilynder2(80,0,1,stop_angle*PI/180,start_angle*PI/180);
			}
			else
			{
			DrawCilynder2(80,0,1,stop_angle*PI/180,start_angle*PI/180);
			glTranslated(sin(ang*PI/180),0,cos(ang*PI/180));
				glPushMatrix();
		DrawCilynder2(80,0,1,start_angle*PI/180,stop_angle*PI/180);
			}
		glPopMatrix();
	}

	glPopMatrix();

}

void DrawControls()
{

	glDisable(GL_DEPTH_TEST);
	glLoadIdentity();
	glOrtho(0,600,0,100,-1,1);

	glColor3d(0.8,0.8,0.8);
	glBegin(GL_POLYGON);
		glVertex2d(0,0);
		glVertex2d(0,97);
		glVertex2d(600,97);
		glVertex2d(600,0);
	glEnd();

	// controls
	glLineWidth(2);
	glColor3d(0.4,0.3,0.6);
	glBegin(GL_LINES);
		glVertex2d(cut_low,50);
		glVertex2d(cut_top,50);
		glVertex2d(show_low,50);
		glVertex2d(show_top,50);
		glVertex2d(300,height_low);
		glVertex2d(300,height_top);
	glEnd();

	// show control
	glColor3d(1,0,0.7);
	show = show_low+(show_top-show_low)*(show_angle/360.0);
	glBegin(GL_POLYGON);
		glVertex2d(show-5,45);
		glVertex2d(show+5,45);
		glVertex2d(show,60);
	glEnd();
	// cut control
	glColor3d(1,0,0.7);
	cut = cut_low+(cut_top-cut_low)*(cut_angle/360.0);
	glBegin(GL_POLYGON);
		glVertex2d(cut-5,45);
		glVertex2d(cut+5,45);
		glVertex2d(cut,60);
	glEnd();
	// height control
	glColor3d(1,0,0.7);
	height = height_low+(height_top-height_low)*(knife_height/100.0);
	glBegin(GL_POLYGON);
		glVertex2d(290,height);
		glVertex2d(305,height+5);
		glVertex2d(305,height-5);
	glEnd();


}


void DrawKnife()
{
	glPushMatrix();
		glScaled(1.4,1,1);


	glColor3d(0.7,0.7,0.7);	
	glBegin(GL_POLYGON);
		glVertex3d(0,0,0);
		glVertex3d(0,2,0);
		glVertex3d(4,2,0);
		glVertex3d(4,0,0);
	glEnd();
	
	glPushMatrix();
		glTranslated(3.5,1.5,0);
		glRotated(-90,0,0,1);
		glScaled(0.7,3,0.3);
		DrawCilynder1(20,0.5,1);
		
		glTranslated(0,1,0);
		glScaled(1,0.05,1);
		DrawCilynder1(20,0,0.5);
	glPopMatrix();
		glPopMatrix();
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glViewport(0,100,600,500);
	glLoadIdentity();

	glFrustum(-1,1,-1,1,0.7,200);
	gluLookAt(eyex,eyey,eyez, 	0,4,0, 	0,1,0); 

	glPushMatrix();
		glScaled(5,5,5);
		glRotated(show_angle,0,1,0);
		DrawCake();
	glPopMatrix();

	glPushMatrix();
	glTranslated(0,knife_height/15.0,0);
	glRotated(cut_angle+show_angle,0,1,0);
		DrawKnife();
	glPopMatrix();

	glViewport(0,0,600,100);

	DrawControls();

	glutSwapBuffers();
}

void idle()
{

	if(stop)
		offset+=0.01;
	glutPostRedisplay();
}

void motion(int x, int y)
{
	if(x>=show-5 && x<=show+5 && (600-y) >= 45 && (600-y)<=60)
	{
		show_angle = (x-show_low)*360.0/(show_top-show_low);

		if(show_angle<0)
			show_angle = 0;
		else if(show_angle>360)
			show_angle=360;
	}
	else if(x>=cut-5 && x<=cut+5 && (600-y) >= 45 && (600-y)<=60)
	{
		cut_angle = (x-cut_low)*360.0/(cut_top-cut_low);

		if(cut_angle<0)
			cut_angle = 0;
		else if(cut_angle>360)
			cut_angle=360;
	}
	else if(x>= 290 && x<=305 &&  (600-y)>=height-5 &&  (600-y)<= height+5 )
	{
		height = 600-y;
		knife_height =  ((600-y)-height_low)*100.0/(height_top-height_low);

		if(!start_down && knife_height<90)
			start_down = true;
		if(start && knife_height<90)
			stop_down=true;
		if(knife_height<0) 
		{
				knife_height =0;
				if(start_down && !start)
					start_angle = cut_angle+90;
				else if(stop_down && start)
					stop_angle = cut_angle+90;
		}
		else if(knife_height>100)
		{
				knife_height = 100;
				if(start_down && !start)
					start=true;
				else if(stop_down && !stop)
					stop=true;
		}
		
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
	glutMotionFunc(motion);
	
	init();
	glutMainLoop();
}
