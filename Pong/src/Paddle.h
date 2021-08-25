#pragma once
#include <SDL.h>

extern SDL_Rect paddle1;
extern SDL_Rect paddle2;
//move the right paddle to the y coordinate of the ball with the same speed that paddle 1
void moveArtificialPaddle();
void movePaddleUp(SDL_Rect* paddle);
void movePaddleDown(SDL_Rect* paddle);
void centerPaddles();
void initPaddle();