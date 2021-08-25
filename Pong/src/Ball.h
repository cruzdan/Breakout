#pragma once
extern bool serve;
extern int ballSpeedY;
extern SDL_Texture* ballImageTexture;
extern SDL_Rect ballImageRect;
extern SDL_Rect ball;
extern int timer;

void centerBall();
void moveBall();
void initBall();
void loadImageBall();
void closeBall();
void start(int time);