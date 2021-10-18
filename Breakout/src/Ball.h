#pragma once
#include <SDL.h>
extern SDL_Texture* ballTexture;
extern SDL_Rect* ballRect;
extern float* ballSpeedX;
extern float* ballSpeedY;
extern float ballSpeedChangeX;
extern float maxBallSpeed;
extern int actualBalls;
void centerBall(int ballIndex);
void closeTextureBall();
void initBall();
void changeBallMovementWithBrick(SDL_Rect brick, int ballIndex);
void incrementBallSpeed();
void decrementBallSpeed();
SDL_Point* getBallSpeedMultiplicators(SDL_Point* ballMultiplicator);
void setMultiplicatorBallSpeed(SDL_Point* ballMultiplicator);

float* getBallSpeedMultiplicatorsX(float* ballMultiplicatorX);
float* getBallSpeedMultiplicatorsY(float* ballMultiplicatorY);
void setMultiplicatorBallSpeed(float* ballMultiplicatorX, float* ballMultiplicatorY);

void initBallSpeed(int ballIndex);
void showBalls(SDL_Renderer* renderer);
void addNewBall();
void restartBall();
SDL_Point* getActualBallPercentages(SDL_Point* percentages);
void reziseBalls();