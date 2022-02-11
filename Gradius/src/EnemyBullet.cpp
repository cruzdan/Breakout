// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "EnemyBullet.h"
#include "Sprites.h"
#include "Textures.h"

EnemyBullet::EnemyBullet() :
	Bullet(),
	speedX(0),
	speedY(0),
	sprites(nullptr),
	sprite(),
	boss(false)
{
	sprites = new Sprites();
	sprites->setTimeNext(0.25);
	sprites->addSprite( 292,31,5,5 );
	sprites->addSprite(301, 31, 5, 5);

	//boos bullet
	sprite = { 58,52,15,4 };
}

void EnemyBullet::update(float deltaTime) {
	x += speedX * deltaTime;
	y += speedY * deltaTime;
	if(!boss)
		sprites->update(deltaTime);
	if (speedX > 0) {
		if (x > endX) {
			dead = true;
			return;
		}
	}
	else {
		if (x + w < firstX) {
			dead = true;
			return;
		}
	}
	if (speedY > 0) {
		if (y > endY) {
			dead = true;
			return;
		}
	}
	else {
		if (y + h < firstY) {
			dead = true;
			return;
		}
	}
}

void EnemyBullet::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect;
	SDL_Rect bulletRect = { (int)x,(int)y,w,h };
	if (!boss) {
		Vec4 p = sprites->getActualSprite();
		spriteRect = { p.x,p.y,p.w,p.h };
		SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &bulletRect);
	}
	else {
		spriteRect = { sprite.x,sprite.y,sprite.w,sprite.h };
		SDL_RenderCopy(renderer, shipTexture, &spriteRect, &bulletRect);
	}	
}