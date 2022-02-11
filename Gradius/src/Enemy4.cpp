// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemy4.h"
#include "Sprites.h"
#include "Textures.h"

Enemy4::Enemy4(): 
	Enemy(),
	speedX(0),
	center(0),
	longitude(0),
	sprites(nullptr)
{
	sprites = new Sprites();
	sprites->setTimeNext(0.25);
}

void Enemy4::update(float deltaTime) {
	sprites->update(deltaTime);
	x += speedX * deltaTime;
	y = center - (float)(longitude * abs(sin(((double)endX - x / 2) * M_PI / 180)));
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

void Enemy4::show(SDL_Renderer* renderer) {
	Vec4 p = sprites->getActualSprite();
	SDL_Rect spriteRect = { p.x, p.y, p.w, p.h };
	SDL_Rect showRect = { (int)x,(int)y, w, h };
	SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &showRect);
}

void Enemy4::setSprites() {
	if (upgrade) {
		//red sprites
		sprites->addSprite(253, 45, 16, 16);
		sprites->addSprite(272, 45, 16, 16);
		sprites->addSprite(294, 45, 16, 16);
		sprites->addSprite(311, 45, 16, 16);
	}
	else {
		//blue sprites
		sprites->addSprite(173, 45, 16, 16);
		sprites->addSprite(192, 45, 16, 16);
		sprites->addSprite(214, 45, 16, 16);
		sprites->addSprite(231, 45, 16, 16);
	}
}