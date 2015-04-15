#include "../includes/declarations.h"

//Function to draw text on screen.
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

//Function to draw text on main menu
void drawStrokeText(char*string,int x,int y,int z)
{
      char *c;
      glEnable(GL_BLEND);
      glEnable(GL_LINE_SMOOTH);
      glPushMatrix();
      glTranslatef(x+80,y,z);
      if(!strcmp(string,"Next Level"))
      glScalef(0.7f,0.7f,z);
      glColor4f(0.0,0.0,0.0,1.0);
  
      for (c=string; *c != '\0'; c++)
      {
            glutStrokeCharacter(GLUT_STROKE_MONO_ROMAN , *c);
      }
      glPopMatrix();
}