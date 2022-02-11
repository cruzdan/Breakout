// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Upgrade.h"
#include "Sprites.h"
#include "Textures.h"

Upgrade::Upgrade():
	x(0),
	y(0),
	w(0),
	h(0),
	speedX(0),
	firstX(0),
	endX(0),
	dead(false),
	sprites(nullptr)
{
	sprites = new Sprites();
	sprites->setTimeNext(0.25);
	sprites->addSprite(7, 26, 16, 14);
	sprites->addSprite(27, 26, 16, 14);
	sprites->addSprite(47, 26, 16, 14);
}

void Upgrade::update(float deltaTime) {
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
	sprites->update(deltaTime);
}

void Upgrade::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect;
	Vec4 rect = sprites->getActualSprite();
	spriteRect.x = rect.x;
	spriteRect.y = rect.y;
	spriteRect.w = rect.w;
	spriteRect.h = rect.h;
	SDL_Rect showRect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, shipTexture, &spriteRect, &showRect);
}