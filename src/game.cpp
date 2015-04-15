#include <iostream>
#include <GL/glut.h>
#include <string.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/unistd.h>
// #define WIDTH 1366  
// #define HEIGHT 768
#define SEGMENTS 10000
#define MAX_LEVELS 9
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
int WIDTH, HEIGHT;
bool next_level;
bool start_game;
bool play_game;
bool lvlSelect = false;
int circle_choose = 511;
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
bool highlight_lvls = false;
bool highlight_play = false;
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

string GetStdoutFromCommand(string cmd) 
{
    string data;
    FILE * stream;
    const int max_buffer = 256;
    char buffer[max_buffer];
    cmd.append(" 2>&1");

    stream = popen(cmd.c_str(), "r");
    if (stream) {
    while (!feof(stream))
    if (fgets(buffer, max_buffer, stream) != NULL) data.append(buffer);
    pclose(stream);
    }
    return data;
}

void findresoulution()
{
    string s = "xrandr|grep '*'";
    string p = GetStdoutFromCommand(s);
    char width[4], height[4];
    int temp,i;

    for(i=0;i<p.size();i++)
        if(p[i]=='x')
            break;

    temp=i;
    i--;
    temp++;
    int d=3;

    while(p[i]!=' ')
        width[d--] = p[i--];

    d=0;

    while(p[temp]!=' ')
        height[d++] = p[temp++];

    int finalwidth, finalheight;
    WIDTH = atoi(width);
    HEIGHT = atoi(height);
}

void draw_string(string str)
{
    for(unsigned int i=0;i<str.length();i++)
    {
        glutStrokeCharacter(GLUT_STROKE_ROMAN, *(str.begin()+i));
    }
}

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

