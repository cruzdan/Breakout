// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemy3.h"
#include "Textures.h"
#include "Ship.h"
#include "Bullet.h"
#include "EnemyBullet.h"

Enemy3::Enemy3():
	Enemy(),
	speedX(0),
	timer(2),
	up(false),
	shipTarget(nullptr),
	bullets()
{

}

void Enemy3::shootEnemyBullet() {

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

void Enemy3::update(float deltaTime) {
	x += speedX * deltaTime;
	timer -= deltaTime;
	if (timer <= 0) {
		shootEnemyBullet();
		timer = 2;
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

void Enemy3::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect;
	SDL_Rect showRect = { (int)x,(int)y,w,h };

	float distanceX = (shipTarget->getX() + shipTarget->getW() / 2) - (x + w / 2);
	float distanceY = (y + h / 2) - (shipTarget->getY() + shipTarget->getH() / 2);
	float div = distanceY / distanceX;

	/*
	{ 161,4,16,16 }; down, 75°
    { 145,4,16,16 }; down, 45°
	{ 177,4,16,16 }; down, 0°
	*/


	if (distanceX > 0) {
		if (div > 1.732) {
			//enemy is down and is aim 75°
			spriteRect = { 161,4,16,16 };
			SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &showRect);
		}
		else if (div > 0.57773) {
			//enemy is down and is aim 45°
			spriteRect = { 145,4,16,16 };
			SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &showRect);
		}
		else if (div > -0.57773) {
			if (up) {
				//enemy is up and is aim 0°
				spriteRect = { 177,4,16,16 };
				SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 180, NULL, SDL_FLIP_HORIZONTAL);
			}
			else {
				//enemy is down and is aim 0°
				spriteRect = { 177,4,16,16 };
				SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &showRect);
			}
				
		}
		else if (div > -1.732) {
			//enemy is up and is aim -45°
			spriteRect = { 145, 4, 16, 16 };
			SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 180, NULL, SDL_FLIP_HORIZONTAL);
		}
		else {
			//enemy is up and is aim -75°
			spriteRect = { 161,4,16,16 };
			SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 180, NULL, SDL_FLIP_HORIZONTAL);
		}
	}
	else {
		if (div > 1.732) {
			//enemy is up and is aim 285°
			spriteRect = { 161,4,16,16 };
			SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 180, NULL, SDL_FLIP_NONE);
		}
		else if (div > 0.57773) {
			//enemy is up and is aim 225°
			spriteRect = { 145,4,16,16 };
			SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 180, NULL, SDL_FLIP_NONE);
		}
		else if (div > -0.57773) {
			if (up) {
				//enemy is up and is aim 180°
				spriteRect = { 177,4,16,16 };
				SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 180, NULL, SDL_FLIP_NONE);
			}
			else {
				//enemy is down and is aim 180°
				spriteRect = { 177,4,16,16 };
				SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 0, NULL, SDL_FLIP_HORIZONTAL);
			}
				
		}
		else if (div > -1.732) {
			//enemy is down and is aim 135°
			spriteRect = { 145,4,16,16 };
			SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
		else {
			//enemy is down and is aim 165°
			spriteRect = { 161,4,16,16 };
			SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 0, NULL, SDL_FLIP_HORIZONTAL);
		}
	}
}