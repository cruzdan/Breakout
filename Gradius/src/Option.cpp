// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Option.h"
#include "Textures.h"
#include "Sprites.h"

Option::Option() :
	x(0),
	y(0),
	w(0),
	h(0),
	hasMissile(false),
	route(),
	index(0),
	sprites(nullptr)
{
	sprites = new Sprites();
	sprites->setTimeNext(0.25);
	sprites->addSprite(93, 49, 16, 10);
	sprites->addSprite(77, 49, 16, 10);
}

void Option::addRoute(float mx, float my) {
	route.push_back({ mx,my });
}

void Option::update(float deltaTime) {
	sprites->update(deltaTime);
}

void Option::show(SDL_Renderer* renderer) {
	SDL_Rect spriteRect;
	Vec4 rect = sprites->getActualSprite();
	spriteRect.x = rect.x;
	spriteRect.y = rect.y;
	spriteRect.w = rect.w;
	spriteRect.h = rect.h;
	SDL_Rect optionRect = { (int)x,(int)y,w,h };
	SDL_RenderCopy(renderer, shipTexture, &spriteRect, &optionRect);
}

void Option::move(float newX, float newY) {
	updateRoute(newX, newY);
	updateIndex();
	x = route.at(index).x;
	y = route.at(index).y;
}

void Option::updateRoute(float newX, float newY) {
	route.at(index).x = newX;
	route.at(index).y = newY;
}

void Option::updateIndex() {
	int a = (int)route.size();
	if (index < a - 1) {
		index++;
	}
	else {
		index = 0;
	}
}