#include <GL/glut.h>
#include <GL/gl.h>
#include <bits/stdc++.h>
#include "../include/graphics.h"
using namespace std;

#define PI 3.141592653589

void drawCircle(float x,float y,float radius,char type)
{
    if(type=='P')
    {
        drawFilledCircle(x,y,radius);
    }
    else
    {
        drawEmptycircle(x,y,radius);
    }

}

void drawFilledCircle(float cx,float cy,float rius)
{
    float delta_theta = 0.4;
    glBegin( GL_POLYGON ); 
    for( float angle = 0; angle < 2*PI; angle += delta_theta )
    glVertex2f(cx+ rius*cos(angle),cy+ rius*sin(angle));
    glEnd();
}

void drawEmptycircle(float cx,float cy,float rius)
{
    int NUM_LINES = 600;
    glBegin( GL_POINTS );
    for(int i=0;i<NUM_LINES;i++)
    {
        float theta = 2.0f * PI * float(i) / float(NUM_LINES);
        float x = rius * cosf(theta);
        float y = rius * sinf(theta);
        glVertex2f(x + cx, y + cy);
    }
    glEnd();
}   

void resizeWindow (int w, int h)
{
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluOrtho2D (0.0, (GLdouble) w, 0.0, (GLdouble) h);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}