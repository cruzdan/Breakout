// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Sprites.h"

Sprites::Sprites() :
	sprites(),
	timer(0),
	timeNext(0),
	index(0)
{

}

void Sprites::changeIndex() {
	int a = (int)sprites.size();
	if (index < a - 1) {
		index++;
	}
	else {
		index = 0;
	}
}

void Sprites::addSprite(int x, int y, int w, int h) {
	Vec4 rect = { x,y,w,h };
	sprites.push_back(rect);
}

void Sprites::update(float deltaTime) {
	timer += deltaTime;
	if (timer >= timeNext) {
		changeIndex();
		timer = 0;
	}
}

Vec4 Sprites::getActualSprite() {
	return sprites.at(index);
}

void Sprites::clearSprites() {
	sprites.clear();
}