#include "Asteroid.h"
#include "Sprite.h"
#include "Game.h"
#include <iostream>

const double PI = 3.14159265;

Asteroid::Asteroid() :
	multiplicatorX(0),
	multiplicatorY(0),
	angle(0),
	speed(0),
	originalAngle(0),
	rect({ 0,0,0,0 })
{

}

void Asteroid::showAsteroid(SDL_Renderer* renderer) {
	SDL_RenderCopyEx(renderer, asteroidTexture, NULL, &rect, (int)angle, NULL, SDL_FLIP_NONE);
}

void Asteroid::moveAsteroid(float deltaTime) {
	rect.x += (int)(speed * multiplicatorX * deltaTime);
	rect.y += (int)(speed * multiplicatorY * deltaTime);
	angle += 3;
}