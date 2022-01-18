#pragma once
extern SDL_Rect paddle;
extern float paddleSpeed;
void centerPaddle();
void movePaddleRight();
void movePaddleLeft();
void initPaddle();
void setWindowPaddleCoordinates(int percentageX);
void getActualPadddleCoordinates(int* x);
void incrementPaddleSpeed();
void decrementPaddleSpeed();
void updatePaddle(float deltaTime);
int getMultiplicatorPaddleSpeed();
void setMultiplicatorPaddleSpeed(int paddleMultiplicator);