// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "ScrollBackground.h"
#include "Textures.h"

ScrollBackground::ScrollBackground():
	x(0),
	y(0),
	w(0),
	h(0),
	firstSpriteX(0),
	lastSpriteX(0),
	speed(0),
	spriteX(0),
	spriteY(0),
	spriteW(0),
	spriteH(0)
{

}

void ScrollBackground::update(float deltaTime) {
	spriteX += speed * deltaTime;
	if (spriteX > lastSpriteX) {
		spriteX = (float)firstSpriteX;
	}
}

void ScrollBackground::show(SDL_Renderer* renderer) {
	SDL_Rect backSpriteRect = { (int)spriteX,(int)spriteY,spriteW,spriteH };
	SDL_Rect rect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, levelOneTexture, &backSpriteRect, &rect);
}