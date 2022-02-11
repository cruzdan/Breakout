// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Laser.h"
#include "Textures.h"

Laser::Laser() :
	Bullet(),
	speedX(0)
{

}

void Laser::update(float deltaTime) {
	x += speedX * deltaTime;
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

void Laser::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect = { 58,52,15,4 };
	SDL_Rect bulletRect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, shipTexture, &spriteRect, &bulletRect);
}