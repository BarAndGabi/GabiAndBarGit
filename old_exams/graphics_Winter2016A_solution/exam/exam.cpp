#include <math.h>
#include "GLUT.h"
#include <time.h>
#include <stdio.h>

const int WIDTH = 600;
const int HEIGHT = 600;
const double PI = 4*atan(1.0);
const int GSIZE = 200;
const int TSIZE = 256;


double ground[GSIZE][GSIZE] = {0};
unsigned char pix[GSIZE][GSIZE][3]; // red, green, blue

double offset=0;
double eyex=2,eyey=18,eyez=35;
double dz = 0, dx=0,dy=0;
double speed = 0;
double dirx=0,diry=0,dirz=-1;
double sight_angle = PI;

unsigned char tx0[TSIZE][TSIZE][4]; 
unsigned char tx1[TSIZE][TSIZE][4]; 
unsigned char tx2[TSIZE][TSIZE][4]; 
unsigned char tx3[256][256][4]; // wall
unsigned char tx4[128][128][4]; // castle wall

unsigned char* bmp;

const int MAX_TOWERS = 20;
int num_towers = 0;
typedef struct 
{
	int row;
	int col;
	int height;
	int sides;
} TOWER;

TOWER all_towers[MAX_TOWERS];


void UpdateTerrain2();
void UpdateTerrain3();
void Smooth();
void SetColorMap(int i,int j);

void LoadBitmap(char *fname)
{
	FILE* pf;
	BITMAPFILEHEADER bf;
	BITMAPINFOHEADER bi;
	int sz;

	pf = fopen(fname,"rb");
	fread(&bf,sizeof(BITMAPFILEHEADER),1,pf);
	fread(&bi,sizeof(BITMAPINFOHEADER),1,pf);

	sz = bi.biHeight*bi.biWidth*3;
	bmp = (unsigned char*) malloc(sz);

	fread(bmp,1,sz,pf);

	fclose(pf);
}


void SetTexture(int tnum)
{
	int i,j;
	int r;
	switch(tnum)
	{
	case 0: // road
			for(i=0;i<TSIZE;i++)
				for(j=0;j<TSIZE;j++)
				{
					r=rand()%55;
					if(i<5||i>TSIZE-5 || 
						i>TSIZE/2-5 && i<TSIZE/2+5 && j<TSIZE/2) // yellow
					{
					tx0[i][j][0] = 200+r; // red
					tx0[i][j][1] = 200+r; // green
					tx0[i][j][2] = 0; // blue
					tx0[i][j][3] = 0; // red
					}
					else
					{
					tx0[i][j][0] = 130+r; // red
					tx0[i][j][1] = 130+r; // green
					tx0[i][j][2] = 130+r; // blue
					tx0[i][j][3] = 0; // red
					}
				}
		break;
	case 1: // crossroad
			for(i=0;i<TSIZE;i++)
				for(j=0;j<TSIZE;j++)
				{
					r=rand()%55;
					tx1[i][j][0] = 130+r; // red
					tx1[i][j][1] = 130+r; // green
					tx1[i][j][2] = 130+r; // blue
					tx1[i][j][3] = 0; // red
				}
		break;
	case 2: // crossing
			for(i=0;i<TSIZE;i++)
				for(j=0;j<TSIZE;j++)
				{

					r=rand()%55;
					if(i<TSIZE/2)
					{
					tx2[i][j][0] = 130+r; // red
					tx2[i][j][1] = 130+r; // green
					tx2[i][j][2] = 130+r; // blue
					tx2[i][j][3] = 0; // red
					}
					else
					{
					tx2[i][j][0] = 200+r; // red
					tx2[i][j][1] = 200+r; // green
					tx2[i][j][2] = 200+r; // blue
					tx2[i][j][3] = 0; // red
					}
				}
		break;
	case 3: // door
			for(i=0;i<256;i++)
				for(j=0;j<256;j++)
				{
					tx3[255-i][j][0] = bmp[3*(256*i+j)+2]; // red
					tx3[255-i][j][1] = bmp[3*(256*i+j)+1]; // green
					tx3[255-i][j][2] = bmp[3*(256*i+j)]; // blue
					tx3[255-i][j][3] = 0; // alpha
				}
		break;
	case 4: // castle wall from file
			for(i=0;i<128;i++)
				for(j=0;j<128;j++)
				{
					tx4[127-i][j][0] = bmp[3*(128*i+j)+2]; // red
					tx4[127-i][j][1] = bmp[3*(128*i+j)+1]; // green
					tx4[127-i][j][2] = bmp[3*(128*i+j)]; // blue
					tx4[127-i][j][3] = 0; // alpha
				}
		break;
	}
}

