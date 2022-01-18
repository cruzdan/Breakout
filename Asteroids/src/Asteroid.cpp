// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
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
	x(0.0),
	y(0.0),
	w(0),
	h(0)
{

}

void Asteroid::showAsteroid(SDL_Renderer* renderer) {
	SDL_Rect rect;
	rect.x = (int)x;
	rect.y = (int)y;
	rect.w = w;
	rect.h = h;
	SDL_RenderCopyEx(renderer, asteroidTexture, NULL, &rect, (int)angle, NULL, SDL_FLIP_NONE);
}

void Asteroid::moveAsteroid(float deltaTime) {
	x += (float)(speed * multiplicatorX * deltaTime);
	y += (float)(speed * multiplicatorY * deltaTime);
	angle += 3;
}