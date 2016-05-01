#pragma once

#include "stdafx.h"
#include "sprite.hpp"
#include "background.hpp"

using namespace std;
int score =0;
bool exitFlag = false;

class Cat: public Sprite
{
public:
    Cat(SDL_Renderer *renderer, int screenW, int screenH):Sprite(renderer, screenW, screenH){};
    void read(string file, float offset)
    {
        Sprite::read(file, offset);
        ax = 1.0;
        ay = (WindowHeight/1.79);
        vx = 10.0;
        vy = 0.0;
        x = 100;
        y = (WindowHeight * .84);
        srcrect.x = 0;
        srcrect.y = 0;
        srcrect.w = 500;
        srcrect.h = 250;
        destrect.x = 0;
        destrect.y = 60; 
        destrect.w = WindowWidth * .10; 
        destrect.h = WindowHeight * .10;
    }
    
    /*Cheetah Movement*/
    void move(const SDL_Event &e)
    {
        if(e.type == SDL_KEYDOWN)
        {  
            if(y >= (WindowHeight *.85))
            {
                if (e.key.keysym.sym == SDLK_UP)
                    vy -= (WindowHeight/1.5);
            }


            if (e.key.keysym.sym == SDLK_LEFT) 
            {}
            else if (e.key.keysym.sym == SDLK_RIGHT) 
            {
                //put scroll acceleration in here
            }
        }
    }

    /*Update the Cheetah State*/
    void update(float dt, float velocity, int a)
    {
        if(dead) return;

        if(y<WindowHeight*.85) t = 0;// when the cat jumps it will freeze on leeping picture

        if(t< 240)
        {
          t+= dt*(velocity*-2);
        }
        else t = 0.0;

		vx+=ax*dt;
		vy+=ay*dt;
		x+=vx*dt;
		y+=vy*dt;
        if(t <= 10){
            srcrect.x = 0;
            srcrect.y = 0;
        }
        else if (t>30 && t<= 60){
            srcrect.x = 500;
        }
        else if (t>60 && t<= 90){
            srcrect.x = 0;
            srcrect.y = 250;
        }
        else if (t>90 && t<=120 ){
            srcrect.x=500;
        }
        else if(t>120 && t<=150) {
            srcrect.x = 0;
            srcrect.y = 500;
        }
        else if (t>150 && t<=180 ){
            srcrect.x=500;
        }
        else if (t>180 && t<= 210){
            srcrect.x = 0;
            srcrect.y = 750;
        }
        else srcrect.x = 500;

        /*End of Screen Interaction*/
        if(x > screenW-destrect.w || x < 0) 
			{
                exitFlag = 1;
                cout << "End Reached!" << endl;
                cout << "SCORE: " << score << endl;
                vx =- vx;
            }

        
        /*Interaction With Ground*/
        if(y > (screenH * .85)-destrect.h) 
        {
			if (y > (WindowHeight * .85)) 
            {
                y = WindowHeight * .85;
                vy =0;
            }
	    }
    }
};