void genLevel()
{
    if(level==0)
    {
        circles[0].setVal(0.667*WIDTH, 0.5*HEIGHT, 0.0416*WIDTH, false);
        circles[1].setVal(0.833*WIDTH, 0.5*HEIGHT, 0.0416*WIDTH, false);
        collected=2;
        num_circles=2;
    }
    if(level==1)
    {
        circles[0].setVal(0.166*WIDTH, 0.5*HEIGHT, 0.0416*WIDTH, false);
        circles[1].setVal(0.833*WIDTH, 0.5*HEIGHT, 0.0416*WIDTH, false);
        collected=2;
        num_circles=2;
    }
    if(level==2)
    {
        circles[0].setVal(0.383*WIDTH, 0.5*HEIGHT, 0.0416*WIDTH, false);
        circles[1].setVal(0.616*WIDTH, 0.5*HEIGHT, 0.0416*WIDTH, false);
        circles[2].setVal(0.5*WIDTH, 0.5*HEIGHT, 0.0416*WIDTH, true);
         collected=2;
        num_circles=3;
    }
    if(level==3)
    {
        circles[0].setVal(0.416*WIDTH,0.416*HEIGHT, 0.0416*WIDTH, false);
        circles[1].setVal(0.583*WIDTH,0.416*HEIGHT,0.0416*WIDTH, false);
        circles[2].setVal(0.416*WIDTH, 0.583*HEIGHT, 0.0416*WIDTH, false);
        circles[3].setVal(0.583*WIDTH, 0.583*HEIGHT,0.0416*WIDTH , false);
        collected=4;
        num_circles=4;
    }
    if(level==4)
    {
        circles[0].setVal(0.416*WIDTH, 0.416*HEIGHT, 0.0416*WIDTH, false);
        circles[1].setVal(0.583*WIDTH, 0.416*HEIGHT,0.0416*WIDTH, false);
        circles[2].setVal(0.416*WIDTH, 0.583*HEIGHT,0.0416*WIDTH, false);
        circles[3].setVal(0.583*WIDTH, 0.583*HEIGHT, 0.0416*WIDTH, true);
        collected=3;
        num_circles=4;
    }
    if(level==5)
    {
        circles[0].setVal(0.5*WIDTH, 0.5*HEIGHT, 0.025*WIDTH, false);
        circles[1].setVal(0.083*WIDTH, 0.5*HEIGHT, 0.0166*WIDTH, true);
        circles[2].setVal(0.125*WIDTH, 0.5*HEIGHT,0.0166*WIDTH, true);
        circles[3].setVal(0.25*WIDTH, 0.5*HEIGHT, 0.0166*WIDTH, true);
        circles[4].setVal(0.33*WIDTH, 0.5*HEIGHT, 0.025*WIDTH, false);
        circles[5].setVal(0.416*WIDTH, 0.5*HEIGHT, 0.0166*WIDTH, true);
        circles[6].setVal(0.583*WIDTH, 0.5*HEIGHT, 0.0166*WIDTH, true);
        circles[7].setVal(0.66*WIDTH, 0.5*HEIGHT, 0.025*WIDTH, false);
        circles[8].setVal(0.75*WIDTH, 0.5*HEIGHT, 0.0166*WIDTH, true);
        circles[9].setVal(0.916*WIDTH, 0.5*HEIGHT, 0.0166*WIDTH, true);
        circles[10].setVal(0.875*WIDTH, 0.5*HEIGHT, 0.0166*WIDTH, true);
        collected=3;
        num_circles=11;

    }
    if(level==6)
    {
        circles[0].setVal(0.0625*WIDTH, 0.5*HEIGHT, 0.0125*WIDTH, true);
        circles[1].setVal(0.09375*WIDTH, 0.5*HEIGHT, 0.0125*WIDTH, true);
        circles[2].setVal(0.219*WIDTH, 0.5*HEIGHT, 0.0125*WIDTH, true);
        circles[3].setVal(0.344*WIDTH, 0.5*HEIGHT, 0.0125*WIDTH, true);
        circles[4].setVal(0.406*WIDTH, 0.5*HEIGHT, 0.0189*WIDTH, true);
        circles[5].setVal(0.469*WIDTH, 0.5*HEIGHT, 0.0125*WIDTH, true);
        circles[6].setVal(0.531*WIDTH, 0.5*HEIGHT, 0.0189*WIDTH, false);
        circles[7].setVal(0.593*WIDTH, 0.5*HEIGHT, 0.0125*WIDTH, true);
        circles[8].setVal(0.656*WIDTH, 0.5*HEIGHT, 0.0189*WIDTH, false);
        circles[9].setVal(0.718*WIDTH, 0.5*HEIGHT, 0.0125*WIDTH, true);
        circles[10].setVal(0.781*WIDTH, 0.5*HEIGHT, 0.0189*WIDTH, true);
        circles[11].setVal(0.843*WIDTH, 0.5*HEIGHT, 0.0125*WIDTH, true);
        circles[12].setVal(0.906*WIDTH, 0.5*HEIGHT, 0.0189*WIDTH, false);
        circles[13].setVal(0.969*WIDTH, 0.5*HEIGHT, 0.0125*WIDTH, true);
        collected=3;
        num_circles=14;
    }
    if(level==7)
    {
        circles[0].setVal(0.125*WIDTH+0.08*WIDTH, 0.125*HEIGHT+0.08*WIDTH, 0.0125*WIDTH+0.0125*HEIGHT, true);
        circles[1].setVal(0.25*WIDTH+0.08*WIDTH, 0.25*HEIGHT+0.08*WIDTH,0.00935*WIDTH+0.00935*HEIGHT, true);
        circles[2].setVal(0.25*WIDTH+0.08*WIDTH,0.3125*HEIGHT+0.08*WIDTH,0.00935*WIDTH+0.00935*HEIGHT, false);
        circles[3].setVal(0.25*WIDTH+0.08*WIDTH, 0.1875*HEIGHT+0.08*WIDTH, 0.00935*WIDTH+0.00935*HEIGHT, false);
        circles[4].setVal(0.375*WIDTH+0.08*WIDTH, 0.375*HEIGHT+0.08*WIDTH, 0.00935*WIDTH+0.00935*HEIGHT, true);
        circles[5].setVal(0.375*WIDTH+0.08*WIDTH, 0.4375*HEIGHT+0.08*WIDTH, 0.00935*WIDTH+0.00935*HEIGHT, false);
        circles[6].setVal(0.375*WIDTH+0.08*WIDTH, 0.3125*HEIGHT+0.08*WIDTH, 0.00935*WIDTH+0.00935*HEIGHT, false);
        circles[7].setVal(0.5*WIDTH+0.08*WIDTH, 0.5*HEIGHT+0.08*WIDTH, 0.00935*WIDTH+0.00935*HEIGHT, true);
        circles[8].setVal(0.5*WIDTH+0.08*WIDTH, 0.5625*HEIGHT+0.08*WIDTH, 0.00935*WIDTH+0.00935*HEIGHT, false);
        circles[9].setVal(0.5*WIDTH+0.08*WIDTH, 0.4375*HEIGHT+0.08*WIDTH, 0.00935*WIDTH+0.00935*HEIGHT, false);
        circles[10].setVal(0.625*WIDTH+0.08*WIDTH, 0.625*HEIGHT+0.08*WIDTH, 0.0125*WIDTH+0.0125*HEIGHT, true);
        collected=6;
        num_circles=11;

    }
    if(level==8)
    {
        circles[0].setVal(0.25*WIDTH, 0.3125*HEIGHT, 0.025*WIDTH+0.025*HEIGHT, true);
        circles[1].setVal(0.25*WIDTH, 0.6875*HEIGHT, 0.025*WIDTH+0.025*HEIGHT, true);
        circles[2].setVal(0.5*WIDTH, 0.3125*HEIGHT, 0.025*WIDTH+0.025*HEIGHT, true);
        circles[3].setVal(0.5*WIDTH, 0.6875*HEIGHT, 0.025*WIDTH+0.025*HEIGHT, true);
        circles[4].setVal(0.75*WIDTH, 0.6875*HEIGHT, 0.025*WIDTH+0.025*HEIGHT, true);

        circles[5].setVal(0.5*WIDTH, 0.7875*HEIGHT, 0.01*WIDTH+0.01*HEIGHT, false);
        circles[6].setVal(0.44*WIDTH, 0.6875*HEIGHT, 0.01*WIDTH+0.01*HEIGHT, false);

        circles[7].setVal(0.5*WIDTH, 0.2125*HEIGHT, 0.01*WIDTH+0.01*HEIGHT, false);
        circles[8].setVal(0.56*WIDTH, 0.3125*HEIGHT, 0.01*WIDTH+0.01*HEIGHT, false);

        circles[9].setVal(0.75*WIDTH, 0.7875*HEIGHT, 0.01*WIDTH+0.01*HEIGHT,false );
        circles[10].setVal(0.81*WIDTH, 0.6875*HEIGHT, 0.01*WIDTH+0.01*HEIGHT,false );
        circles[11].setVal(0.75*WIDTH, 0.5875*HEIGHT, 0.01*WIDTH+0.01*HEIGHT,false );

        circles[12].setVal(0.25*WIDTH, 0.88*HEIGHT, 0.00625*WIDTH + 0.00625*HEIGHT,true);
        circles[13].setVal(0.5*WIDTH, 0.88*HEIGHT, 0.00625*WIDTH + 0.00625*HEIGHT,true );
        circles[14].setVal(0.75*WIDTH, 0.88*HEIGHT, 0.00625*WIDTH + 0.00625*HEIGHT,true );
        collected=7;
        num_circles=15;
    }
     
}

