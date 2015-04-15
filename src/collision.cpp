#include "../includes/declarations.h"

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