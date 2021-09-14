#pragma once
#include <SDL.h>
extern SDL_Texture* ballTexture;
extern SDL_Rect* ballRect;
extern int* ballSpeedX;
extern int* ballSpeedY;
extern int ballSpeedChangeX;
extern int maxBallSpeed;
extern int actualBalls;
void centerBall(int ballIndex);
void closeTextureBall();
void initBall();
void changeBallMovementWithBrick(SDL_Rect brick, int ballIndex);
void incrementBallSpeed();
void decrementBallSpeed();
SDL_Point* getBallSpeedMultiplicators(SDL_Point* ballMultiplicator);
void setMultiplicatorBallSpeed(SDL_Point* ballMultiplicator);
void initBallSpeed(int ballIndex);
void showBalls(SDL_Renderer* renderer);
void adNewBall();
void restartBall();
SDL_Point* getActualBallPercentages(SDL_Point* percentages);
void reziseBalls();