#pragma once
#include "Bullet.h"

class InclinedBullet : public Bullet {
public:
	InclinedBullet();
	
	void setSpeed(int speed, int angle);

	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;
private:
	float speedY;
	float speedX;
};