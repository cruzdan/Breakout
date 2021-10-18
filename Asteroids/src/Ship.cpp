#include "Ship.h"
#include "Game.h"
#include "Bullet.h"
#include "Sprite.h"

const double PI = 3.14159265;
const int MAX_BULLETS = 8;

Ship::Ship()
	:rect({ 0,0,0,0 }),
	angle(0),
	speed(0),
	mulX(0),
	mulY(0),
	timerShip(0),
	maxSpeed(0),
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
			angle += 360;//-(abs((int)angle) % 360);
	}
	if (keys[SDL_SCANCODE_S]) {
		if (speed > -maxSpeed * deltaTime)
			speed -= changeVel * deltaTime;
		mulX = cos((angle - 90) * PI / 180);
		mulY = sin((angle - 90) * PI / 180);
	}
	if (keys[SDL_SCANCODE_D]) {
		angle += changeAngle * deltaTime;
		if (angle > 360)
			angle -= 360;//(int)angle % 360;
	}
	if (keys[SDL_SCANCODE_W]) {
		if (speed < maxSpeed * deltaTime)
			speed += changeVel * deltaTime;
		mulX = cos((angle - 90) * PI / 180);
		mulY = sin((angle - 90) * PI / 180);
	}
}

void Ship::show(SDL_Renderer* renderer) {
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
		rect.x += (int)(speed * mulX);
		rect.y += (int)(speed * mulY);
	}
}

void Ship::shoot() {
	if (bulletsAvailable > 0) {
		Bullet* bullet = new Bullet();
		double mulX = cos((angle - 90) * PI / 180);
		double mulY = sin((angle - 90) * PI / 180);
		int rectW = rect.w / 2;
		int rectH = rect.h / 2;
		int rectX = rect.x + rect.w / 2 - rectW / 2 + (int)((3 * rect.h / 4) * mulX);
		int rectY = rect.y + rect.h / 2 - rectH / 2 + (int)((3 * rect.h / 4) * mulY);

		bullet->setMulX(mulX);
		bullet->setMulY(mulY);
		bullet->setSpeed(rect.w * 14.61f);
		bullet->setRect(rectX, rectY, rectW, rectH);
		bullet->setAngle(angle);

		addBullet(bullet);
		bulletsAvailable--;
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