#pragma once
#include <string>
extern bool serve;
extern int ballSpeedY;
extern SDL_Texture* ballImageTexture;
extern SDL_Rect ball;
extern int timer;
extern SDL_Texture* ballImageTexture;

void centerBall();
void moveBall(SDL_Renderer* renderer);
void initBall(SDL_Renderer* renderer);

void closeBall();
void start(int time);