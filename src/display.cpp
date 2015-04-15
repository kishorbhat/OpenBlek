#include "../includes/declarations.h"

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