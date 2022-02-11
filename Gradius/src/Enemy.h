#pragma once
#include <SDL.h>

class Enemy {
public:
	Enemy();
	void setX(const float newX) { x = newX; }
	void setY(const float newY) { y = newY; }
	void setW(const int newW) { w = newW; }
	void setH(const int newH) { h = newH; }
	void setfirstX(const int newFirstX) { firstX = newFirstX; }
	void setfirstY(const int newFirstY) { firstY = newFirstY; }
	void setEndX(const int newEndX) { endX = newEndX; }
	void setEndY(const int newEndY) { endY = newEndY; }
	void setDead(const bool newDead) { dead = newDead; }
	void setScore(const int newScore) { score = newScore; }
	void setLifes(const int newLifes) { lifes = newLifes; }
	void setUpgrade(const bool newUpgrade) { upgrade = newUpgrade; }

	float getX() const { return x; }
	float getY() const { return y; }
	int getW() const { return w; }
	int getH() const { return h; }
	int getFirstX() const { return firstX; }
	int getFirstY() const { return firstY; }
	int getEndX() const { return endX; }
	int getEndY() const { return endY; }
	bool getDead() const { return dead; }
	int getScore() const { return score; }
	int getLifes() const { return lifes; }
	bool getUpgrade() const { return upgrade; }

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
	//score when the enemy dies
	int score;
	int lifes;
	bool upgrade;
};