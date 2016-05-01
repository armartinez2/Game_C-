#pragma once

#include "sprite.hpp"

using namespace std;

class Floor: public Sprite
{
public:
    Floor(SDL_Renderer *renderer, int screenW, int screenH):Sprite(renderer, screenW, screenH){};
    
    void read(string file, float offset)
    {
        Sprite::read(file, offset);
        ax = 1.0;
        ay = 0.0;
        vx = 10.0;
        vy = 0.0;
        x = 340;
        y = 5;
        destrect.x = 0;
        destrect.y = WindowHeight-14;
        destrect.w = WindowWidth;
        destrect.h = 15;
    }

    
    void display()
    {
        SDL_RenderCopy(screen, bitmapTextures[0], NULL, &destrect);
    }
};