void resetAll()
{
    memset(arr,0,5000);
    z=0;
    next_level=false;
    if(play_game||lvlSelect)
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
    if(level==MAX_LEVELS)
    {
        level=0;
        start_game=true;
        play_game=lvlSelect=false;
    }
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

bool inCircle(int xp, int yp, float xc, float yc)
{
	double r = 0.083 * WIDTH;
	if (sqrt(pow((xc - xp), 2) + pow((yc - yp), 2)) <= r)
		return true;
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
      drawText("Blek",0.417*WIDTH,0.583*HEIGHT);
      
      drawText("R : Return To Main Menu",0.05*WIDTH,0.1*HEIGHT);
      drawText("N : Go to Previous Level",0.3*WIDTH,0.1*HEIGHT);
      drawText("M : Go to Next Level",0.595*WIDTH,0.1*HEIGHT);
      drawText("Q : Quit Game",0.890*WIDTH,0.1*HEIGHT);

      drawText("Level Select",0.417*WIDTH,0.5*HEIGHT);
      if (highlight_lvls)
        glColor3f(0.0, 1.0, 0.0);
      else
        glColor3f(1.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex3f(0.417*WIDTH, 0.492*HEIGHT, 0.0f);
      glVertex3f(0.495*WIDTH, 0.492*HEIGHT, 0.0f);
      glEnd();

      drawText("Play!",0.417*WIDTH,0.417*HEIGHT);
      if (highlight_play)
        glColor3f(0.0, 1.0, 0.0);
      else
        glColor3f(1.0, 0.0, 0.0);
      glBegin(GL_LINES);
      glVertex3f(0.417*WIDTH, 0.408*HEIGHT, 0.0f);
      glVertex3f(0.450*WIDTH, 0.408*HEIGHT, 0.0f);
      glEnd();
    }

    else if(lvlSelect)
    {
        circles[0].setVal(0.167*WIDTH, 0.67*HEIGHT, 0.0415*WIDTH+0.0415*HEIGHT,false);
        circles[1].setVal(0.500*WIDTH, 0.67*HEIGHT, 0.0415*WIDTH+0.0415*HEIGHT,false);
        circles[2].setVal(0.833*WIDTH, 0.67*HEIGHT, 0.0415*WIDTH+0.0415*HEIGHT,false);
        circles[3].setVal(0.167*WIDTH, 0.417*HEIGHT, 0.0415*WIDTH+0.0415*HEIGHT,false);
        circles[4].setVal(0.500*WIDTH, 0.417*HEIGHT, 0.0415*WIDTH+0.0415*HEIGHT,false);
        circles[5].setVal(0.833*WIDTH, 0.417*HEIGHT, 0.0415*WIDTH+0.0415*HEIGHT,false);
        circles[6].setVal(0.167*WIDTH, 0.167*HEIGHT, 0.0415*WIDTH+0.0415*HEIGHT,false);
        circles[7].setVal(0.500*WIDTH, 0.167*HEIGHT, 0.0415*WIDTH+0.0415*HEIGHT,false);
        circles[8].setVal(0.833*WIDTH, 0.167*HEIGHT, 0.0415*WIDTH+0.0415*HEIGHT,false);
        num_circles=9;
        drawCircles();
        drawText("1", 0.167*WIDTH, 0.67*HEIGHT);
        drawText("2", 0.5*WIDTH, 0.67*HEIGHT);
        drawText("3", 0.833*WIDTH, 0.67*HEIGHT);
        drawText("4", 0.167*WIDTH, 0.417*HEIGHT);
        drawText("5", 0.5*WIDTH, 0.417*HEIGHT);
        drawText("6", 0.833*WIDTH, 0.417*HEIGHT);
        drawText("7", 0.167*WIDTH, 0.167*HEIGHT);
        drawText("8", 0.5*WIDTH, 0.167*HEIGHT);
        drawText("9", 0.833*WIDTH, 0.167*HEIGHT);

        switch(circle_choose)
        {
        	case 1:
                    drawText("Baby Steps", 0.47*WIDTH, 0.833*HEIGHT);
                    break;

            case 2:
                    drawText("Far Apart", 0.47*WIDTH, 0.833*HEIGHT);
                    break;

            case 4:
                    drawText("Obstacle!!", 0.47*WIDTH, 0.833*HEIGHT);
                    break;

            case 8:
                    drawText("Magic Square", 0.47*WIDTH, 0.833*HEIGHT);
                    break;

            case 16:
                    drawText("Bad Apple", 0.47*WIDTH, 0.833*HEIGHT);
                    break;

            case 32:
                    drawText("Three Musketeers", 0.47*WIDTH, 0.833*HEIGHT);
                    break;

            case 64:
                    drawText("Man in the Middle", 0.47*WIDTH, 0.833*HEIGHT);
                    break;

            case 128:
                    drawText("Ok, This is Tough!", 0.47*WIDTH, 0.833*HEIGHT);
                    break;

            case 256:
                    drawText("Final Showdown", 0.47*WIDTH, 0.833*HEIGHT);
                    break;

            default:
                    drawText("Level Select", 0.47*WIDTH, 0.833*HEIGHT);
                    break;
        }

    }

    else if(next_level)
    {
        if(level!=MAX_LEVELS)
            drawText("Next level",0.417*WIDTH,0.500*HEIGHT);
        else
            drawText("You're Done!!",0.417*WIDTH,0.500*HEIGHT);
    }
    else if (play_game)
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
    }
    glutSwapBuffers();
    glutPostRedisplay();
    glFlush();
}

