#pragma once
extern int ballSpeedY;
void update(SDL_Renderer* renderer);
void initUpdateVariables();
void getLastBallSpeed(int* speedX);
void setNewBallSpeedWindow(int percentageX);
void incrementBallSpeedX();
void incrementBallSpeedY();
void decrementBallSpeedX();
void decrementBallSpeedY();