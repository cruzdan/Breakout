// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemy2.h"
#include "Sprites.h"
#include "Textures.h"

Enemy2::Enemy2(): 
	Enemy(),
	speedX(0),
	center(0),
	longitude(0),
	sprites()
{
	sprites = new Sprites();
	sprites->setTimeNext(0.25);
}

void Enemy2::update(float deltaTime) {
	sprites->update(deltaTime);
	x += speedX * deltaTime;
	y = (float)(longitude * sin(((double)endX - x) * M_PI / 180) + center);

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

void Enemy2::show(SDL_Renderer* renderer) {
	Vec4 p = sprites->getActualSprite();
	SDL_Rect spriteRect = { p.x,p.y,p.w,p.h };
	SDL_Rect showRect = { (int)x,(int)y, w, h };
	SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &showRect);
}

void Enemy2::setSprites() {
	if (upgrade) {
		sprites->addSprite(89, 47, 16, 16);
		sprites->addSprite(109, 47, 16, 16);
		sprites->addSprite(130, 47, 16, 16);
		sprites->addSprite(151, 47, 16, 16);
	}
	else {
		sprites->addSprite( 7,47,16,16 );
		sprites->addSprite(27, 47, 16, 16);
		sprites->addSprite(48, 47, 16, 16);
		sprites->addSprite(69, 47, 16, 16);
	}
}