void keyPressed(unsigned char key, int x, int y)
{
    if (key == 'm')
    {
        if(level==MAX_LEVELS)
        {
            resetAll();
        }
        else
        {
            level++;
            if(level<MAX_LEVELS)
                resetAll();
            else 
                next_level=true;
        }   
    }

    if (key == 'n')
    {
        if(level)
            level--;
        resetAll();
    }

    if (key == 'r')
    {
        cout << key << "\n";
        start_game = true;
        lvlSelect = false;
        play_game = false;
        level = 0;
        resetAll();
    }

    if (key == 'q')
    {
        cout << "Thank you for playing!\n";
        cout << "This game was designed by:\n";
        cout << "Abraham Sebastian, 13IT103\n";
        cout << "Kishor Bhat, 13IT114\n";
        cout << "Chinmay Deshpande, 13IT210\n";
        cout << "Sagar Ramprasad, 13IT233\n";
        cout << "Pranav Konanur, 13IT228\n";
        exit(0);
    }
}

void myMouseStat(int button,int state,int x, int y)
{
    if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
        if (highlight_lvls)
        {
            lvlSelect = true;
            highlight_lvls = false;
            resetAll();
        }
    
        else if (highlight_play)
        {
            play_game = true;
            highlight_play = false;
            resetAll();
        }

        else if (lvlSelect)
        {
            int fl = (int)((float) log10(circle_choose) / (float) log10(2));
            cout << fl << "\n";
            if (fl <= 8)
            {
                level = fl;
                play_game = true;
                lvlSelect = false;
                resetAll();
            }
        }
    
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
}

void mouse_motion(int x, int y)
{
    int cg_x = getOpenGLX(x), cg_y = getOpenGLY(y);
    if (start_game)
    {
        if (cg_x >= 0.367*WIDTH && cg_x <= 1.367*WIDTH && cg_y >= 0.492*HEIGHT && cg_y <= 0.542*HEIGHT)
            highlight_lvls = true;
        else
            highlight_lvls = false;

        if (cg_x >= 0.417*WIDTH && cg_x <= 0.8*WIDTH && cg_y >= 0.417*HEIGHT && cg_y <= 0.467*HEIGHT)
            highlight_play = true;
        else
            highlight_play = false;
    }

    if (lvlSelect)
    {
    	for (int i = 0; i < 9; i++)
    	{
    		if (inCircle(cg_x, cg_y, circles[i].x, circles[i].y))
    		{
    			circle_choose &= (int) pow(2, i);
                break;
    		}
    	    else
    			circle_choose = 511;
    	}
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
    findresoulution();
    glutInit( &argc, argv);
    glutInitDisplayMode( GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowPosition( 100, 100);
    glutInitWindowSize(WIDTH,HEIGHT);
    glutCreateWindow( "Testing");
    glutFullScreen();
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
