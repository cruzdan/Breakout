#pragma once
#include <SDL.h>
extern SDL_Texture* ballTexture;
extern SDL_Rect ballRect;
extern SDL_Surface* ballImage;
extern int ballSpeedX;
extern int ballSpeedY;
extern int ballSpeedChange;
extern int maxBallSpeed;
void centerBall();
void closeTextureBall();
void initBall();
void changeBallMovementWithBrick(SDL_Rect rect, SDL_Rect brick);
void incrementBallSpeedX();
void incrementBallSpeedY();
void decrementBallSpeedX();
void decrementBallSpeedY();
int getMultiplicatorBallSpeed();
void setMultiplicatorBallSpeed(int balleMultiplicator);