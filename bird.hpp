#pragma once

#include "stdafx.h"
#include "sprite.hpp"

#include <time.h>

using namespace std; 

class Bird: public Sprite
{
public:
    Bird(SDL_Renderer *renderer, int screenW, int screenH):Sprite(renderer, screenW, screenH){};
    int random_variable;

    void read(string file, float offset)
    {
        random_variable = rand(); 
        Sprite::read(file, offset);
        ax = 0.0;
        ay = 0.0; 
        vx = -20.0;
        vy = 0.0;
        x = random_variable % (WindowWidth-100); 
        y = random_variable % (WindowHeight-((int)(WindowHeight*.25)));
        srcrect.x = 0;
        srcrect.y = 0;
        srcrect.h = 312;
        srcrect.w = 240;
        destrect.x = 0;
        destrect.y = y;
        destrect.w = 80;
        destrect.h = 80;
    }
    
    /*Bird Movement*/
    void move(const SDL_Event &e, float accelerate)
    {
        if(e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE)
            ax -= accelerate;
        else if (vx != 0) 
            ax = 5;
        else 
            ax = 0;
    }

    /*Update the Bird State*/
    void update(float dt, float offset, int a)
    {
        if(destrect.x <= -1*screenW)
        { 
            srand(SDL_GetTicks());
            x = screenW + (rand()%(screenW/4));
            y = rand() % (int)(screenH*.92);
        }
        if(dead) return;
//====================================================
        //This will change the picture of the cheetah over time
        if(t<400){
            t+=(1000.0*dt) * 1.5;
        }
        else t = 0.0;

        if(t<=20){
            srcrect.x = 0;
            srcrect.y = 0;
        }
        else if (t>20 && t<= 40){
            srcrect.x = 240;
        }
        else if (t>40 && t<= 60){
            srcrect.x = 480;
        }
        else if(t>60 && t<= 80){
            srcrect.x = 720;
        }
        else if (t>80 && t<= 100){
            srcrect.x = 960;
        }
        else if (t>100 && t<=120){
            srcrect.x = 0;
            srcrect.y = 312;
        }
        else if(t>120 && t<= 140){
            srcrect.x = 240;
        }
        else if(t>140 && t<= 160){
            srcrect.x = 480;
        }
        else if(t>160 && t<= 180){
            srcrect.x = 720;
        }
        else if(t>180 && t<= 200){
            srcrect.x = 960;
        }
        else if(t>200 && t<= 220){
            srcrect.y = 624;
            srcrect.x = 0;
        }
        else if(t>220 && t<= 240){
            srcrect.x = 240;
        }
        else if(t>240 && t<= 260){
            srcrect.x = 480;
        }
        else if(t>260 && t<= 280){
            srcrect.x = 720;
        }
        else if(t>280 && t<= 300){
            srcrect.x = 960;
        }
        else if(t>300 && t<= 320){
            srcrect.y = 936;
            srcrect.x = 0;
        }
        else if(t>320 && t<= 340){
            srcrect.x = 240;
        }
        else if(t>340 && t<= 360){
            srcrect.x = 480;
        }
        else if(t>360 && t<= 380){
            srcrect.x = 720;
        }
        else srcrect.x = 960;
        
//======================================================


		vx+=ax*dt;
		vy+=ay*dt;
		x+=vx*dt;
		y+=vy*dt;
    }

    void seed(int number)
    {
        srand(number);  /*use current time as seed for random generator*/
    }
};