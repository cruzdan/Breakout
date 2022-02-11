#pragma once
#include <SDL.h>

class Bullet {
public:
	Bullet();

	void setX(const float newX) { x = newX; }
	void setY(const float newY) { y = newY; }
	void setW(const int newW) { w = newW; }
	void setH(const int newH) { h = newH; }
	void setfirstX(const int newFirstX) { firstX = newFirstX; }
	void setfirstY(const int newFirstY) { firstY = newFirstY; }
	void setEndX(const int newEndX) { endX = newEndX; }
	void setEndY(const int newEndY) { endY = newEndY; }
	void setDead(const bool newDead) { dead = newDead; }
	void setDamage(const int newDamage) { damage = newDamage; }

	float getX() const { return x; }
	float getY() const { return y; }
	int getW() const { return w; }
	int getH() const { return h; }
	int getFirstX() const { return firstX; }
	int getFirstY() const { return firstY; }
	int getEndX() const { return endX; }
	int getEndY() const { return endY; }
	bool getDead() const { return dead; }
	int getDamage() const { return damage; }

	virtual void update(float deltaTime);
	virtual void show(SDL_Renderer* renderer);
protected:
	float x;
	float y;
	int w;
	int h;
	int firstX;
	int firstY;
	int endX;
	int endY;
	bool dead;
	int damage;
};