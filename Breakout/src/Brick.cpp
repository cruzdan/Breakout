#include <SDL.h>
#include "Menu.h"
#include "Brick.h"
#include "GlobalVariables.h"
#include <stdlib.h>
#include "Image.h"

int totalRectanglesY;
int totalRectangles;
SDL_Rect brick;
int freeSizeX;//space between two bricks in x position
int freeSizeY;//space between two bricks in y position
int lastBrickY;//the last pixel in y of the bricks
int initialBrickY;//the first pixel in y of the bricks
SDL_Rect* rectangles;// bricks on the board
int* brickLives; //indicates the lives of the bricks
int* brickImageTypes;//indicates the type of image of the bricks
int actualBricks;

SDL_Texture* brickTexture;

void initBrickRows() {
	totalRectanglesY = level + rand() % 5;
	totalRectangles = totalRectanglesX * totalRectanglesY;
	rectangles = new SDL_Rect[totalRectangles];
	brickLives = new int[totalRectangles];
	brickImageTypes = new int[totalRectangles];
}

void initBrickLives() {
	actualBricks = totalRectangles;
	for (int i = 0; i < actualBricks; i++) {
		brickLives[i] = 1 + rand() % 2;
	}
}

//assign the rectangle size and add them to rectangles
void createRectangles() {
	brick.w = boardWidth / (totalRectanglesX + 1);
	brick.h = (int)(SCREEN_HEIGHT * 0.01777);
	freeSizeX = brick.w / (totalRectanglesX + 1);
	freeSizeY = SCREEN_HEIGHT / 240;
	initialBrickY = (int)(SCREEN_HEIGHT * 0.19555);
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

void initBrickImageType() {
	for (int i = 0; i < actualBricks; i++) {
		brickImageTypes[i] = rand() % 10;
	}
}

void showBricks(SDL_Renderer* renderer) {
	for (int i = 0; i < totalRectangles; i++) {
		if (brickLives[i] > 0) {
			switch (brickImageTypes[i]) {
			case 0:
				loadImage(renderer, &brickTexture, "images/bricks/beach.jpg");
				break;
			case 1:
				loadImage(renderer, &brickTexture, "images/bricks/bulb.jpg");
				break;
			case 2:
				loadImage(renderer, &brickTexture, "images/bricks/drop.jpg");
				break;
			case 3:
				loadImage(renderer, &brickTexture, "images/bricks/drop-of-water.jpg");
				break;
			case 4:
				loadImage(renderer, &brickTexture, "images/bricks/earth.jpg");
				break;
			case 5:
				loadImage(renderer, &brickTexture, "images/bricks/green.jpg");
				break;
			case 6:
				loadImage(renderer, &brickTexture, "images/bricks/lava.jpg");
				break;
			case 7:
				loadImage(renderer, &brickTexture, "images/bricks/sand.jpg");
				break;
			case 8:
				loadImage(renderer, &brickTexture, "images/bricks/steelwool.jpg");
				break;
			case 9:
				loadImage(renderer, &brickTexture, "images/bricks/strawberry.jpg");
				break;
			}
			SDL_RenderCopy(renderer, brickTexture, NULL, &rectangles[i]);
		}
	}
}


void closeBrick() {
	SDL_DestroyTexture(brickTexture);
	delete[] rectangles;
	delete[] brickLives;
	delete[] brickImageTypes;
}