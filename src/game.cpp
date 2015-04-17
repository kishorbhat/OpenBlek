/* OpenGL implementation of Blek*/
#include "../includes/declarations.h"
#include "helpers.cpp"
#include "getresolution.cpp"
#include "display.cpp"
#include "collision.cpp"
#include "strings.cpp"
#include "genlevel.cpp"
#include "drawobjects.cpp"


//Main function
int main( int argc, char ** argv)
{
    findresolution();
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("OpenBlek");
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
