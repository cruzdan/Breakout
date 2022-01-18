// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Bullet.h"
#include "Game.h"
#include "Ship.h"
#include "Sprite.h"
const double PI = 3.14159265;
Bullet::Bullet() :
	multiplicatorX(0),
	multiplicatorY(0),
	angle(0),
	speed(0),
	x(0.0),
	y(0.0),
	w(0),
	h(0)
{

}

void Bullet::showBullet(SDL_Renderer* renderer) {
	SDL_Rect rect;
	rect.x = (int)x;
	rect.y = (int)y;
	rect.w = w;
	rect.h = h;
	SDL_RenderCopyEx(renderer, rocketTexture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Bullet::moveBullet(float deltaTime) {
	x += (float)(speed * multiplicatorX * deltaTime);
	y += (float)(speed * multiplicatorY * deltaTime);
}