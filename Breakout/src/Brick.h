#pragma once
#include <SDL.h>
extern SDL_Rect brick;
extern int freeSizeY;
extern int freeSizeX;
const int totalRectanglesX = 15;
const int totalRectanglesY = 4;
const int totalRectangles = totalRectanglesX * totalRectanglesY;
extern SDL_Rect rectangles[];
extern bool brickStatus[];
void activateBricks();
void createRectangles();
void showBricks();
void initBrickVariables();