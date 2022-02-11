#pragma once
#include "Enemy.h"
#include <vector>

class Enemy9 : public Enemy {
public:
	Enemy9();

	void setSpeedX(const float newSpeedX) { speedX = newSpeedX; }
	void setSpeedY(const float newSpeedY) { speedY = newSpeedY; }
	void setTimeShoot(const float time) { timeShoot = time; }
	void setShipTarget(class Ship* ship) { shipTarget = ship; }
	void setBullets(std::vector<class Bullet*>* newBullets) { bullets = newBullets; }
	void setMovement(const int newM) { movement = newM; }

	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }
	int getMovement() const { return movement; }


	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;
private:
	void shootEnemyBullet();
	float speedX;
	float speedY;
	float timer;
	float timeShoot;
	class Sprites* sprites;
	std::vector<class Bullet*>* bullets;
	class Ship* shipTarget;
	bool stop;
	//0->follow ship, 1->move up and down
	int movement;
};