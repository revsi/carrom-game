
#include <GL/glut.h>
#include <GL/gl.h>
#include <bits/stdc++.h>
#include "../include/physics.h"
#include "../include/graphics.h"
#include "../include/globals.h"

using namespace std;

#define PI 3.141592653589
#define DEG2RAD(deg) (deg * PI / 180)


class Coins // coin class
{
    public :
        float x,y,vx,vy,r,M;
        bool scored;
        void init(float X, float Y, float R, float m)
        {
            x = X;
            y = Y;
            vx = 0.0f;
            vy = 0.0f;
            r = R;
            M = m;
            scored=0;
        }
        void update()
        {
            if(x + r > 968 || x - r < 342)	//collision with the walls
            {
                vx *= -1;
            }
            if(y + r > 668 || y - r < 42)
            {
                vy *= -1;
            }
            x += vx;
            y += vy;
            if(abs(vx)>0)    // friction reducing the speed
            {
                vx-=0.006*(vx);
            }
            if(abs(vy)>0)   //threshold speed at which the coin should stop
            {
                vy-=0.006*(vy);
            }
            if(speed(vx,vy)<=1e-2) 
            {
                vx=0;
                vy=0;
            }
            /* BE Careful, the below statement is only for striker !!!!! */
            if(abs(vx)==0 && abs(vy)==0 && M==3.0f && flag==1)
            {
                x=655.0f;
                y=118.0f;
                flag=0;
            }
        }
};

Coins a[10]; 
void drawArrow()   // arrow for the direction
{
	float CenX=a[0].x;
	float CenY=a[0].y;
	float theta=DEG2RAD(StrikeAngle);
	float EndX=CenX+40*(cosf(theta));
	float EndY=CenY+40*(sinf(theta));
	float x1=10*(cosf(DEG2RAD(165) + theta));
	float y1=10*(sinf(DEG2RAD(165)+ theta));
	float x2=10*(cosf(DEG2RAD(195) + theta));
	float y2=10*(sinf(DEG2RAD(195) + theta));
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	glVertex2f(CenX,CenY);
	glVertex2f(EndX,EndY);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	glVertex2f(EndX,EndY);
	glVertex2f(EndX+x1,EndY+y1);
	glEnd();
	glColor3f(0,0,0);
	glBegin(GL_LINES);
	glVertex2f(EndX,EndY);
	glVertex2f(EndX+x2,EndY+y2);
	glEnd();

}
void TextOutput(char* string, float x, float y, float z)
{
	glRasterPos3f(x,y,z);
	int len, i;
  	len = (int)strlen(string);
  	for (i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, string[i]);
  }
}

