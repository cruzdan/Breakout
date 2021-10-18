#include "Bullet.h"
#include "Game.h"
#include "Ship.h"
#include "Sprite.h"
const double PI = 3.14159265;
Bullet::Bullet() :
	multiplicatorX(0),
	multiplicatorY(0),
	angle(0),
	rect({ 0,0,0,0 })
{

}

void Bullet::showBullet(SDL_Renderer* renderer) {
	SDL_RenderCopyEx(renderer, rocketTexture, NULL, &rect, angle, NULL, SDL_FLIP_NONE);
}

void Bullet::moveBullet(float deltaTime) {
	rect.x += (int)(speed * multiplicatorX * deltaTime);
	rect.y += (int)(speed * multiplicatorY * deltaTime);
}