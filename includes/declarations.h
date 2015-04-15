#include <iostream>
#include <string.h>
#include <string>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <sys/unistd.h>

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

string GetStdoutFromCommand(string);

void findresoulution();

void draw_string(string);

void circle(float, float, float, int, bool);

void genLevel();

void resetAll();

bool checkCollision(int, int);

bool inCircle(int, int, float, float);

void drawText(char const *,float,float);

void init();

float getOpenGLX(int);

float getOpenGLY(int);

void drawLines(int);

void drawBlackLines(int);

void addValue(int,int);

void drawCircles();

void myDisplay();

void keyPressed(unsigned char, int, int);

void myMouseStat(int, int, int, int);

void myPressedMove(int, int);

void mouse_motion(int, int);

void myTimer(int);