void init()
{
	int i,j;
	glClearColor(0.7,0.7,1,1);
	glEnable(GL_DEPTH_TEST); // set objects by their depth
	srand(time(0));

	for(int i=1;i<700;i++)
	UpdateTerrain2();
		for(int i=1;i<200;i++)
	UpdateTerrain3();

	Smooth();

	// setup map
	for(i=0;i<GSIZE;i++)
		for(j=0;j<GSIZE;j++)
			SetColorMap(i,j);

	// textures
	SetTexture(0); // road
	glBindTexture(GL_TEXTURE_2D,0);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,TSIZE,TSIZE,0,GL_RGBA,
		GL_UNSIGNED_BYTE,tx0);

	SetTexture(1); // crossroad
	glBindTexture(GL_TEXTURE_2D,1);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,TSIZE,TSIZE,0,GL_RGBA,
		GL_UNSIGNED_BYTE,tx1);

	SetTexture(2); // crossing
	glBindTexture(GL_TEXTURE_2D,2);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,TSIZE,TSIZE,0,GL_RGBA,
		GL_UNSIGNED_BYTE,tx2);

	LoadBitmap("door.bmp");
	SetTexture(3); // castle door
	glBindTexture(GL_TEXTURE_2D,3);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,256,256,0,GL_RGBA,
		GL_UNSIGNED_BYTE,tx3);

	LoadBitmap("stone-wall1.bmp");
	SetTexture(4); // castle wall
	glBindTexture(GL_TEXTURE_2D,4);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
	glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,128,128,0,GL_RGBA,
		GL_UNSIGNED_BYTE,tx4);

}



void SetColorMap(int i,int j)
{
	double x = ground[GSIZE-i-1][j]/3;

	if(x<0) // water
	{
		pix[i][j][0] = 0;
		pix[i][j][1] = 100;
		pix[i][j][2] = 180;
	}
	else
	{
	if(x>1) // snow
	{
		if(x>2)
		{
		pix[i][j][0] = 255;
		pix[i][j][1] = 255;
		pix[i][j][2] = 255;
		}
		else
		{
		pix[i][j][0] = 255*x/2;
		pix[i][j][1] = 255*x/2;
		pix[i][j][2] = 255*x/2;
		}
	}
	else if(x<0.1) // sand
	{
		pix[i][j][0] = 255;
		pix[i][j][1] = 240;
		pix[i][j][2] = 220;
	}

	else
	{
		pix[i][j][0] = 255*(0.2+0.3*x);
		pix[i][j][1] = 255*(0.8-0.4*x);
		pix[i][j][2] = 0;
	}

	}
}

void Smooth()
{
	int i,j;
	double tmp[GSIZE][GSIZE];

	for(i=1;i<GSIZE-1;i++)
		for(j=1;j<GSIZE-1;j++)
			tmp[i][j] = (ground[i-1][j-1]+2*ground[i-1][j]+ground[i-1][j+1]+
								2*ground[i][j-1]+4*ground[i][j]+2*ground[i][j+1]+
								ground[i+1][j-1]+2*ground[i+1][j]+ground[i+1][j+1])/16;

	for(i=1;i<GSIZE-1;i++)
		for(j=1;j<GSIZE-1;j++)
			ground[i][j] = tmp[i][j];

}

void UpdateTerrain1()
{
	int i,j;

	for(i=0;i<GSIZE;i++)
		for(j=0;j<GSIZE;j++)
			ground[i][j] = -5+rand()%10;
}

