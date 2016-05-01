#include "stdafx.h"
//#include "bike.hpp"
#include "background.hpp"
#include "staticsprite.hpp"
#include "floor.hpp"
#include "ScreenInfo.h"
#include "threadedOut.h"
#include "bird.hpp"
#include "boulder.hpp"
#include "cat.hpp"
#include "counter.hpp"

using namespace std;

int i = 1;

int main(int argc, const char * argv[]) 
{
    int posX=100, posY=100, microseconds = 2500, last = SDL_GetTicks(), accelerant = (WindowWidth/0.9);
    vector<Sprite *> sprites;
    SDL_Window *window=NULL;
    SDL_Renderer *renderer=NULL;
    
    /*Creates Window*/
    SDL_Init(SDL_INIT_VIDEO);
    window= SDL_CreateWindow("Bike", posX, posY, WindowWidth, WindowHeight, 0);
    renderer= SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    
    /*Creates Background's 1st Half [0]*/
    BG *bg1 = new BG(renderer, WindowWidth, WindowHeight);
    bg1->read("./txt/otherbackground.txt", 0);
    sprites.push_back(bg1);
    
    /*Creates Background's 2nd Half [1]*/
    BG *bg2 = new BG(renderer, WindowWidth, WindowHeight);
    bg2->read("./txt/otherbackground.txt", WindowWidth);
    sprites.push_back(bg2);
    
    /*Creates Cat [2]*/
    Cat *cat=new Cat(renderer, WindowWidth, WindowHeight);
    cat->read("./txt/cat.txt", 0);
    sprites.push_back(cat);

    /*Creates Bird1 [3]*/
    Bird *bird1 = new Bird (renderer, WindowWidth, WindowHeight);
    bird1->seed(SDL_GetTicks());
    bird1->read("./txt/bird.txt", 0);
    sprites.push_back(bird1);

    /*Creates Bird2 [4]*/
    Bird *bird2 = new Bird (renderer, WindowWidth, WindowHeight);
    bird2->seed(SDL_GetTicks());
    bird2->read("./txt/bird.txt", 0);
    sprites.push_back(bird2);
    
    /*Creates Bird3 [5]*/
    Bird *bird3 = new Bird (renderer, WindowWidth, WindowHeight);
    bird3->seed(SDL_GetTicks());
    bird3->read("./txt/bird.txt", 0);
    sprites.push_back(bird3);

    /*Creates boulder1 [6]*/
    Boulder *boulder1 = new Boulder (renderer, WindowWidth, WindowHeight);
    boulder1->read("./txt/boulder.txt", 0);
    sprites.push_back(boulder1);

    for (int i = 0; i<6; i++){
    	Counter *counter = new Counter (renderer, WindowWidth, WindowHeight);
    	counter->read("./txt/counter.txt", i);
    	sprites.push_back(counter);
    }
    
    /*Creates Rain [7-N]*/
    for(int i=0;i<300;i++)
    {
        Sprite *s = new Sprite(renderer, WindowWidth, WindowHeight);
        s->read("./txt/rain.txt", 0);
        sprites.push_back(s);
    }
   
    while(!exitFlag)
    {
        /*gives the processor a break*/
        usleep(microseconds);

        float dt = float(SDL_GetTicks()-last)/1000.0;
    
        SDL_Event e;
        if(SDL_PollEvent(&e))
        {
            if(e.type==SDL_QUIT)
                break;
            cat->move(e);
            bird1->move(e, accelerant); 
            bird2->move(e, accelerant);
            bird3->move(e, accelerant);
            boulder1->move(e, accelerant);
            bg2->scroll(e, accelerant);
    		bg1->scroll(e, accelerant);
        }
        
        for(unsigned i=0;i<sprites.size();i++){
        	if(i == 2) sprites[i]->update(dt,sprites[1]->getVelocity(),0);
        	else if(i>7 && i<14) sprites[i]->update(dt,i-7,score);
        	else sprites[i]->update(dt,i-7,0);
        }
        
        last=SDL_GetTicks();
        
        SDL_RenderClear(renderer);
        
        bg1->display();
        bg2->display();

        
        for(unsigned i=2;i<sprites.size();i++)
            sprites[i]->draw();
            
        //==============COLLISION CODE==========================================
        if(sprites[2]->collidesWith(sprites[6]))
        {
			cout << "CRASH!" << endl;
            cout << "SCORE: " << score << endl;
            //exitFlag = true;
            //maybe we should trip a flag to stop the main game loop???????? 
            //=====psuedo==============
            //kill movements
            //question, "continue? y/n"
            //cin >> userInput >> endl;
            // if yes
            //        
            //if no 
            //      exitFlag = true;
            //=========================
		}

        if(sprites[2]->collidesWith(sprites[5]))
        {
           // cout << "bird3 impact" << endl;
            score++;
        }
        if(sprites[2]->collidesWith(sprites[4]))
        {
           // cout << "bird2 impact" << enmdl;
            score++;
        }
        if(sprites[2]->collidesWith(sprites[3]))
        {
           // cout << "bird1 impact" << endl;
            score++;
        }
       
        /*
        for(unsigned i=3;i<sprites.size();i++){
            for(unsigned j=i+1;j<sprites.size();j++){
                if(!sprites[i]->isDead() && !sprites[j]->isDead() &&
                   sprites[j]->collidesWith(sprites[i])){
                       if(sprites[i]->getVelocity()>sprites[j]->getVelocity())
                           sprites[j]->kill();
                       else
                           sprites[i]->kill();
                }
            }
        }
        */
        //======================================================================
       
        SDL_RenderPresent(renderer);
    }
    
    for(unsigned i=0;i<sprites.size();i++)
        delete sprites[i];
    
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}