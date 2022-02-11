#pragma once
#include <SDL.h>
#include "Sprites.h"
class Shield {
public:
	Shield();

	void update(float deltaTime);
	void show(SDL_Renderer* renderer);

	void setX(const float newX) { x = newX; }
	void setY(const float newY) { y = newY; }
	void setW(const int newW) { w = newW; }
	void setH(const int newH) { h = newH; }
	void setLifes(const int newLifes) { lifes = newLifes; }
	void setBlueSprites();
	void setRedSprites();

	float getX() const { return x; }
	float getY() const { return y; }
	int getW() const { return w; }
	int getH() const { return h; }
	int getLifes() const { return lifes; }

	
private:
	float x;
	float y;
	int w;
	int h;
	int lifes;
	class Sprites* sprites;
};