void UpdateTerrain2()
{
	int i,j;
	int x1,x2,y1,y2;
	double a,b;
	double delta = 0.1;

	x1 = rand() % GSIZE;
	y1 = rand() % GSIZE;
	x2 = rand() % GSIZE;
	y2 = rand() % GSIZE;

	if(x2!=x1)
	{
		a = ((double)y2-y1)/(x2-x1);
		b = y1-a*x1;
		if(rand()%2 == 1) delta = -delta;

	for(i=0;i<GSIZE;i++)
		for(j=0;j<GSIZE;j++)
			if(i>a*j+b)
				ground[i][j] += delta;
			else
				ground[i][j] -= delta;
	}
}

void UpdateTerrain3()
{
	int x,y;
	int n = 1200;
	double delta = 0.06;
	if(rand()%2==0) delta = -delta;
	x = rand()%GSIZE;
	y = rand()%GSIZE;
	while(n>0)
	{
		n--;
		ground[y][x]+=delta;
		// choose direction
		switch(rand()%4)
		{
		case 0: // go left
			x--;
			break;
		case 1: // go right
			x++;
			break;
		case 2: // go down
			y--;
			break;
		case 3: // go up
			y++;
			break;
		}
		// check borders
		x+=GSIZE;
		x= x%GSIZE;
		y+=GSIZE;
		y= y%GSIZE;
	}
}
void SetColor(double h)
{
	double x =fabs( (h)/3);

	if(fabs(x)>1) // snow
	{
		glColor3d((x)/2,x/2,x/1.5);
	}
	else if(x<0.1)
		glColor3d(1,1,0.8);

	else
		glColor3d(0.2+0.3*(x),0.8-0.4*(x),0);
}

void SetColorMap(double h)
{
	double x =fabs( (h)/3);

	if(fabs(x)>1) // snow
	{
		glColor3d((x)/2,x/2,x/1.5);
	}
	else if(x<0.1)
		glColor3d(1,1,0.8);

	else
		glColor3d(0.2+0.3*(x),0.8-0.4*(x),0);
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
			glVertex3d(topr*sin(alpha+teta),1,topr*cos(alpha+teta));
					glColor3d(0,fabs(cos(alpha-teta)),fabs(sin(alpha-teta)));
			glVertex3d(bottomr*sin(alpha+teta),0,bottomr*cos(alpha+teta));
			glVertex3d(bottomr*sin(alpha),0,bottomr*cos(alpha));
		glEnd();
	}
}

