#pragma once
#include "Bullet.h"
class HorizontalBullet : public Bullet {
public:
	HorizontalBullet();
	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;
	void setSpeedX(const int newSpeed) { speedX = newSpeed; }
	int getSpeedX() const { return speedX; }
private:
	int speedX;
};