void drawScene(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	if(GameEnd==1)
	{
		glPushMatrix();
		char scoreStr[100000]={'\0'};
		glColor4f(1,0,0,0.5);
		sprintf(scoreStr,"GAME OVER");
		TextOutput(scoreStr,100,650,0.0f);
		sprintf(scoreStr,"Your Score : %d",(int)score);
		TextOutput(scoreStr,100,600,0.0f);
	}
	else
	{
		if(Instruction==0)
		{
			glPushMatrix();
			char scoreStr[100000]={'\0'};
			glColor3f(0.5,0.5,1);
			sprintf(scoreStr,"WELCOME TO CARROM GAME");
			TextOutput(scoreStr,600,600,0.0f);
			sprintf(scoreStr,"HOW TO PLAY");
			TextOutput(scoreStr,100,560,0.0f);

			sprintf(scoreStr," Change Power of Striker by Up & Down arrow keys.");
			TextOutput(scoreStr,100,530,0.0f);

			sprintf(scoreStr," Change Direction of striker by 'a' and 'c' keys.");
			TextOutput(scoreStr,100,500,0.0f);

			sprintf(scoreStr," Move the Striker by left & right arrow keys ");
			TextOutput(scoreStr,100,470,0.0f);

			sprintf(scoreStr," For Striking press space bar");
			TextOutput(scoreStr,100,440,0.0f);

			sprintf(scoreStr," Red: 50 points, your coin : 10 points, other coin : -5 points");
			TextOutput(scoreStr,100,410,0.0f);

			sprintf(scoreStr," Each second costs you 1 point, Initial Score is 30 points");
			TextOutput(scoreStr,100,380,0.0f);
			glColor3f(0.8,0.5,0.2);
			sprintf(scoreStr," To Begin the GAME : ");
			TextOutput(scoreStr,200,230,0.0f);
			sprintf(scoreStr," Press 'w' for white coins ");
			TextOutput(scoreStr,200,200,0.0f);
			sprintf(scoreStr," Press 'b' for Black coins ");
			TextOutput(scoreStr,200,170,0.0f);
			glPopMatrix();

		}
		else
		{
			glPushMatrix();
													/*Outer Border starts*/
			glColor3f(0.647059,0.164706,0.164706);
			glBegin(GL_POLYGON);
			glVertex2f(300,0);
			glVertex2f(300,710);
			glVertex2f(1010,710);
			glVertex2f(1010,0);
			glEnd();
													/*Outer Border Ends*/
													/*Inner Border starts*/
			glColor3f(1.0f, 0.55f, 0.3f);
			glBegin(GL_POLYGON);
			glVertex2f(342,62);
			glVertex2f(342,648);
			glVertex2f(362,668);
			glVertex2f(948,668);
			glVertex2f(968,648);
			glVertex2f(968,62);
			glVertex2f(948,42);
			glVertex2f(362,42);
			glEnd();
			glColor3f(0.5f,0.5f,0.5f);
			drawCircle(362,62,20,'P');
			drawCircle(362,648,20,'P');
			drawCircle(948,648,20,'P');
			drawCircle(948,62,20,'P');
														/*Inner Border(including holes) Ends*/
														/*Central Line starts*/
			glBegin(GL_LINES);
			glColor3f(0.647059,0.164706,0.164706);
			glVertex2f(400,114);
			glVertex2f(400,596);
			glVertex2f(414,610);
			glVertex2f(896,610);
			glVertex2f(910,596);
			glVertex2f(910,114);
			glVertex2f(896,100);
			glVertex2f(414,100);
			glEnd();
			drawCircle(414,114,14,'L');
			drawCircle(414,596,14,'L');
			drawCircle(896,596,14,'L');
			drawCircle(896,114,14,'L');
														/*Central Line ends*/
														/*Central Ring starts*/
			drawCircle(657,374,100,'L');
														/*Central Ring ends*/
														/*Printing the details*/
			glColor4f(1.0f, 0.5f, 0.0f, 0.5f);
			char scoreStr[100000]={'\0'};
			char My[10]={'\0'};
			if(MyCoins%2==1)
			{
				strcpy(My,"Whites");
			}
			else
			{
				strcpy(My,"Blacks");
			}
			sprintf(scoreStr,"Your Coins : %s",My);
			TextOutput(scoreStr,100,430,0.0f);
			sprintf(scoreStr,"Power : %d",(int)speed(InVelx,InVely));
			TextOutput(scoreStr,100,393,0.0f);
			sprintf(scoreStr,"Score : %d",(int)score);
			TextOutput(scoreStr,100,360,0.0f);
			/*Vel end*/
			if(flag==0)
			{
				drawArrow();
			}
			/*Striker and Coins starts*/
			glPushMatrix();
			glColor3f(0.0f, 1.0f, 0.5f);
			drawCircle(a[0].x,a[0].y, a[0].r,'P'); // Striker
			if(a[1].scored==0)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
				drawCircle(a[1].x,a[1].y, a[1].r,'P'); // White
			}
			if(a[2].scored==0)
			{
				glColor3f(0.0f, 0.0f, 0.0f);
				drawCircle(a[2].x,a[2].y, a[2].r,'P'); // Black
			}
			if(a[3].scored==0)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
				drawCircle(a[3].x,a[3].y, a[3].r,'P'); // White
			}
			if(a[4].scored==0)
			{
				glColor3f(0.0f, 0.0f, 0.0f);
				drawCircle(a[4].x,a[4].y, a[4].r,'P'); // Black
			}
			if(a[5].scored==0)
			{
				glColor3f(1.0f, 1.0f, 1.0f);
				drawCircle(a[5].x,a[5].y, a[5].r,'P'); // White
			}
			if(a[6].scored==0)
			{
				glColor3f(0.0f, 0.0f, 0.0f);
				drawCircle(a[6].x,a[6].y, a[6].r,'P'); // Black
			}
			if(a[7].scored==0)
			{
				glColor3f(1,0,0);
				drawCircle(a[7].x,a[7].y, a[7].r,'P'); // Red
			}
			glPopMatrix();
			/*Striker and Coins ends*/
			glPopMatrix();
		}
	}
	glFlush();
	glutSwapBuffers();
}