// horiz_rep - amount of textures horizontally per cilynder
void DrawTexCilynder1(int n,double topr, double bottomr,int tnum, int horiz_rep,
	int vert_rep)
{
	double teta = 2*PI/n;
	double alpha;
	int c;
	double part = horiz_rep/(double)n;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tnum);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE); // gl_modulate for lighting


	for(alpha = 0,c=0; alpha<2*PI;alpha+=teta,c++)
	{

		if(alpha<PI/2 || alpha>3*PI/2 )
			glColor3d(0.5+0.5*cos(alpha),0.5+0.5*cos(alpha),0.5+0.5*cos(alpha));
		else 
			glColor3d(0.5,0.5,0.5);

//			glNormal3d(sin(alpha),tan(bottomr-topr),cos(alpha));
		glBegin(GL_POLYGON);
if(topr!=0)
{
		glTexCoord2d(c*part,0);
			glVertex3d(topr*sin(alpha),1,topr*cos(alpha)); // 1
//			glNormal3d(sin(alpha+teta),tan(bottomr-topr),cos(alpha+teta));
		glTexCoord2d((c+1)*part,0);
			glVertex3d(topr*sin(alpha+teta),1,topr*cos(alpha+teta)); // 2
}		
else
{
			glTexCoord2d(c*part+0.5,0);
			glVertex3d(0,1,0); // 1
}
			glTexCoord2d((c+1)*part,vert_rep);
			glVertex3d(bottomr*sin(alpha+teta),0,bottomr*cos(alpha+teta)); // 3
//			glNormal3d(sin(alpha),tan(bottomr-topr),cos(alpha));

		glTexCoord2d(c*part,vert_rep);
			glVertex3d(bottomr*sin(alpha),0,bottomr*cos(alpha)); // 4
		glEnd();
	}
	glDisable(GL_TEXTURE_2D);

}	
// n must be 4
void DrawEntrance(int n,double topr, double bottomr,int tnum, int horiz_rep,
	int vert_rep)
{
	double teta = 2*PI/n;
	double alpha;
	int c;
	double part = horiz_rep/(double)n;

	glEnable(GL_TEXTURE_2D);


	for(alpha = 0,c=0; alpha<2*PI;alpha+=teta,c++)
	{

		if(alpha<PI/2 || alpha>3*PI/2 )
			glColor3d(0.5+0.5*cos(alpha),0.5+0.5*cos(alpha),0.5+0.5*cos(alpha));
		else 
			glColor3d(0.5,0.5,0.5);
		
		if(c%2==1)
		{
	glBindTexture(GL_TEXTURE_2D,tnum);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE); // gl_modulate for lighting

	glBegin(GL_POLYGON);
		glTexCoord2d(c*part,0);
			glVertex3d(topr*sin(alpha),1,topr*cos(alpha)); // 1
		glTexCoord2d((c+1)*part,0);
			glVertex3d(topr*sin(alpha+teta/3),1,topr*cos(alpha+teta/3)); // 2
		glTexCoord2d((c+1)*part,vert_rep);
			glVertex3d(bottomr*sin(alpha+teta/3),0,bottomr*cos(alpha+teta/3)); // 3
		glTexCoord2d(c*part,vert_rep);
			glVertex3d(bottomr*sin(alpha),0,bottomr*cos(alpha)); // 4
	glEnd();
// door

	glBindTexture(GL_TEXTURE_2D,3);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE); // gl_modulate for lighting

	glBegin(GL_POLYGON);
		glTexCoord2d(0,0);
			glVertex3d(topr*sin(alpha+teta/3),1,topr*cos(alpha+teta/3)); // 2
		glTexCoord2d(1,0);
			glVertex3d(topr*sin(alpha+2*teta/3),1,topr*cos(alpha+2*teta/3)); // 2
		glTexCoord2d(1,1);
			glVertex3d(bottomr*sin(alpha+2*teta/3),0,bottomr*cos(alpha+2*teta/3)); // 3
		glTexCoord2d(0,1);
			glVertex3d(bottomr*sin(alpha+teta/3),0,bottomr*cos(alpha+teta/3)); // 4
	glEnd();

	glBindTexture(GL_TEXTURE_2D,tnum);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE); // gl_modulate for lighting

		glBegin(GL_POLYGON);
		glTexCoord2d(c*part,0);
			glVertex3d(topr*sin(alpha+2*teta/3),1,topr*cos(alpha+2*teta/3)); // 1
		glTexCoord2d((c+1)*part,0);
			glVertex3d(topr*sin(alpha+teta),1,topr*cos(alpha+teta)); // 2
		glTexCoord2d((c+1)*part,vert_rep);
			glVertex3d(bottomr*sin(alpha+teta),0,bottomr*cos(alpha+teta)); // 3
		glTexCoord2d(c*part,vert_rep);
			glVertex3d(bottomr*sin(alpha+2*teta/3),0,bottomr*cos(alpha+2*teta/3)); // 4
		glEnd();
		}
		else
		{
		glBegin(GL_POLYGON);
		glTexCoord2d(c*part,0);
			glVertex3d(topr*sin(alpha),1,topr*cos(alpha)); // 1
		glTexCoord2d((c+1)*part,0);
			glVertex3d(topr*sin(alpha+teta),1,topr*cos(alpha+teta)); // 2
		glTexCoord2d((c+1)*part,vert_rep);
			glVertex3d(bottomr*sin(alpha+teta),0,bottomr*cos(alpha+teta)); // 3
		glTexCoord2d(c*part,vert_rep);
			glVertex3d(bottomr*sin(alpha),0,bottomr*cos(alpha)); // 4
		glEnd();
		}
	}
	glDisable(GL_TEXTURE_2D);

}		
void DrawTopTower(int n,double topr, double bottomr,int tnum, int horiz_rep,
	int vert_rep)
{
	double teta = 2*PI/n;
	double alpha;
	int c;
	double part = horiz_rep/(double)n;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,tnum);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE); // gl_modulate for lighting


	for(alpha = 0,c=0; alpha<2*PI;alpha+=teta,c++)
	{
		if(alpha<PI/2 || alpha>3*PI/2 )
			glColor3d(0.3+0.5*cos(alpha),0.3+0.5*cos(alpha),0.3+0.5*cos(alpha));
		else 
			glColor3d(0.3,0.3,0.3);
//			glNormal3d(sin(alpha),tan(bottomr-topr),cos(alpha));
		glBegin(GL_POLYGON);
		glTexCoord2d(c*part,0);
			glVertex3d(topr*sin(alpha),1+0.5*(c%2),topr*cos(alpha)); // 1
//			glNormal3d(sin(alpha+teta),tan(bottomr-topr),cos(alpha+teta));
		glTexCoord2d((c+1)*part,0);
			glVertex3d(topr*sin(alpha+teta),1+0.5*(c%2),topr*cos(alpha+teta)); // 2
			glTexCoord2d((c+1)*part,vert_rep);
			glVertex3d(bottomr*sin(alpha+teta),0,bottomr*cos(alpha+teta)); // 3
//			glNormal3d(sin(alpha),tan(bottomr-topr),cos(alpha));

		glTexCoord2d(c*part,vert_rep);
			glVertex3d(bottomr*sin(alpha),0,bottomr*cos(alpha)); // 4
		glEnd();
	}

	for(alpha = 0,c=0; alpha<2*PI;alpha+=teta,c++)
	{
			glColor3d(0.5,0.5,0.5);
//			glNormal3d(sin(alpha),tan(bottomr-topr),cos(alpha));
		glBegin(GL_POLYGON);
		glTexCoord2d(c*part,0);
			glVertex3d(0,0.5,0); // 1
//			glNormal3d(sin(alpha+teta),tan(bottomr-topr),cos(alpha+teta));
		glTexCoord2d((c+1)*part,0);
			glVertex3d(0,0.5,0); // 2
			glTexCoord2d((c+1)*part,vert_rep);
			glVertex3d(bottomr*sin(alpha+teta),0.5,bottomr*cos(alpha+teta)); // 3
//			glNormal3d(sin(alpha),tan(bottomr-topr),cos(alpha));

		glTexCoord2d(c*part,vert_rep);
			glVertex3d(bottomr*sin(alpha),0.5,bottomr*cos(alpha)); // 4
		glEnd();
	}
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


