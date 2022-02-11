#pragma once
#include "SDL.h"

class Upgrade {
public:
	Upgrade();

	void setX(const float newX) { x = newX; }
	void setY(const float newY) { y = newY; }
	void setW(const int newW) { w = newW; }
	void setH(const int newH) { h = newH; }
	void setSpeed(const float newSpeed) { speedX = newSpeed; }
	void setfirstX(const int newFirstX) { firstX = newFirstX; }
	void setEndX(const int newEndX) { endX = newEndX; }
	void setDead(const bool newDead) { dead = newDead; }

	float getX() const { return x; }
	float getY() const { return y; }
	int getW() const { return w; }
	int getH() const { return h; }
	float getSpeedX() const { return speedX; }
	int getFirstX() const { return firstX; }
	int getEndX() const { return endX; }
	bool getDead() const { return dead; }

	void update(float deltaTime);
	void show(SDL_Renderer* renderer);

private:
	float x;
	float y;
	int w;
	int h;
	float speedX;
	int firstX;
	int endX;
	bool dead;
	class Sprites* sprites;
};