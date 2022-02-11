#pragma once
#include <SDL.h>
class ScrollBackground {
public:
	ScrollBackground();
	void setX(const float newX) { x = newX; }
	void setY(const float newY) { y = newY; }
	void setW(const int newW) { w = newW; }
	void setH(const int newH) { h = newH; }
	void setFirstSpriteX(const int newX) { firstSpriteX = newX; }
	void setLastSpriteX(const int newX) { lastSpriteX = newX; }
	void setSpeed(const int newSpeed) { speed = newSpeed; }
	void setSpriteX(const float newX) { spriteX = newX; }
	void setSpriteY(const float newY) { spriteY = newY; }
	void setSpriteW(const int newW) { spriteW = newW; }
	void setSpriteH(const int newH) { spriteH = newH; }

	float getX() const { return x; }
	float getY() const { return y; }
	int getW() const { return w; }
	int getH() const { return h; }
	int getFirstSpriteX() const { return firstSpriteX; }
	int getLastSpriteX() const { return lastSpriteX; }
	int getSpeed() const { return speed; }
	float getSpriteX() const { return spriteX; }
	float getSpriteY() const { return spriteY; }
	int getSpriteW() const { return spriteW; }
	int getSpriteH() const { return spriteH; }

	void update(float deltaTime);
	void show(SDL_Renderer* renderer);
private:
	float x;
	float y;
	int w;
	int h;
	int firstSpriteX;
	int lastSpriteX;
	int speed;
	float spriteX;
	float spriteY;
	int spriteW;
	int spriteH;
};