void DrawFloor()
{
	int i,j;
	double len;

	glColor3d(1,1,0.7);

	for(i=2;i<GSIZE;i++)
		for(j=2;j<GSIZE;j++)
		{

			glBegin(GL_POLYGON);
			SetColor(ground[i][j]);
		glVertex3d(j-GSIZE/2,ground[i][j],i-GSIZE/2);
			SetColor(ground[i][j-1]);
		glVertex3d(j-GSIZE/2-1,ground[i][j-1],i-GSIZE/2);
			SetColor(ground[i-1][j-1]);
		glVertex3d(j-GSIZE/2-1,ground[i-1][j-1],i-GSIZE/2-1);
			SetColor(ground[i-1][j]);
		glVertex3d(j-GSIZE/2,ground[i-1][j],i-GSIZE/2-1);
	glEnd();
		}
		// water
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4d(0,0.5,0.95,0.7);
		glBegin(GL_POLYGON);
			glVertex3d(-GSIZE/2,0,-GSIZE/2);
			glVertex3d(GSIZE/2,0,-GSIZE/2);
			glVertex3d(GSIZE/2,0,GSIZE/2);
			glVertex3d(-GSIZE/2,0,GSIZE/2);
		glEnd();
		glDisable(GL_BLEND);
}


void AddTower(int x,int y)
{
	if(num_towers<MAX_TOWERS)
	{
	all_towers[num_towers].col = x;
	all_towers[num_towers].row = y;
	all_towers[num_towers].height = 4;
	all_towers[num_towers].sides = 20;
	num_towers++;
	}
}

