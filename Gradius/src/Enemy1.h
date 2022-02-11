#pragma once
#include "Enemy.h"
#include "Vecs.h"

class Enemy1 : public Enemy {
public:
	Enemy1();

	void setSpeedX(const float newSpeedX) { speedX = newSpeedX; }
	void setSpeedY(const float newSpeedY) { speedY = newSpeedY; }
	void setLimitUpY(const int limit) { limitUpY = limit; }
	void setLimitDownY(const int limit) { limitDownY = limit; }

	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }
	int getLimitUpY() const { return limitUpY; }
	int getLimitDownY() const { return limitDownY; }

	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;
	void addSpriteRect(int x, int y, int w, int h, int index);
	void setSprites();
	void setActualSprite();

private:
	float speedX;
	float speedY;
	int limitUpY;
	int limitDownY;
	Vec4 sRects[2];
	int actualSprite;
};