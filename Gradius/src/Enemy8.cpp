// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemy8.h"
#include "Textures.h"
#include <cmath>

Enemy8::Enemy8() :
	Enemy(),
	speedX(0),
	speedY(0),
	center(0),
	longitude(0),
	stop(false),
	mountainX(0)
{

}

void Enemy8::update(float deltaTime) {
	x += speedX * deltaTime;
	if (!stop) {
		y = (float)(center - (longitude * abs(sin(((double)x - mountainX) * M_PI / 180))));
		if ((speedX > 0 && x - mountainX >= 180) || speedX < 0 && x - mountainX <= -180) {
			stop = true;
		}
	}
	else {
		y += speedY * deltaTime;
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
	if (y > endY) {
		dead = true;
	}
	else if (y + h < firstY) {
		dead = true;
	}
}

void Enemy8::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect = { 278,29,10,9 };
	SDL_Rect showRect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &showRect);
}