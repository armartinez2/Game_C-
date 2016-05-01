#pragma once

#include "stdafx.h"
#include "sprite.hpp"
#include "background.hpp"

using namespace std;

class Counter: public Sprite
{
public:
    Counter(SDL_Renderer *renderer, int screenW, int screenH):Sprite(renderer, screenW, screenH){};
    void read(string file, float offset)
    {
        Sprite::read(file, offset);
        ax = 0.0;
        ay = 0.0;
        vx = 0.0;
        vy = 0.0;
        x = 0 + offset*(screenW*.1) ;
        y = 0.0;
        srcrect.x = 0;
        srcrect.y = 0;
        srcrect.w = 100;
        srcrect.h = 90;
        destrect.x = x;
        destrect.y = y; 
        destrect.w = screenW *.1;
        destrect.h = screenH *.1;
    }
    
    /*Update the Bikes State*/
    void update(float dt, float offset, int score)
    {
        // find the degree of the score
        //=================================
        int place;
        if(offset == 1) place = 100000;
        else if(offset == 2) place = 10000;
        else if(offset == 3) place = 1000;
        else if (offset == 4) place = 100;
        else if (offset == 5) place = 10;
        else place = 1;  
        //=================================

        if(score/place < 1){
            srcrect.x = 0;
            srcrect.y = 0;
        }
        else if(score/place >= 1 && score/place < 2){
            srcrect.x = 90;
        }
        else if(score/place >= 2 && score/place < 3){
            srcrect.x = 175;
        }
        else if(score/place >= 3 && score/place < 4){
            srcrect.x = 265;
        }
        else if(score/place >= 4 && score/place < 5){
            srcrect.x = 355;
        }
        else if(score/place >= 5 && score/place < 6){
            srcrect.x = 445;
        }
        else if(score/place >= 6 && score/place < 7){
            srcrect.x = 535;
        }
        else if(score/place >= 7 && score/place < 8){
            srcrect.x = 620;
        }
        else if(score/place >= 8 && score/place < 9){
            srcrect.x = 715;
        }
        else srcrect.x = 800;
    }
};