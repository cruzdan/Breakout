#pragma once
#include <SDL.h>
extern SDL_Rect paddle;
extern int paddleSpeed;
void centerPaddle();
void movePaddleRight();
void movePaddleLeft();
void initPaddle();
void setWindowPaddleCoordinates(int percentageX);
void getActualPadddleCoordinates(int* x);
void incrementPaddleSpeed();
void decrementPaddleSpeed();
void updatePaddle();
int getMultiplicatorPaddleSpeed();
void setMultiplicatorPaddleSpeed(int paddleMultiplicator);