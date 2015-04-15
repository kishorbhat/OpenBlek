#include "../includes/declarations.h"
#include "helpers.cpp"
#include "getresolution.cpp"
#include "display.cpp"
#include "collision.cpp"
#include "strings.cpp"
#include "genlevel.cpp"
#include "drawobjects.cpp"


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
