#pragma once

#include "sprite.hpp"
#include "ScreenInfo.h"

class BG: public Sprite
{
    public:
    BG(SDL_Renderer *renderer, int screenW, int screenH):Sprite(renderer, screenW, screenH){};

    void read(string file, int xx)
    {
        Sprite::read(file, xx);
        ax = 0.0;
        ay = 0.0;
        vx = 0.0;
        vy = 0.0;
        x = xx;
        y = 0;
        destrect.x = xx;
        destrect.y = 0;
        destrect.w = screenW;
        destrect.h = screenH;
    }

    void scroll(SDL_Event &e,float accelerate) 
    {
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE) 
            ax = -accelerate;
        else if (vx != 0) 
            ax = 5;
        else 
            ax = 0;
    }

    void update(float dt, float offset, int a)
    {
        
        if(destrect.x <= -1*screenW) 
            x = screenW-5;
        
        t+=1000.0*dt;
        vx+=ax*dt;
        vy+=ay*dt;
        x+=vx*dt;
        y+=vy*dt;
        destrect.x = x;
        destrect.y = y;
    }

    void display()
    {
        SDL_RenderCopy(screen, bitmapTextures[0], NULL, &destrect);
    }
};