void DrawGates()
{
	// gates
	double mid[3];
	double gamma;

	if(num_towers>2)
	{
	mid[0] = (all_towers[0].col+ all_towers[num_towers-1].col)/2.0;
	mid[2] = (all_towers[0].row+ all_towers[num_towers-1].row)/2.0;
	mid[1] = (ground[all_towers[0].row][all_towers[0].col]+
		ground[all_towers[num_towers-1].row][all_towers[num_towers-1].col])/2.0; 
	gamma = atan(-(all_towers[0].row- all_towers[num_towers-1].row)/(double)(all_towers[0].col- all_towers[num_towers-1].col));
		glPushMatrix();
		glTranslated(mid[0]-GSIZE/2,mid[1],mid[2]-GSIZE/2);
			glScaled(2,5,2);
			glRotated(45+gamma*180/PI,0,1,0);
//			DrawTexCilynder1(4,1,1,4,4,2);
			DrawEntrance(4,1,1,4,4,2);
		glPopMatrix();


	// roof
	glPushMatrix();
		glTranslated(mid[0]-GSIZE/2,4+mid[1],mid[2]-GSIZE/2);
		glScaled(2,2,2);
			glRotated(45+gamma*180/PI,0,1,0);
		DrawTopTower(24,1.1,1.1,4,24,2);
	glPopMatrix();
	}

}

void DrawWalls()
{
	int i;

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,4);
	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

	for(i=1;i<num_towers;i++)
	{
		glBegin(GL_POLYGON);
		glTexCoord2d(0,0);
			glVertex3d(all_towers[i].col-GSIZE/2,0,all_towers[i].row-GSIZE/2);
		glTexCoord2d(0,3);
			glVertex3d(all_towers[i].col-GSIZE/2,5+ground[all_towers[i].row][all_towers[i].col],all_towers[i].row-GSIZE/2);
		glTexCoord2d(5,3);
			glVertex3d(all_towers[i-1].col-GSIZE/2,5+ground[all_towers[i-1].row][all_towers[i-1].col],all_towers[i-1].row-GSIZE/2);
		glTexCoord2d(5,0);
			glVertex3d(all_towers[i-1].col-GSIZE/2,0,all_towers[i-1].row-GSIZE/2);
		glEnd();
	}

int last=num_towers-1;
		glBegin(GL_POLYGON);
		glTexCoord2d(0,0);
			glVertex3d(all_towers[0].col-GSIZE/2,0,all_towers[0].row-GSIZE/2);
		glTexCoord2d(0,3);
			glVertex3d(all_towers[0].col-GSIZE/2,4+ground[all_towers[0].row][all_towers[0].col],all_towers[0].row-GSIZE/2);
		glTexCoord2d(5,3);
			glVertex3d(all_towers[last].col-GSIZE/2,4+ground[all_towers[last].row][all_towers[last].col],all_towers[last].row-GSIZE/2);
		glTexCoord2d(5,0);
			glVertex3d(all_towers[last].col-GSIZE/2,0,all_towers[last].row-GSIZE/2);
		glEnd();

	DrawGates();
	

}

void DrawTowers()
{
	int i;
	for(i=0;i<num_towers;i++)
	{
		glPushMatrix();
		glTranslated(all_towers[i].col-GSIZE/2,ground[all_towers[i].row][all_towers[i].col],all_towers[i].row-GSIZE/2);
			glScaled(2,6,2);
			DrawTexCilynder1(all_towers[i].sides,1,1,4,all_towers[i].sides,2);
		glPopMatrix();
	// roof
	glPushMatrix();
		glTranslated(all_towers[i].col-GSIZE/2,5+ground[all_towers[i].row][all_towers[i].col],all_towers[i].row-GSIZE/2);
		glScaled(2,2,2);
		DrawTopTower(all_towers[i].sides,1.1,1.1,4,all_towers[i].sides,2);
	glPopMatrix();
	
	}
	// draw walls
	DrawWalls();
	glDisable(GL_TEXTURE_2D);

}

