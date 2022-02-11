// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Missile.h"
#include "Textures.h"
#include "Mountain.h"
#include "Level.h"

Missile::Missile():
	Bullet(),
	speedX(0),
	speedY(0),
	angle(0),
	state(1),
	id(0),
	mountain(nullptr),
	level(nullptr)
{
	mountain = new Mountain();
}

void Missile::moveRight(float deltaTime) {
	x += speedX * deltaTime;
}

void Missile::moveDown(float deltaTime) {
	y += speedY * deltaTime;
}

void Missile::checkOutOfScreen() {
	if (x > endX)
		dead = true;
	else if (y > endY)
		dead = true;
}

void Missile::update(float deltaTime) {
	int actualX = (int)(level->getProgress() + (x + (float)w) / (endX / 14));
	int actualY = (int)((y + h / 2) / (endY / 13) + 1);
	int downY = (int)((y + h / 2 + speedY * deltaTime) / (endY / 13) + 1);
	int mountainIndex = mountain->getCollisionIndexOnRate(actualX, 14);
	if (mountainIndex > -1) {
		int rightX = (int)(level->getProgress() + (x + speedX * deltaTime + (float)w) / (endX / 14));
		int newState = mountain->getMissileStateMap(actualX, actualY, rightX, downY, mountainIndex);
		if (newState > -1) {
			state = newState;
		}
		else {
			dead = true;
		}
	}
	if (downY >= 13 && actualX >= 64 && actualX <= 207)
		state = 0;
	if (actualX >= 208)
		state = 1;

	moveRight(deltaTime);
	if (state == 1)
		moveDown(deltaTime);
	checkOutOfScreen();
}

void Missile::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect = { 21,53,7,3 };
	SDL_Rect bulletRect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, shipTexture, &spriteRect, &bulletRect);
}