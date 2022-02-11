#pragma once
#include "Enemy.h"

class Enemy4 : public Enemy {
public:
	Enemy4();

	void setSpeedX(const float newSpeedX) { speedX = newSpeedX; }
	void setCenter(const int newCenter) { center = newCenter; }
	void setLongitude(const float newLongitude) { longitude = newLongitude; }

	float getSpeedX() const { return speedX; }
	int getCenter() const { return center; }
	float getLongitude() const { return longitude; }

	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;
	void setSprites();
private:
	float speedX;
	int center;
	//longitude of the enemy jump
	float longitude;
	class Sprites* sprites;
};