// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemy6.h"
#include "Enemy7.h"
#include "Textures.h"

Enemy6::Enemy6():
	Enemy(),
	speedX(0),
	timer(0),
	timeShoot(0),
	sprite(),
	enemies(),
	up(false),
	shipTarget(nullptr),
	bullets(nullptr)
{

}

void Enemy6::update(float deltaTime) {
	x += speedX * deltaTime;
	timer += deltaTime;
	if (timer >= timeShoot) {
		addEnemy7();
		timer = 0;
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

void Enemy6::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect = { sprite.x,sprite.y,sprite.w,sprite.h };
	SDL_Rect showRect = { (int)x,(int)y,w,h };
	if(up)
		SDL_RenderCopyEx(renderer, enemyTexture2, &spriteRect, &showRect, 180, NULL,SDL_FLIP_NONE);
	else
		SDL_RenderCopy(renderer, enemyTexture2, &spriteRect, &showRect);
}

void Enemy6::setBlueSprite() {
	sprite = { 10, 8, 32, 28 };
}

void Enemy6::setRedSprite() {
	sprite = { 49, 8, 32, 28 };
}

void Enemy6::addEnemy7() {
	Enemy7* enemy = new Enemy7();
	enemy->setW(w / 2);
	enemy->setH(h / 2);
	enemy->setX(x + w / 2 - enemy->getW() / 2);
	if (up) {
		enemy->setY(y + h + enemy->getH());
		enemy->setSpeedY((float)(h * 2));
	}
	else {
		enemy->setY(y - enemy->getH());
		enemy->setSpeedY((float)(-h * 2));
	}
	enemy->setfirstX(0);
	enemy->setfirstY(0);
	enemy->setEndX(endX);
	enemy->setEndY(endY);
	enemy->setScore(100);
	enemy->setLifes(1);
	enemy->setSpeedX(speedX);
	enemy->setTimeShoot(1.0);
	enemy->setShipTarget(shipTarget);
	enemy->setBullets(bullets);
	enemies->push_back(enemy);
}