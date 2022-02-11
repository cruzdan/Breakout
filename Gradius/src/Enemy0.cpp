// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemy0.h"
#include "Textures.h"

Enemy0::Enemy0() :
	Enemy(),
	speedX(0),
	sprites(nullptr),
	line(0)
{
	sprites = new Sprites();
	sprites->setTimeNext(0.25);
	sprites->addSprite(6, 5, 13, 13);
	sprites->addSprite(27, 5, 13, 13);
	sprites->addSprite(49, 5, 13, 13);
}

void Enemy0::update(float deltaTime) {
	sprites->update(deltaTime);
	x += speedX * deltaTime;
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

void Enemy0::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect;
	Vec4 rect = sprites->getActualSprite();
	spriteRect.x = rect.x;
	spriteRect.y = rect.y;
	spriteRect.w = rect.w;
	spriteRect.h = rect.h;
	SDL_Rect showRect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &showRect);
}