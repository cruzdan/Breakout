// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemy7.h"
#include "EnemyBullet.h"
#include "Ship.h"
#include "Sprites.h"
#include "Textures.h"

Enemy7::Enemy7() :
	Enemy(),
	speedX(0),
	speedY(0),
	timer(0),
	timeShoot(0),
	shipTarget(nullptr),
	bullets(),
	sprites(nullptr),
	paused(false)
{
	sprites = new Sprites();
	sprites->setTimeNext(0.25);
	sprites->addSprite(68, 5, 16, 16);
	sprites->addSprite(86, 5, 16, 16);
	sprites->addSprite(104, 5, 16, 16);
	sprites->addSprite(123, 5, 16, 16);
}

void Enemy7::update(float deltaTime) {
	sprites->update(deltaTime);
	x += speedX * deltaTime;
	if (!paused) {
		y += speedY * deltaTime;
		if (speedY > 0) {
			if ((y + h / 2) > (shipTarget->getY() + shipTarget->getH() / 2)) {
				paused = true;
			}
		}
		else {
			if ((y + h / 2) < (shipTarget->getY() + shipTarget->getH() / 2)) {
				paused = true;
			}
		}
	}
	else {
		timer += deltaTime;
		if (timer >= timeShoot) {
			shootEnemyBullet();
			timer = 0;
		}
	}
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

void Enemy7::show(SDL_Renderer* renderer) {
	Vec4 p = sprites->getActualSprite();
	SDL_Rect spriteRect = { p.x,p.y,p.w,p.h };
	SDL_Rect showRect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &showRect);
}

void Enemy7::shootEnemyBullet() {

	float distanceX = (shipTarget->getX() + shipTarget->getW() / 2) - (x + w / 2);
	float distanceY = (y + h / 2) - (shipTarget->getY() + shipTarget->getH() / 2);
	float angle = distanceY / distanceX;

	EnemyBullet* bull = new EnemyBullet();

	bull->setW(w / 3);
	bull->setH(h / 3);
	bull->setfirstX(firstX);
	bull->setfirstY(firstY + endY / 13);
	bull->setEndX(endX);
	bull->setEndY(endY - endY / 13);
	bull->setDamage(1);

	float speed = 15.0f * (float)bull->getW();
	if (distanceX > 0) {

		bull->setSpeedY((float)(-speed * sin(atan(angle))));
		bull->setSpeedX((float)(speed * cos(atan(angle))));
		bull->setX((float)(x + w / 2 + bull->getW() * cos(angle)));
		bull->setY((float)(y + h / 2 - bull->getH() * sin(angle)));
	}
	else {
		bull->setSpeedY((float)(speed * sin(atan(angle))));
		bull->setSpeedX((float)(-speed * cos(atan(angle))));
		bull->setX((float)(x + w / 2 - bull->getW() * cos(angle)));
		bull->setY((float)(y + h / 2 + bull->getH() * sin(angle)));
	}
	bullets->push_back(bull);
}