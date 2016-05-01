#pragma once
#include <SDL2/SDL.h>
#include "sprite.hpp"
#include <string>

class StaticSprite: public Sprite
{
public:
    StaticSprite(SDL_Renderer *renderer, int screenW, int screenH):Sprite(renderer, screenW, screenH){}
    void read(string file, float offset)
    {
        Sprite::read(file, offset);
        ax = 0.0;
        ay = 0.0;
        vx = 0.0;
        vy = 0.0;
    }
};
