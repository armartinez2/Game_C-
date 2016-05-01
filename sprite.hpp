#pragma once
#include "stdafx.h"
#include "ScreenInfo.h"

#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

class Sprite
{
protected:
  bool dead;
  int totalTime, screenW, screenH;
  float ax, ay, vx, vy, x, y, t;
  
  SDL_Renderer *screen;
  SDL_Rect destrect, srcrect;    
    
  vector<SDL_Texture *> bitmapTextures;
  vector<int> timeTextures;
    
public:
  Sprite(SDL_Renderer *newScreen, int newScreenW, int newScreenH)
  {
    screen=newScreen;
    screenW=newScreenW;
    screenH=newScreenH;
    dead=false;
  }

  bool isDead()
  {
    return dead;
  }

  void kill()
  {
    dead=true;
  }

  float getVelocity()
  {
    return vx;
  }

  bool contains(int xo, int yo)
  {
    return destrect.x<=xo && xo<=destrect.x+destrect.w && destrect.y<=yo && yo<=destrect.y+destrect.h;
  }
  
  bool collidesWith(Sprite *other)
  {
    return contains(other->destrect.x, other->destrect.y) || 
    contains(other->destrect.x+other->destrect.w, other->destrect.y) || 
    contains(other->destrect.x, other->destrect.y+other->destrect.h) || 
    contains(other->destrect.x+other->destrect.w, other->destrect.y+other->destrect.h);
  }
  
  virtual void read(string file, float offset)
  {
    SDL_Surface *bitmapSurface;
    ifstream in(file.c_str());
    string path;
    int red, green, blue;
  
    int n;
    in>>n>>red>>green>>blue>>path;
  
    for(int i=0;i<n;i++)
    {
      string filename;
      int time;
      stringstream s;
      in>>filename>>time;
      s<<path<<"/"<<filename;
      
      bitmapSurface= SDL_LoadBMP(s.str().c_str());
      timeTextures.push_back(time);
      totalTime+=time;
      
      int WhiteKey=SDL_MapRGB(bitmapSurface->format, red, green, blue);
      SDL_SetColorKey(bitmapSurface, SDL_TRUE, WhiteKey);
      SDL_Texture *bitmapText;
      bitmapText=SDL_CreateTextureFromSurface(screen, bitmapSurface);
      bitmapTextures.push_back(bitmapText);
      SDL_FreeSurface(bitmapSurface);  
    }

    t=(float)(rand()%1000);
    ax=0.0;
    ay=0.0;
    vx = -155.0; // this attribute should beproportional to the background acceleration and/or velocity
    vy = 80.0;
    destrect.x=0;
    destrect.y=0;
    destrect.w=2;
    destrect.h=12;
    
    x=rand()%(WindowWidth-destrect.w);
    y=rand()%(WindowHeight-destrect.h);
    in.close();
  }
  
  virtual void update(float dt, float offset, int a)
  {
    if(dead) 
      return;
    
    t+=1000.0*dt;
    vx+=ax*dt;
    vy+=ay*dt;
    x+=vx*dt;
    y+=vy*dt;
    
    if(x > screenW-destrect.w || x < 0)
      x = WindowWidth-20;

    if(y > screenH-destrect.h || y < 0)
    {
      y = 0;
      vy =- vy;
    }
  }

  void draw()
  {
    if(dead) 
      return;
    destrect.x=(int)x;
    destrect.y=(int)y;
    int ti=((int)t) % totalTime;
    int time=0;
    unsigned i;
    
    for(i=0;i<bitmapTextures.size();i++)
    {
      time+=timeTextures[i];
      if(ti<=time) 
        break;
    }
    
    if(i>=bitmapTextures.size()) 
      i=0;

    SDL_RenderCopy(screen, bitmapTextures[i], &srcrect, &destrect); // added srcrect)  
  }
  
  ~Sprite()
  {
    for(unsigned i=0;i<bitmapTextures.size();i++)
    { 
        SDL_DestroyTexture(bitmapTextures[i]);
    }
  }
};
