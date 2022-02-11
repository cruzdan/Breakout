// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "InclinedBullet.h"
#include "Textures.h"

InclinedBullet::InclinedBullet() :
	Bullet(),
	speedX(0),
	speedY(0)
{

}

void InclinedBullet::update(float deltaTime) {
	x += speedX * deltaTime;
	y += speedY * deltaTime;

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

void InclinedBullet::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect = { 47,51,6,6 };
	SDL_Rect bulletRect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, shipTexture, &spriteRect, &bulletRect);
}

void InclinedBullet::setSpeed(int speed, int newAngle) {
	speedX = (float)(cos(newAngle * M_PI / 180) * speed);
	speedY = -(float)(sin(newAngle * M_PI / 180) * speed);
}