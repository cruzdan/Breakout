#pragma once
#include <SDL.h>
extern SDL_Rect brick;
extern int freeSizeY;
extern int freeSizeX;
extern int lastBrickY;
extern int initialBrickY;
extern int* brickLives;
extern int actualBricks;
const int totalRectanglesX = 14;
extern int totalRectanglesY;
extern int totalRectangles;
extern SDL_Rect* rectangles;
void createRectangles();
void initBrickImageType();
void showBricks(SDL_Renderer* renderer);
void initBrickLives();
void initBrickRows();
void initBrickTextures(SDL_Renderer* renderer);