void ShowTowersOnMap()
{
	int i;
	glPointSize(2);
	glBegin(GL_LINE_LOOP);
	glColor3d(0.0,0.0,0.5);
	for(i=0;i<num_towers;i++)
	{
			glVertex2d(all_towers[i].col/double((GSIZE/2))-1,1-(all_towers[i].row/double((GSIZE/2))));
	}
	glEnd();
	glColor3d(1,0,1);
	for(i=0;i<num_towers;i++)
	{
		glBegin(GL_POINTS);
			glVertex2d(all_towers[i].col/double((GSIZE/2))-1,1-(all_towers[i].row/double((GSIZE/2))));
		glEnd();
	}
	glPointSize(1);


}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	glViewport(0,0,WIDTH,HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	glFrustum(-1,1,-1,1,0.7,300);
	gluLookAt(eyex,eyey,eyez,
		eyex+dirx,eyey-0.5,eyez+dirz,0,1,0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity(); // starts transformations from 0

	DrawFloor();
	DrawTowers();

	// map
	glViewport(0,0,GSIZE,GSIZE);
	glDisable(GL_DEPTH_TEST);
	glDrawPixels(GSIZE,GSIZE,GL_RGB,GL_UNSIGNED_BYTE,pix);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); 
	glOrtho(-1,1,-1,1,-1,1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
	// show user location (eyex,eyez)
	glColor3d(1,0,0);
	glBegin(GL_LINE_LOOP);
		glVertex2d(eyex/(GSIZE/2)-0.05,-eyez/(GSIZE/2)-0.05);
		glVertex2d(eyex/(GSIZE/2)-0.05,-eyez/(GSIZE/2)+0.05);
		glVertex2d(eyex/(GSIZE/2)+0.05,-eyez/(GSIZE/2)+0.05);
		glVertex2d(eyex/(GSIZE/2)+0.05,-eyez/(GSIZE/2)-0.05);
	glEnd();
	glColor3d(1,1,0);
	glBegin(GL_LINES);
		glVertex2d(eyex/(GSIZE/2)-0.05,-eyez/(GSIZE/2)-0.05);
		glVertex2d(eyex/(GSIZE/2)+0.05,-eyez/(GSIZE/2)+0.05);
		glVertex2d(eyex/(GSIZE/2)-0.05,-eyez/(GSIZE/2)+0.05);
		glVertex2d(eyex/(GSIZE/2)+0.05,-eyez/(GSIZE/2)-0.05);
	glEnd();

	ShowTowersOnMap();
	glEnable(GL_DEPTH_TEST);

	glutSwapBuffers();
}

void idle()
{
	offset+=0.5;

	dirx = sin(sight_angle);
	dirz= cos(sight_angle);
	eyez+=speed*dirz;
	eyex+=speed*dirx;
	eyey+=dy;

	glutPostRedisplay();
}



void special(int key, int x, int y)
{
	switch(key)
	{
	case GLUT_KEY_UP:
		speed+=0.001;
		break;
	case GLUT_KEY_DOWN:
		speed-=0.001;
		break;
	case GLUT_KEY_LEFT:
		sight_angle+=0.01;
		break;
	case GLUT_KEY_RIGHT:
		sight_angle-=0.01;
		break;
	case GLUT_KEY_PAGE_UP:
		dy+=0.001;
		break;
	case GLUT_KEY_PAGE_DOWN:
		dy-=0.001;
		break;

	}
}

void mouse(int button,int state, int x,int y)
{
	if(button == GLUT_LEFT_BUTTON && state== GLUT_DOWN)
	{
		if(x<GSIZE && HEIGHT-y < GSIZE)
		{
			AddTower(x,GSIZE-( HEIGHT-y));
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
	glutSpecialFunc(special);
	glutMouseFunc(mouse);

	init();
	glutMainLoop();
}
