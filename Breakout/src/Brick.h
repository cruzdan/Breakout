#pragma once
#include <SDL.h>
extern SDL_Rect brick;
extern int freeSizeY;
extern int freeSizeX;
extern int lastBrickY;
extern int initialBrickY;
extern int brickLives[];
extern int actualBricks;
const int totalRectanglesX = 14;
const int totalRectanglesY = 8;
const int totalRectangles = totalRectanglesX * totalRectanglesY;
extern SDL_Rect rectangles[];
void createRectangles();
void showBricks();
void initBrickVariables();
void initBrickLives();
