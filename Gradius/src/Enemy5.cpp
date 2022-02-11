// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemy5.h"
#include "Level.h"
#include "Textures.h"
#include "Ship.h"
#include "EnemyBullet.h"
#include "Sprites.h"
#include <cmath>

Enemy5::Enemy5() :
	Enemy(),
	speedX(0),
	speedY(0),
	paused(false),
	movement(0),
	topY(0),
	lastTopX(0),
	bottomY(0),
	mountainIndex(-1),
	coordFirstMountainX(0),
	climbed(false),
	level(nullptr),
	pausedSpeedX(0),
	timer(0),
	timeShoot(0),
	coordReverseFirstMountainX(0),
	reverseLastTopX(0),
	shipTarget(nullptr),
	sprites(nullptr),
	sprite(),
	up(false),
	bullets(),
	sizeCoordX(0),
	sizeCoordY(0),
	shoots(0)
{
	sprites = new Sprites();
	sprites->setTimeNext(0.25);
}

void Enemy5::update(float deltaTime) {
	if (!paused) {
		sprites->update(deltaTime);
		x += speedX * deltaTime;
		switch (movement) {
		case 0:
			checkClimbMountain();
			break;
		case 1:
			climb(deltaTime);
			break;
		case 2:
			checkLastXTopMountain();
			break;
		case 3:
			down(deltaTime);
			break;
		}
		if (x + w / 2 >= endX / 2) {
			paused = true;
		}
	}
	else {
		x += pausedSpeedX * deltaTime;
		timer += deltaTime;
		if (timer >= timeShoot) {
			shootEnemyBullet();
			timer = 0;
			paused = false;
			shoots++;
			if (shoots > 2) {
				speedX = -(speedX + speedX);
				if (climbed) {
					switch (movement) {
					case 0:
						climbed = false;
						coordFirstMountainX = coordReverseFirstMountainX;
						lastTopX = reverseLastTopX;
						break;
					case 1:
						movement = 3;
						break;
					case 2:
						lastTopX = reverseLastTopX;
						break;
					case 3:
						movement = 1;
						lastTopX = reverseLastTopX;
						break;
					}
				}
				else {
					coordFirstMountainX = coordReverseFirstMountainX;
				}
			}
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

void Enemy5::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect;
	SDL_Rect showRect = { (int)x,(int)y,w,h };

	if (paused) {
		spriteRect = { sprite.x,sprite.y,sprite.w,sprite.h };
		if (up) {
			if (x < shipTarget->getX()) {
				SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 180, NULL,SDL_FLIP_HORIZONTAL);
			}
			else {
				SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 180, NULL, SDL_FLIP_NONE);
			}
		}
		else {
			if (x < shipTarget->getX()) {
				SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &showRect);
			}
			else {
				SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 0, NULL, SDL_FLIP_HORIZONTAL);
			}
		}
	}
	else {
		Vec4 p = sprites->getActualSprite();
		spriteRect = { p.x,p.y,p.w,p.h };
		if (up) {
			if (speedX > 0) {
				SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 180, NULL, SDL_FLIP_HORIZONTAL);
			}
			else {
				SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 180, NULL, SDL_FLIP_NONE);
			}
		}
		else {
			if (speedX > 0) {
				SDL_RenderCopy(renderer, enemyTexture, &spriteRect, &showRect);
			}
			else {
				SDL_RenderCopyEx(renderer, enemyTexture, &spriteRect, &showRect, 0, NULL, SDL_FLIP_HORIZONTAL);
			}
		}
	}
}

void Enemy5::checkClimbMountain() {
	if (mountainIndex > -1 && !climbed) {
		float actualCoordinateX = level->getProgress() + (x + w / 2) / sizeCoordX;
		float actualCoordinateY = (y + h / 2) / sizeCoordY;
		//only to the enemies on the floor: y >= 10
		if (speedX > 0) {
			if (actualCoordinateX >= coordFirstMountainX && actualCoordinateY >= 10) {
				movement = 1;
				climbed = true;
			}
		}
		else {
			if (actualCoordinateX <= coordFirstMountainX && actualCoordinateY >= 10) {
				movement = 1;
				climbed = true;
			}
		}
	}
}

void Enemy5::climb(float deltaTime) {
	speedY = (float)-abs(speedY);
	y += speedY * deltaTime;
	float actualCoordinateY;
	if(mountainIndex == 1)
		actualCoordinateY = (y + h + sizeCoordY / 2) / sizeCoordY;
	else
		actualCoordinateY = (y + h) / sizeCoordY;
	if (actualCoordinateY <= topY) {
		movement = 2;
	}
}

void Enemy5::checkLastXTopMountain() {
	
	if (speedX > 0) {

		float actualCoordinateX;
		if(mountainIndex == 1)
			actualCoordinateX = level->getProgress() + (x + w - sizeCoordX) / sizeCoordX;
		else
			actualCoordinateX = level->getProgress() + (x + w) / sizeCoordX;
		if (actualCoordinateX >= lastTopX) {
			movement = 3;
		}
	}
	else {
		float actualCoordinateX;
		if(mountainIndex == 1)
			actualCoordinateX = level->getProgress() + (x + sizeCoordX) / sizeCoordX;
		else
			actualCoordinateX = level->getProgress() + x / sizeCoordX;
		if (actualCoordinateX <= lastTopX) {
			movement = 3;
		}
	}
}

void Enemy5::down(float deltaTime) {
	speedY = (float)abs(speedY);
	y += speedY * deltaTime;
	float actualCoordinateY = (y + h) / sizeCoordY;
	if (actualCoordinateY >= bottomY) {
		movement = 0;
	}
}

void Enemy5::shootEnemyBullet() {

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

		bull->setSpeedY(-speed * sin(atan(angle)));
		bull->setSpeedX(speed * cos(atan(angle)));
		bull->setX(x + w / 2 + bull->getW() * cos(angle));
		bull->setY(y + h / 2 - bull->getH() * sin(angle));
	}
	else {
		bull->setSpeedY(speed * sin(atan(angle)));
		bull->setSpeedX(-speed * cos(atan(angle)));
		bull->setX(x + w / 2 - bull->getW() * cos(angle));
		bull->setY(y + h / 2 + bull->getH() * sin(angle));
	}

	bullets->push_back(bull);
}

void Enemy5::setSprites() {
	if (upgrade) {
		sprites->addSprite(180, 27, 16, 16);
		sprites->addSprite(198, 27, 16, 16);
		sprite = { 217,27,16,16 };
	}
	else {
		sprites->addSprite(122, 27, 16, 16);
		sprites->addSprite(140, 27, 16, 16);
		sprite = { 159,27,16,16 };
	}
}