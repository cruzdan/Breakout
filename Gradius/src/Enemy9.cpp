// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemy9.h"
#include "Sprites.h"
#include "Ship.h"
#include "EnemyBullet.h"
#include "Textures.h"

Enemy9::Enemy9() :
	Enemy(),
	speedX(0),
	speedY(0),
	timer(0),
	timeShoot(0),
	shipTarget(nullptr),
	bullets(),
	sprites(nullptr),
	stop(false),
	movement(0)
{
	sprites = new Sprites();
	sprites->setTimeNext(0.25);
	sprites->addSprite(11, 44, 48, 48);
	sprites->addSprite(128, 44, 48, 48);
}

void Enemy9::update(float deltaTime) {
	sprites->update(deltaTime);
	if(!stop){
		x += speedX * deltaTime;
		if (x < 2 * endX / 3) {
			stop = true;
		}
	}
	else {
		timer += deltaTime;
		if (timer >= timeShoot) {
			timer = 0;
			shootEnemyBullet();
		}
		if (movement == 0) {
			if (y + h / 2 - (shipTarget->getY() + shipTarget->getH() / 2) > 0) {
				//boos is below of ship
				y -= speedY * deltaTime;
			}
			else {
				//boos is above of ship
				y += speedY * deltaTime;
			}
		}
		else {
			y += speedY * deltaTime;
			if (speedY < 0) {
				if (y < firstY) {
					speedY = -speedY;
				}
			}
			else {
				if (y + h > endY) {
					speedY = -speedY;
				}
			}
		}
	}
}

void Enemy9::show(SDL_Renderer* renderer) {
	Vec4 p = sprites->getActualSprite();
	SDL_Rect spriteRect = { p.x,p.y,p.w,p.h };
	SDL_Rect showRect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, enemyTexture2, &spriteRect, &showRect);
}

void Enemy9::shootEnemyBullet() {

	EnemyBullet* bull1 = new EnemyBullet();
	EnemyBullet* bull2 = new EnemyBullet();
	EnemyBullet* bull3 = new EnemyBullet();
	EnemyBullet* bull4 = new EnemyBullet();


	bull1->setW(w / 3);
	bull1->setH(h / 12);
	bull1->setfirstX(firstX);
	bull1->setfirstY(firstY);
	bull1->setEndX(endX);
	bull1->setEndY(endY);
	bull1->setDamage(1);
	bull1->setBoss(true);
	bull1->setSpeedX(-15.0f * (float)bull1->getW());

	bull2->setW(w / 3);
	bull2->setH(h / 12);
	bull2->setfirstX(firstX);
	bull2->setfirstY(firstY);
	bull2->setEndX(endX);
	bull2->setEndY(endY);
	bull2->setDamage(1);
	bull2->setBoss(true);
	bull2->setSpeedX(-15.0f * (float)bull1->getW());

	bull3->setW(w / 3);
	bull3->setH(h / 12);
	bull3->setfirstX(firstX);
	bull3->setfirstY(firstY);
	bull3->setEndX(endX);
	bull3->setEndY(endY);
	bull3->setDamage(1);
	bull3->setBoss(true);
	bull3->setSpeedX(-15.0f * (float)bull1->getW());

	bull4->setW(w / 3);
	bull4->setH(h / 12);
	bull4->setfirstX(firstX);
	bull4->setfirstY(firstY);
	bull4->setEndX(endX);
	bull4->setEndY(endY);
	bull4->setDamage(1);
	bull4->setBoss(true);
	bull4->setSpeedX(-15.0f * (float)bull1->getW());
	
	bull1->setX(x);
	bull1->setY(y + (float)h * 0.0833f);
	bullets->push_back(bull1);

	bull2->setX(x - w);
	bull2->setY(y + (float)h * 0.3125f);
	bullets->push_back(bull2);

	bull3->setX(x - w);
	bull3->setY(y + (float)h * 0.6041f);
	bullets->push_back(bull3);

	bull4->setX(x);
	bull4->setY(y + (float)h * 0.8333f);
	bullets->push_back(bull4);
}