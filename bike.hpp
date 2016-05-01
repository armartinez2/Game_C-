#pragma once

#include "stdafx.h"
#include "sprite.hpp"
#include "background.hpp"

using namespace std;
int score =0;
bool exitFlag = false;

class Bike: public Sprite
{
public:
    Bike(SDL_Renderer *renderer, int screenW, int screenH):Sprite(renderer, screenW, screenH){};
    void read(string file, float offset)
    {
        Sprite::read(file, offset);
        ax = 1.0;
        ay = (WindowHeight/2.6666);
        vx = 10.0;
        vy = 0.0;
        x = 100;
        y = (WindowHeight-88);
        destrect.x = 0;
        destrect.y = y; 
        destrect.w = 80;
        destrect.h = 80;
    }
    
    /*Bike Movement*/
    void move(const SDL_Event &e)
    {
        if(e.type == SDL_KEYDOWN)
        {  
            if (e.key.keysym.sym == SDLK_UP)
                vy -= (WindowHeight/30);
            else if (e.key.keysym.sym == SDLK_DOWN) 
            {}


            if (e.key.keysym.sym == SDLK_LEFT) 
            {}
            else if (e.key.keysym.sym == SDLK_RIGHT) 
            {}
        }
    }

    /*Update the Bikes State*/
    void update(float dt, float offset, int a)
    {
        if(dead) return;
		t+=1000.0*dt;
		vx+=ax*dt;
		vy+=ay*dt;
		x+=vx*dt;
		y+=vy*dt;

        /*Horizontal Bouncing*/
        if(x > screenW-destrect.w || x < 0) 
			{
                exitFlag = 1;
                cout << "End Reached!" << endl;
                cout << "SCORE: " << score << endl;
                vx =- vx;
            }

        
        /*Veritical Bouncing*/
        if(y > screenH-destrect.h || y > WindowWidth) 
        {
			if (vy > 0)
            {
                ay = (WindowHeight/2.6666);
                vy = -(vy/1.3); //vy =- ((vy)-(WindowHeight/31.25));
            }
            if (y > (WindowHeight-79)) 
            {
                y = WindowHeight-79;
                vy =0;
            }
	    }
    }
};