#pragma once
#include "Enemy.h"
#include <vector>

class Enemy7 : public Enemy {
public:
	Enemy7();

	void setSpeedX(const float newSpeedX) { speedX = newSpeedX; }
	void setSpeedY(const float newSpeedY) { speedY = newSpeedY; }
	void setTimeShoot(const float time) { timeShoot = time; }
	void setShipTarget(class Ship* ship) { shipTarget = ship; }
	void setBullets(std::vector<class Bullet*>* newBullets) { bullets = newBullets; }

	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }
	

	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;

private:
	void shootEnemyBullet();
	float speedX;
	float speedY;
	float timer;
	float timeShoot;
	class Ship* shipTarget;
	std::vector<class Bullet*>* bullets;
	class Sprites* sprites;
	bool paused;
};