#pragma once

#include "Enemy.h"
class Enemy2 : public Enemy {
public:
	Enemy2();

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
	//center of the movement to oscillate in y
	int center;
	//distance to move the enemy for center to up or down 
	float longitude;
	class Sprites* sprites;
};