void init (void)
{
	glClearColor (0.0,0.0,0.0,0.0);
	glShadeModel (GL_SMOOTH);
	a[0].init(655.0f,118.0f,18.0f,3.0f); // Striker
	a[1].init(657.0f,288.0f,14.0f,1.5f); // White
	a[2].init(728.0f,325.471f,14.0f,1.5f); // Black
	a[3].init(728.0f,422.528f,14.0f,1.5f); // White
	a[4].init(657.0f,460.0f,14.0f,1.5f); // Black
	a[5].init(586.0f,422.528f,14.0f,1.5f); // White
	a[6].init(586.0f,325.471f,14.0f,1.5f); // Black
	a[7].init(657.0f,374.0f,14.0f,1.5f); // Red
}


bool checkCollision(int i, int j) //Check for collision between coins.
{
	float x=(a[i].x-a[j].x);
	x*=x;
	float y=(a[i].y-a[j].y);
	y*=y;
	float r=(a[i].r+a[j].r);
	r*=r;
	if(x+y <= r)
	{
		return 1;
	}
	return 0;
}

void Check(int direction)  // check the striker position changes by the user
{
	if(flag==0)
	{
		bool clearflag=0;
		while(clearflag==0)
		{
			clearflag=1;
			float x1=a[0].x;
			float y1=a[0].y;
			if(x1<=414)
			{
				a[0].x=414;
				x1=414;
			}
			if(x1>=896)
			{
				a[0].x=896;
				x1=896;
			}
			float r1=a[0].r;
			for(int i=1;i<=7;i=i+1)
			{
				float x2=a[i].x;
				float y2=a[i].y;
				float r2=a[i].r;
				float D=distance(x1,y1,x2,y2);
				if(D<=(r1+r2))
				{
					clearflag=0;
					float T=sqrt((r1+r2)*(r1+r2) - (y2-y1)*(y2-y1));
					if(direction==0)
					{
						a[0].x-=T;
					}
					else
					{
						a[0].x+=T;
					}
				}
			}
		}
	}
}
void GameCheck()  //checking the status of game
{
	bool f=0;
	for(int i=1;i<=7;i=i+1)
	{
		if(i==7 || i%2==MyCoins)
		{
			if(a[i].scored==0)
			{
				f=1;
				break;
			}
		}
	}
	if(f==0)
	{
		GameEnd=1;
	}
}
void motion(int val)   // movement of all coins 
{
	for(int i=0;i<8;i=i+1)
	{
		a[i].update();
		float Dis1=distance(a[i].x, a[i].y,362,62);
		float Dis2=distance(a[i].x, a[i].y,362,648);
		float Dis3=distance(a[i].x, a[i].y,948,648);
		float Dis4=distance(a[i].x, a[i].y,948,62);
		if(a[i].scored == 0 && (Dis1 <= 20 || Dis2 <= 20 || Dis3 <= 20 || Dis4 <= 20))
		{
			if(i!=0)
			{
				a[i].scored=1;
				if(i>0 && i<7)
				{
					if(i%2==MyCoins)
					{
						score+=10;
					}
					else
					{
						score-=5;
					}
				}
				else if(i==7)
				{
					score+=50;
				}
				a[i].x=0;
				a[i].y=0;
			}
			else
			{
				a[i].x=655;
				a[i].y=118;
				a[i].vx=0;
				a[i].vy=0;
			}
		}
	}
	for(int i=0;i<8;i=i+1)
	{
		for(int j=0;j<8;j=j+1)
		{
			if(i!=j)
			{
				bool res=checkCollision(i,j);
				if(res==1)
				{
					float FX=((a[i].vx * (a[i].M - a[j].M))+(2*a[j].M * a[j].vx))/(a[i].M + a[j].M);
					float FY=((a[i].vy * (a[i].M - a[j].M))+(2*a[j].M * a[j].vy))/(a[i].M + a[j].M);
					float SX=((a[j].vx * (a[j].M - a[i].M))+(2*a[i].M * a[i].vx))/(a[i].M + a[j].M);
					float SY=((a[j].vy * (a[j].M - a[i].M))+(2*a[i].M * a[i].vy))/(a[i].M + a[j].M);
					a[i].vx = FX;
					a[i].vy = FY;
					a[j].vx = SX;
					a[j].vy = SY;
					a[i].update();
					a[j].update();
				}
			}
		}
	}
	Check(0);
	GameCheck();
	Timer+=10;
	if(Timer%1000==0 && GameEnd==0 && Instruction==1)
	{
		score-=1;
	}
	glutTimerFunc(10, motion, 0);
}
void mySpecialKeyFunc(int c, int x, int y)
{
	if(c==GLUT_KEY_LEFT)
	{
		if(flag==0)
		{
			a[0].x -= 12;
			Check(0);
		}
	}
	if(c==GLUT_KEY_RIGHT)
	{
		if(flag==0)
		{
			a[0].x += 12;
			Check(1);
		}
	}
	if(c==GLUT_KEY_UP)
	{
		if(flag==0)
		{
			InVelx+=0.5;
			InVely+=0.5;
			if(InVelx>=15)
			{
				InVelx=15;
			}
			if(InVely>=15)
			{
				InVely=15;
			}
		}
	}
	if(c==GLUT_KEY_DOWN)
	{
		InVelx-=0.5;
		InVely-=0.5;
		if(InVelx<=5)
		{
			InVelx=5;
		}
		if(InVely<=5)
		{
			InVely=5;
		}
	}
}
void myKeyboardFunc(unsigned char c, int x, int y)
{
	if(c==' ' && flag==0)
	{
		flag=1;
		//float S=Speed(InVelx,InVely);
		float theta=DEG2RAD(StrikeAngle);
		a[0].vx=InVelx*cosf(theta);
		a[0].vy=InVely*sinf(theta);
	}
	else if(c=='a' && flag==0)
	{
		StrikeAngle+=2;
	}
	else if(c=='c' && flag==0)
	{
		StrikeAngle-=3;
	}
	else if(c=='w'&& Instruction==0)
	{
		MyCoins=1;
		Instruction=1;
	}
	else if(c=='b' && Instruction==0)
	{
		MyCoins=0;
		Instruction=1;
	}
}
void myMouseFunc(int button, int state, int x, int y)
{
	GLint viewport[4];
	GLdouble mvmatrix[16], projmatrix[16];
	GLint realy;
	GLdouble wx, wy, wz;
	switch (button) {
		case GLUT_LEFT_BUTTON:
			break;
		case GLUT_RIGHT_BUTTON:
			if (state == GLUT_DOWN)
				exit(0);
			break;
		default:
			break;
	}
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(1500,1000);
	glutInitWindowPosition(50,50);
	glutCreateWindow("Carrom Game");
	init ();
	glutDisplayFunc(drawScene); 
	glutIdleFunc(drawScene);
	glutReshapeFunc(resizeWindow);
	glutMouseFunc(myMouseFunc);
	glutKeyboardFunc(myKeyboardFunc);  
	glutSpecialFunc(mySpecialKeyFunc);
	glutTimerFunc(10, motion, 0);
	glutMainLoop();
	return 0;
}
