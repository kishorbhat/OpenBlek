#include <iostream>
#include <GL/glut.h>
#include <string.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <sys/unistd.h>
#define WIDTH 600
#define HEIGHT 600
#define SEGMENTS 20000
using namespace std;
double arr[5000][2];
int z=0;
int flag=0;
float radius=0.03;
int ptr=0, blackptr=0, ptrsave=0;
int temp_bit=1;
int transx=0,transy=0;
float color[3][3]={{1.0,1.0,1.0},{1.0,1.0,0.0},{0.0,1.0,0.0}};
int red_black;
int collected;
bool next_level;
bool start_game;
bool dispInstr;
int level;
int num_circles;
int mult;
bool multflag;
int delx;
bool leftwall,leftwalli;
bool rightwall,rightwalli;
bool reflectionl;
bool reflectionr;
bool highlight_instr = false;
bool highlight_play = false;
char numbers[][10] = {"One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine", "Ten"};

class Circle
{
public:
    float x;
    float y;
    float r;
    int level;
    bool hit;
    bool obstacle;
    void setVal(float xc, float yc, float rad, bool obs)
    {
        x = xc;
        y = yc;
        r = rad;
        hit=false;
        obstacle=obs;
    }
}circles[100];

void draw_string(std::string str)
{
    for(unsigned int i=0;i<str.length();i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin()+i));
    }
}

void circle(float x, float y, float r, int segments, bool obs)
{
    glBegin( GL_TRIANGLE_FAN );
        if(obs==false)
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

void genLevel()
{
    if(level==0)
    {
        circles[0].setVal(400, 300, 25, false);
        circles[1].setVal(500, 300, 25, false);
        collected=2;
        num_circles=2;
    }
    if(level==1)
    {
        circles[0].setVal(100, 300, 25, false);
        circles[1].setVal(500, 300, 25, false);
        collected=2;
        num_circles=2;
    }
    if(level==2)
    {
        circles[0].setVal(230, 300, 25, false);
        circles[1].setVal(370, 300, 25, false);
        circles[2].setVal(300, 300, 20, true);
         collected=2;
        num_circles=3;
    }
    if(level==3)
    {
        circles[0].setVal(250, 250, 25, false);
        circles[1].setVal(350, 250, 25, false);
        circles[2].setVal(250, 350, 25, false);
        circles[3].setVal(350, 350, 25, false);
        collected=4;
        num_circles=4;
    }
    if(level==4)
    {
        circles[0].setVal(250, 250, 25, false);
        circles[1].setVal(350, 250, 25, false);
        circles[2].setVal(250, 350, 25, false);
        circles[3].setVal(350, 350, 25, true);
        collected=3;
        num_circles=4;
    }
    if(level==5)
    {
        circles[0].setVal(300, 300, 15, false);
        circles[1].setVal(50, 300, 10, true);
        circles[2].setVal(75, 300, 10, true);
        circles[3].setVal(150, 300, 10, true);
        circles[4].setVal(200, 300, 15, false);
        circles[5].setVal(250, 300, 10, true);
        circles[6].setVal(350, 300, 10, true);
        circles[7].setVal(400, 300, 15, false);
        circles[8].setVal(450, 300, 10, true);
        circles[9].setVal(550, 300, 10, true);
        circles[10].setVal(525, 300, 10, true);
        collected=3;
        num_circles=11;

    }
}

void resetAll()
{
    memset(arr,0,5000);
    z=0;
    next_level=false;
    start_game=false;
    transx=0;
    transy=0;
    num_circles=0;
    red_black=0;
    mult=1;
    multflag=false;
    leftwall=true;
    rightwall=true;
    reflectionl=false;
    reflectionr=false;
    genLevel();
}

bool checkCollision(int xp, int yp)
{
    int xc, yc, r;
    for (int i = 0; i < num_circles; i++)
    {
        xc = circles[i].x;
        yc = circles[i].y;
        r = circles[i].r;
        if (sqrt(pow((xc - xp), 2) + pow((yc - yp), 2)) <= r)
        {
            if(circles[i].hit==false)
                collected--;
            circles[i].hit = true;
            if(circles[i].obstacle==true)
            {
                circles[i].hit=false;
                resetAll();
                return false;
            }
            if(collected==0)
            {
                level++;
                next_level=true;
            }

            return true;
        }
    }
    return false;
}

void drawText(char const *str,float x,float y)
{
    int i;
    int len=strlen(str);
    glColor3f(0.0,0.0,0.0);
    int fl = strcmp(str, "Blek");
    glRasterPos2f(x,y);
    for(i=0;i<len;i++)
        if (fl)
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,str[i]);
        else
            glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, str[i]);
}

void init()
{
    glClearColor( 245.0, 245.0, 245.0, 1.0);
    red_black=0;
    next_level=false;
    start_game=true;
    level=0;
    num_circles=0;
    mult=1;
    multflag=false;
    leftwall=true;
    rightwall=true;
    reflectionl=false;
    reflectionr=false;
    glLineWidth(5);
    glMatrixMode( GL_PROJECTION);
    gluOrtho2D(0.0,WIDTH,0.0,HEIGHT);
    memset(arr,0,5000);
    glPointSize(20.0);
    genLevel();
}

