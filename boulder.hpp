#pragma once

#include "stdafx.h"
#include "sprite.hpp"

class Boulder: public Sprite
{
public:
    Boulder(SDL_Renderer *renderer, int screenW, int screenH):Sprite(renderer, screenW, screenH){};

    void read(string file, float offset)
    {
        Sprite::read(file, offset);
        ax = 0.0;
        ay = 0.0; 
        vx = 0.0;
        vy = 0.0;
        x = WindowWidth - 100;
        y = (WindowHeight * .87);
        srcrect.x = 0;
        srcrect.y = 0;
        srcrect.h = 250;
        srcrect.w = 500;
        destrect.x = 0;
        destrect.y = y;
        destrect.w = 80;
        destrect.h = 80;
    }
    
    /*Boulder Movement*/
    void move(SDL_Event &e, float accelerate)
    {
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
            ax = -accelerate;
        else if (vx != 0) 
            ax = 5;
        else 
            ax = 0;
    }

    /*Update the Boulder State*/
    void update(float dt, float offset, int a)
    {
        if(destrect.x <= -1*screenW) x = screenW + (1000/rand());
		t+=1000.0*dt;
		vx+=ax*dt;
		vy+=ay*dt;
		x+=vx*dt;
		y+=vy*dt;
    }

};