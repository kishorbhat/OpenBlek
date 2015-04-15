#include "../includes/declarations.h"

//Function to generate various levels of the program.
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
