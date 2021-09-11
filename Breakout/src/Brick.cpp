#include <SDL.h>
#include "Menu.h"
#include "Brick.h"
#include "GlobalVariables.h"
#include <stdlib.h>

int freeSizeX;//space between two bricks in x position
int freeSizeY;//space between two bricks in y position
int lastBrickY;//the last pixel in y of the bricks
int initialBrickY;//the first pixel in y of the bricks
SDL_Rect rectangles[totalRectangles];// bricks on the board
SDL_Rect brick;
int brickLives[totalRectangles]; //indicates the lives of the bricks
int actualBricks;

void initBrickLives() {
	actualBricks = totalRectangles;
	for (int i = 0; i < totalRectangles; i++) {
		brickLives[i] = 1 + rand() % 2;
	}
}

//assign the rectangle size and add them to rectangles[]
void createRectangles() {
	//brick.w = (int)(boardWidth * 0.8) / totalRectanglesX;
	brick.w = boardWidth / 15;
	//the 60% of the middle of the window space is used to draw the rectangles
	brick.h = (int)(SCREEN_HEIGHT * 0.01777);
	int pos;
	for (int j = 0; j < totalRectanglesY; j++) {
		for (int i = 0; i < totalRectanglesX; i++) {
			pos = i + j * totalRectanglesX;
			brick.x = i * brick.w + (i + 1) * freeSizeX;
			brick.y = j * brick.h + (j + 1) * freeSizeY + initialBrickY;
			rectangles[pos] = brick;
		}
	}
	lastBrickY = rectangles[pos].y + rectangles[pos].h;
}

void showBricks() {
	extern SDL_Renderer* renderer;
	int pos;
	for (int j = 0; j < totalRectanglesY; j++) {
		for (int i = 0; i < totalRectanglesX; i++) {
			pos = i + j * totalRectanglesX;
			if (brickLives[pos] > 0)
				SDL_RenderFillRect(renderer, &rectangles[pos]);
		}
	}
}

void initBrickVariables() {
	freeSizeX = boardWidth / 225;
	freeSizeY = SCREEN_HEIGHT / 240;
	initialBrickY = (int)(SCREEN_HEIGHT * 0.19555);
}
