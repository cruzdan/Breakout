#pragma once
#include "Bullet.h"

class Laser : public Bullet {
public:
	Laser();
	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;
	void setSpeedX(const int newSpeed) { speedX = newSpeed; }
	int getSpeedX() const { return speedX; }
private:
	int speedX;
};