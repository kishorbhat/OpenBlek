#include "../includes/declarations.h"

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