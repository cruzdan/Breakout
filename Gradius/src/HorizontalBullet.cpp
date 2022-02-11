// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "HorizontalBullet.h"
#include "Textures.h"

HorizontalBullet::HorizontalBullet():
	Bullet(),
	speedX(0)
{

}

void HorizontalBullet::update(float deltaTime) {
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

void HorizontalBullet::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect = { 34,52,9,4 };
	SDL_Rect bulletRect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, shipTexture, &spriteRect, &bulletRect);
}