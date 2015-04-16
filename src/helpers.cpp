#include "../includes/declarations.h"

//Function to reset all parameters involved in the game.
void resetAll()
{
    memset(arr,0,10000);
    z=0;
    ptr=0;
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

//Function to initiliaze to variables.
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

//Functions to convert x and y co-ordinates provided by OpenGL mouse function into Euclidean ones. 
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

//Detects which key is pressed and sets appropriate flags.
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

//Function to check mouse activity.
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

//Function passed to passive mouse function to track user movement.
void mouse_motion(int x, int y)
{
    int cg_x = getOpenGLX(x), cg_y = getOpenGLY(y);
    if (start_game)
    {
        if (cg_x >= 0.367*WIDTH && cg_x <=0.495*WIDTH && cg_y >= 0.492*HEIGHT && cg_y <= 0.542*HEIGHT)
            highlight_lvls = true;
        else
            highlight_lvls = false;

        if (cg_x >= 0.417*WIDTH && cg_x <= 0.450*WIDTH && cg_y >= 0.417*HEIGHT && cg_y <= 0.467*HEIGHT)
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

//Timer function to update variables in realtime.
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
