#pragma once

#include <SDL.h>
#include <stdlib.h>
#include <time.h>

struct Capsule {
	SDL_Rect rect;
	int type;
};
extern int actualCapsules;
extern Capsule* capsules;
extern int actualBullets;
extern SDL_Rect* bullets;
extern SDL_Rect textShootTimerRect;
extern bool paddleShoot;

void initRandom();
void initCapsuleVariables(SDL_Renderer* renderer);
void initCapsules(int total, int max);
void checkBrickWithCapsule(int index);
void updateCapsules(SDL_Renderer* renderer);
void showCapsules(SDL_Renderer* renderer);
void restartCapsules();
void restartBullets();
void closeCapsule();
void updateBullets(SDL_Renderer* renderer, int time);
void showBullets(SDL_Renderer* renderer);
void shoot();
SDL_Point* getActualCapsulePercentages(SDL_Point* percentages);
void resizeCapsules();
SDL_Point* getActualBulletPercentages(SDL_Point* percentages);
void resizeBullets();
void showTextScore(SDL_Renderer* renderer);
void changeTextShootActiveText(int seconds, SDL_Renderer* renderer);