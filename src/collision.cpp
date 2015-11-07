#include "../includes/declarations.h"


//Function used to check collision with the balls. Attribute obstacle checks if the ball is the black or red.
bool checkCollision(int xp, int yp)
{
    for (int i = 0; i < num_circles; i++)
    {
        int xc = circles[i].x;
        int yc = circles[i].y;
        int r = circles[i].r;
        if ((xc - xp)*(xc-xp) + (yc - yp)*(yc-yp) <= r*r )
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

//Function used for level select range checking.
bool inCircle(int xp, int yp, float xc, float yc)
{
	double r = 0.083 * WIDTH;
    // Calculating if the line has reached inner point of circle, computing (x1-x2)**2 + (y1-y2)**2 < r**2
	if ((xc - xp)*(xc-xp) + (yc - yp)*(yc-yp) <= r*r )
		return true;
	return false;
}