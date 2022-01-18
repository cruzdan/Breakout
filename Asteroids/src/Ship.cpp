// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Ship.h"
#include "Game.h"
#include "Bullet.h"
#include "Sprite.h"

const double PI = 3.14159265;
const int MAX_BULLETS = 8;

Ship::Ship()
	:x(0.0),
	y(0.0),
	w(0),
	h(0),
	angle(0),
	speed(0),
	mulX(0),
	mulY(0),
	timerShip(0),
	maxSpeed(0),
	changeVel(0),
	changeAngle(4 * 60),
	bulletTimer(0),
	bulletsAvailable(1)
{

}

void Ship::detectKey(const Uint8* keys, float deltaTime) {
	if (keys[SDL_SCANCODE_SPACE]) {
		shoot();
	}
	if (keys[SDL_SCANCODE_A]) {
		angle -= changeAngle * deltaTime;
		if (angle < -360)
			angle += 360;
	}
	if (keys[SDL_SCANCODE_S]) {
		if (speed > -maxSpeed * deltaTime)
			speed -= changeVel * deltaTime;
		mulX = cos((angle - 90.0) * PI / 180);
		mulY = sin((angle - 90.0) * PI / 180);
	}
	if (keys[SDL_SCANCODE_D]) {
		angle += changeAngle * deltaTime;
		if (angle > 360)
			angle -= 360;
	}
	if (keys[SDL_SCANCODE_W]) {
		if (speed < maxSpeed * deltaTime)
			speed += changeVel * deltaTime;
		mulX = cos((angle - 90.0) * PI / 180);
		mulY = sin((angle - 90.0) * PI / 180);
	}
}

void Ship::show(SDL_Renderer* renderer) {
	SDL_Rect rect;
	rect.x = (int)x;
	rect.y = (int)y;
	rect.w = w;
	rect.h = h;
	SDL_RenderCopyEx(renderer, shipTexture, NULL, &rect, (int)angle, NULL, SDL_FLIP_NONE);
}

void Ship::decrementVelocity(float deltaTime) {
	if (speed != 0) {
		timerShip += deltaTime;
		if (speed < 0) {
			if (timerShip > 0.1) {
				if (speed > -changeVel * deltaTime)
					speed = 0;
				else
					speed += changeVel * deltaTime;
				timerShip = 0;
			}
		}
		else {
			if (timerShip > 0.1) {
				if (speed < changeVel * deltaTime)
					speed = 0;
				else
					speed -= changeVel * deltaTime;
				timerShip = 0;
			}
		}
	}
	else {
		timerShip = 0;
	}
}

void Ship::move() {
	if (speed != 0) {
		x += (float)(speed * mulX);
		y += (float)(speed * mulY);
	}
}

void Ship::shoot() {
	if (bulletsAvailable > 0 && shootTimer <= 0) {
		Bullet* bullet = new Bullet();
		float mulX = (float)cos((angle - 90.0) * PI / 180);
		float mulY = (float)sin((angle - 90.0) * PI / 180);
		int newW = w / 2;
		int newH = h / 2;
		float newX = (float)(x + w / 2 - newW / 2 + ((3 * h / 4) * mulX));
		float newY = (float)(y + h / 2 - newH / 2 + ((3 * h / 4) * mulY));
		bullet->setMulX(mulX);
		bullet->setMulY(mulY);
		bullet->setSpeed(w * 14.61f);
		bullet->setX(newX);
		bullet->setY(newY);
		bullet->setW(newW);
		bullet->setH(newH);
		bullet->setAngle(angle);

		addBullet(bullet);
		bulletsAvailable--;
		shootTimer = 0.05f;
	}
}

void Ship::incrementBullet(float deltaTime) {
	bulletTimer += deltaTime;
	if (bulletTimer > 0.25) {
		if (bulletsAvailable < MAX_BULLETS) {
			bulletsAvailable++;
			bulletTimer = 0;
		}
	}
}

void Ship::restartBullets() {
	if (bulletsAvailable < 2)
		bulletsAvailable = 2;
	bulletTimer = 0;

	while (bullets.size() > 0) {
		bullets.pop_back();
	}
}

//restart when all lifes are lost
void Ship::completeRestartBullets() {
	bulletsAvailable = 1;
}

void Ship::addBullet(class Bullet* bullet) {
	bullets.push_back(bullet);
}

void Ship::deleteBullet(class Bullet* bullet) {
	auto index = std::find(bullets.begin(), bullets.end(), bullet);
	if (index != bullets.end())
		bullets.erase(index);
}

void Ship::showMenuBullets(SDL_Renderer* renderer, int lastMenuX, int lastMenuY, int bulletW, int bulletH) {
	SDL_Rect bulletRect = { 0, lastMenuY - bulletH * 2, bulletW * 2, bulletH * 2 };
	for (int i = 0; i < bulletsAvailable; i++) {
		bulletRect.x = lastMenuX - (MAX_BULLETS - i) * bulletRect.w;
		SDL_RenderCopy(renderer, rocketTexture, NULL, &bulletRect);
	}
}

void Ship::downShipShoot(float deltaTime) {
	shootTimer -= deltaTime;
	if (shootTimer < 0) {
		shootTimer = 0;
	}
}