// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL.h>
#include "Menu.h"
#include "Brick.h"
#include <stdlib.h>
#include "Render.h"
#include <vector>

int totalRectanglesY;
int totalRectangles;
int freeSizeX;//space between two bricks in x position
int freeSizeY;//space between two bricks in y position
int lastBrickY;//the last pixel in y of the bricks
int initialBrickY;//the first pixel in y of the bricks
std::vector<class Brick*> bricks; // bricks on game
int actualBricks;
SDL_Texture* brickTexture[10];

void initBrickTextures(SDL_Renderer* renderer) {
	loadImage(renderer, "images/bricks/beach.jpg", &brickTexture[0]);
	loadImage(renderer, "images/bricks/bulb.jpg", &brickTexture[1]);
	loadImage(renderer, "images/bricks/drop.jpg", &brickTexture[2]);
	loadImage(renderer, "images/bricks/drop-of-water.jpg", &brickTexture[3]);
	loadImage(renderer, "images/bricks/earth.jpg", &brickTexture[4]);
	loadImage(renderer, "images/bricks/green.jpg", &brickTexture[5]);
	loadImage(renderer, "images/bricks/lava.jpg", &brickTexture[6]);
	loadImage(renderer, "images/bricks/sand.jpg", &brickTexture[7]);
	loadImage(renderer, "images/bricks/steelwool.jpg", &brickTexture[8]);
	loadImage(renderer, "images/bricks/strawberry.jpg", &brickTexture[9]);
}

void resizeBricks() {
	int width = boardWidth / (totalRectanglesX + 1);
	int height = (int)(getScreenHeight() * 0.01777);
	freeSizeX = width / (totalRectanglesX + 1);
	freeSizeY = getScreenHeight() / 240;
	initialBrickY = (int)(getScreenHeight() * 0.19555);

	int pos = 0;
	for (int j = 0; j < totalRectanglesY; j++) {
		for (int i = 0; i < totalRectanglesX; i++) {
			pos = i + j * totalRectanglesX;
			bricks.at(pos)->setX((float)(i * width + (i + 1) * freeSizeX));
			bricks.at(pos)->setY((float)(j * height + (j + 1) * freeSizeY + initialBrickY));
			bricks.at(pos)->setW(width);
			bricks.at(pos)->setH(height);
		}
	}
	lastBrickY = (int)(bricks.at(pos)->getY() + height);
}

//assign the rectangle size and add them to rectangles
void createRectangles() {
	totalRectanglesY = level + rand() % 5;
	totalRectangles = totalRectanglesX * totalRectanglesY;
	actualBricks = totalRectangles;
	bricks.clear();
	Brick brick;
	brick.setW(boardWidth / (totalRectanglesX + 1));
	brick.setH((int)(getScreenHeight() * 0.01777));
	freeSizeX = brick.getW() / (totalRectanglesX + 1);
	freeSizeY = getScreenHeight() / 240;
	initialBrickY = (int)(getScreenHeight() * 0.19555);
	int pos = 0;
	for (int j = 0; j < totalRectanglesY; j++) {
		for (int i = 0; i < totalRectanglesX; i++) {
			pos = i + j * totalRectanglesX;
			brick.setX((float)(i * brick.getW() + (i + 1) * freeSizeX));
			brick.setY((float)(j * brick.getH() + (j + 1) * freeSizeY + initialBrickY));
			brick.setIndex(pos);
			brick.setLifes(1 + rand() % 2);
			brick.setType(rand() % 10);
			bricks.push_back(new Brick(brick));
		}
	}
	lastBrickY = (int)(bricks.at(pos)->getY() + bricks.at(pos)->getH());
}

void showBricks(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	for (int i = 0; i < totalRectangles; i++) {
		if (bricks.at(i)->getLifes() > 0) {
			SDL_Rect rect;
			rect.x = (int)bricks.at(i)->getX();
			rect.y = (int)bricks.at(i)->getY();
			rect.w = bricks.at(i)->getW();
			rect.h = bricks.at(i)->getH();
			SDL_RenderCopy(renderer, brickTexture[bricks.at(i)->getType()], NULL, &rect);
			SDL_RenderDrawRect(renderer, &rect);
		}
	}
}

void closeBrick() {
	for (int i = 0; i < 10; i++)
		SDL_DestroyTexture(brickTexture[i]);
}