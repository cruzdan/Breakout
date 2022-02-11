// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Shield.h"
#include "Textures.h"

Shield::Shield():
	x(0),
	y(0),
	w(0),
	h(0),
	lifes(0),
	sprites(nullptr)
{
	sprites = new Sprites();
	sprites->setTimeNext(0.25);
}

void Shield::setBlueSprites() {
	sprites->clearSprites();
	sprites->addSprite(113, 45, 8, 16);
	sprites->addSprite(124, 45, 8, 16);
	sprites->addSprite(134, 45, 8, 16);
	sprites->addSprite(144, 45, 8, 16);
}

void Shield::setRedSprites() {
	sprites->clearSprites();
	sprites->addSprite(156, 45, 8, 16);
	sprites->addSprite(167, 45, 8, 16);
	sprites->addSprite(177, 45, 8, 16);
	sprites->addSprite(187, 45, 8, 16);
}

void Shield::update(float deltaTime) {
	sprites->update(deltaTime);
}

void Shield::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect;
	Vec4 rect = sprites->getActualSprite();
	spriteRect.x = rect.x;
	spriteRect.y = rect.y;
	spriteRect.w = rect.w;
	spriteRect.h = rect.h;
	SDL_Rect showRect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, shipTexture, &spriteRect, &showRect);
}