///OPENGL MAPPING///
float getOpenGLX(int x)
{
    double ox = x/ (double)WIDTH*(WIDTH);
    return ox;
}

float getOpenGLY(int y)
{
    double oy = (1 - y/ (double) HEIGHT)*HEIGHT;
    return oy;
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

void addValue(int x,int y)
{
    arr[z][0]=getOpenGLX(x);
    arr[z++][1]=getOpenGLY(y);
    if(checkCollision(arr[z-1][0],arr[z-1][1]))
    {
         if(flag)
        {
            ptr=0;
            flag=0;
        }
    }
}

void drawCircles()
{
    for (int i = 0; i < num_circles; i++)
    {
        if (!circles[i].hit)
            circle(circles[i].x, circles[i].y, circles[i].r, SEGMENTS, circles[i].obstacle);
    }
}

void myDisplay()
{
    glClear( GL_COLOR_BUFFER_BIT );
    if(start_game)
    {
      drawText("Blek",250.0,350.0);
      glColor3f(1.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex3f(250.0f, 345.0f, 0.0f);
      glVertex3f(475.0f, 345.0f, 5.0f);
      glEnd();

      drawText("Level Select",220.0,300.0);
      if (highlight_instr)
        glColor3f(0.0, 1.0, 0.0);
      else
        glColor3f(1.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex3f(220.0f, 295.0f, 0.0f);
      glVertex3f(820.0f, 295.0f, 5.0f);
      glEnd();

      drawText("Play!",250.0,250.0);
      if (highlight_play)
        glColor3f(0.0, 1.0, 0.0);
      else
        glColor3f(1.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex3f(250.0f, 245.0f, 0.0f);
      glVertex3f(480.0f, 245.0f, 5.0f);
      glEnd();
    }

    else if(next_level)
    {
        drawText("Next level",250.0,300.0);
    }
    else
    {
        drawCircles();
        if(flag)
        {
            drawLines(z-1);
            blackptr=0;
            ptr=0;
            red_black=1;
            ptrsave=z;
        }
        if(!flag)
        {
            if(!temp_bit)
            {

                glPushMatrix();
                    if(red_black==0)
                    {
                        if(ptr==z-1)
                        {
                            red_black=1;
                        }
                        else
                        {
                            drawCircles();
                            glTranslatef(transx,transy,0);
                            drawLines(ptr);
                        }
                    }
                    else
                    {
                        if(blackptr==z-1)
                        {
                        	transx+=mult*(arr[z-1][0]-arr[0][0]);
                            transy+=(arr[z-1][1]-arr[0][1]);
                            red_black=0;
                            if(reflectionr && rightwall )
                            {
                            	reflectionr=false;
                            	rightwall=false;
                            	mult*=-1;
          						transx+=2*mult*delx;
                            }
                            else if(reflectionl && leftwall)
                            {
                            	reflectionl=false;
                            	leftwall=false;
                            	mult*=-1;
          						transx+=2*mult*delx;
                            }
                        }
                        else
                        {
                        	drawCircles();
                        	glTranslatef(transx,transy,0);
                        	drawLines(ptrsave);
                        	drawBlackLines(blackptr);
                        }
                    }
                glPopMatrix();
            }
        }
        if(temp_bit)
        {
            // drawText("Project",50.0,500.0,0);
            // drawText("Welcome",250.0,300.0,1);
            // drawText("Drag the Mouse Any Where",10.0,200.0,2);
        }
    }
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}

void keyPressed(unsigned char key, int x, int y)
{
    if (key == 'm')
    {
        level++;
        resetAll();
    }
}

void myMouseStat(int button,int state,int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if(!flag)
        {
            if(temp_bit)
            {
                temp_bit=0;
            }
            resetAll();
            flag=1;
        }
    }
    else if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
    {
        if(flag)
        {
            ptr=0;
            flag=0;
        }
    }
}

void myPressedMove(int x,int y)
{
    if(flag)
        addValue(x,y);
    if(start_game)
    {
        if(x >= 220 && x <= 820 && y >= 295 && y <= 325)
            dispInstr = true;
    }
}

void mouse_motion(int x, int y)
{
    if (start_game)
    {
        if (x >= 220 && x <= 820 && y >= 295 && y <= 325)
            highlight_instr = true;
        else
            highlight_instr = false;

        if (x >= 250 && x <= 480 && y >= 345 && y <= 365)
            highlight_play = true;
        else
            highlight_play = false;
    }

}

void myTimer(int t)
{
    if(ptr!=z&&red_black==0)
    {
        ptr++;
        blackptr=0;
        ptrsave=ptr;
    }
    else if(ptr==z&&red_black==1)
        ptr=0;
    else
    {
        blackptr++;
        ptr=0;
    }
    glutTimerFunc(9,myTimer,0);
}

int main( int argc, char ** argv)
{
    glutInit( &argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowPosition( 100, 100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow( "Testing");
    init();
    glutDisplayFunc(myDisplay);
    glutMouseFunc(myMouseStat);
    glutPassiveMotionFunc(mouse_motion);
    glutMotionFunc(myPressedMove);
    glutTimerFunc(9,myTimer,0);
    glutKeyboardFunc(keyPressed);
    glutMainLoop();
    return 0;
}
