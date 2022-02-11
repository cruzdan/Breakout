#pragma once
#include "Enemy.h"
class Enemy8 : public Enemy {
public:
	Enemy8();

	void setSpeedX(const float newSpeedX) { speedX = newSpeedX; }
	void setSpeedY(const float newSpeedY) { speedY = newSpeedY; }
	void setCenter(const int newCenter) { center = newCenter; }
	void setLongitude(const float newLongitude) { longitude = newLongitude; }
	void setStop(const bool newStop) { stop = newStop; }
	void setMountainX(const float newX) { mountainX = newX; }

	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }
	int getCenter() const { return center; }
	float getLongitude() const { return longitude; }
	bool getStop() const { return stop; }
	float getMountainX() const { return mountainX; }

	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;
private:
	float speedX;
	float speedY;
	float longitude;
	int center;
	bool stop;
	float mountainX;
};