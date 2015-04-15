#include "../includes/declarations.h"

void circle(float x, float y, float r, int segments, bool obs)
{
    glBegin( GL_TRIANGLE_FAN );
        if(obs==false && lvlSelect==1)
            glColor3f(1.0, 1.0, 0.0);
        else if(obs==false)
            glColor3f(1.0, 0.0, 0.0);
        else
            glColor3f(0.0, 0.0, 0.0);
        glVertex2f(x, y);
        for( int n = 0; n <= segments; ++n )
        {
            float const t = 2*M_PI*(float)n/(float)segments;
            glVertex2f(x + sin(t)*r, y + cos(t)*r);
        }
    glEnd();
}

void drawLines(int x)
{
    glBegin(GL_LINE_STRIP);
    glColor3f(0.0,0.0,0.0);
    int newx=arr[0][0];
    glVertex2f(newx,arr[0][1]);
    leftwalli=leftwall;
    rightwalli=rightwall;
    for(int i=1;i<x;i++)
    {
        newx+=mult*(arr[i][0]-arr[i-1][0]);
        if(newx+transx<0 && leftwalli)
        {
            leftwalli=false;
            mult*=-1;
            newx+=2*mult*(arr[i][0]-arr[i-1][0]);
            multflag=true;
            reflectionl=true;
        }
        else if(newx+transx>WIDTH && rightwalli)
        {
            rightwalli=false;
            mult*=-1;
            newx+=2*mult*(arr[i][0]-arr[i-1][0]);
            multflag=true;
            reflectionr=true;
        }
        glVertex2f(newx,arr[i][1]);
        if(x!=z-1&&red_black==0)
            checkCollision(newx+transx,arr[i][1]+transy);
        if(i==x-1 && multflag)
        {
            leftwalli=leftwall;
            rightwalli=rightwall;
            multflag=false;
            mult*=-1;
        }
    }
    glEnd();
}

void drawBlackLines(int x)
{
    glBegin(GL_LINE_STRIP);
    glColor3f(245.0,245.0,245.0);
    int newx=arr[0][0];
    leftwalli=leftwall;
    rightwalli=rightwall;
    glVertex2f(newx,arr[0][1]);
    for(int i=1;i<x;i++)
    {
        newx+=mult*(arr[i][0]-arr[i-1][0]);
        if(newx+transx<0&&leftwalli)
        {
            leftwalli=false;
            mult*=-1;
            newx+=2*mult*(arr[i][0]-arr[i-1][0]);
            multflag=true;
            delx=0;
            reflectionl=true;
        }
        else if(newx+transx>WIDTH&&rightwalli)
        {
            rightwalli=false;
            mult*=-1;
            newx+=2*mult*(arr[i][0]-arr[i-1][0]);
            multflag=true;
            delx=0;
            reflectionr=true;
        }
        glVertex2f(newx,arr[i][1]);
        if(multflag)
            delx+=(arr[i][0]-arr[i-1][0]);
        if(i==x-1 && multflag)
        {
            leftwalli=leftwall;
            rightwalli=rightwall;
            multflag=false;
            mult*=-1;
        }
    }
    glEnd();
}

void drawCircles()
{
    for (int i = 0; i < num_circles; i++)
    {
        if (!circles[i].hit)
            circle(circles[i].x, circles[i].y, circles[i].r, SEGMENTS, circles[i].obstacle);
    }
}
