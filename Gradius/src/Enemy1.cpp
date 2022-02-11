// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemy1.h"
#include "Textures.h"

Enemy1::Enemy1():
	Enemy(),
	speedX(0),
	speedY(0),
	limitUpY(0),
	limitDownY(0),
	sRects(),
	actualSprite(0)
{

}

void Enemy1::update(float deltaTime) {
	x += speedX * deltaTime;
	y += speedY * deltaTime;
	if (speedY < 0) {
		if (y < limitUpY) {
			speedY = -speedY;
			actualSprite = 1;
		}
	}
	else {
		if (y + h > limitDownY) {
			speedY = -speedY;
			actualSprite = 0;
		}
	}
	if (speedX > 0) {
		if (x > endX) {
			dead = true;
		}
	}
	else {
		if (x + w < firstX) {
			dead = true;
		}
	}
}

void Enemy1::show(SDL_Renderer* renderer) {
	SDL_Rect showRect = { (int)x, (int)y, w, h };
	SDL_Rect spriteRect = { sRects[actualSprite].x,sRects[actualSprite].y,sRects[actualSprite].w,sRects[actualSprite].h };
	SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &showRect);
}

void Enemy1::addSpriteRect(int x, int y, int w, int h, int index) {
	sRects[index] = { x,y,w,h };
}

void Enemy1::setSprites() {
	if (upgrade) {
		//red sprite up
		sRects[0] = { 102,27,16,16 };
		//red sprite down
		sRects[1] = { 63,27,16,16 };
	}
	else {
		//blue sprite up
		sRects[0] = { 44,27,16,16 };
		//blue sprite down
		sRects[1] = { 5,27,16,16 };
	}
}

void Enemy1::setActualSprite() {
	if (speedY > 0)
		actualSprite = 1;
	else
		actualSprite = 0;
}