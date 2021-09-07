#include <SDL.h>
#include "Menu.h"
#include "Brick.h"
#include "GlobalVariables.h"

int freeSizeX;//space between two bricks in x position
int freeSizeY;//space between two bricks in y position
int lastBrickY;//the last pixel in y of the bricks
int initialBrickY;//the first pixel in y of the bricks
SDL_Rect rectangles[totalRectangles];// bricks on the board
SDL_Rect brick;
bool brickStatus[totalRectanglesX * totalRectanglesY];//indicates if the brick[i] is on the board or not

//put all the brick status in true
void activateBricks() {
	int pos;
	for (int j = 0; j < totalRectanglesY; j++) {
		for (int i = 0; i < totalRectanglesX; i++) {
			pos = i + j * totalRectanglesX;
			brickStatus[pos] = true;
		}
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
			if (brickStatus[pos])
				SDL_RenderFillRect(renderer, &rectangles[pos]);
		}
	}
}

void initBrickVariables() {
	freeSizeX = boardWidth / 225;
	freeSizeY = SCREEN_HEIGHT / 240;
	initialBrickY = (int)(SCREEN_HEIGHT * 0.19555);
}
