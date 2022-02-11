#pragma once
#include "Enemy.h"
#include "Sprites.h"

class Enemy0 : public Enemy {
public:
	Enemy0();

	void setSpeedX(const float newSpeed) { speedX = newSpeed; }
	void setLine(const int newLine) { line = newLine; }

	float getSpeedX() const { return speedX; }
	int getLine() const { return line; }

	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;

private:
	float speedX;
	class Sprites* sprites;
	int line;
};