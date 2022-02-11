#pragma once
#include "Enemy.h"
#include <vector>

class Enemy3 : public Enemy {
public:
	Enemy3();
	
	void setSpeedX(const float newSpeed) { speedX = newSpeed; }
	void setShipTarget(class Ship* ship) { shipTarget = ship; }
	void setUp(const bool newUp) { up = newUp; }
	void setBullets(std::vector<class Bullet*>* newBullets) { bullets = newBullets; }

	float getSpeedX() const { return speedX; }
	bool getUp() const { return up; }

	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;

private:
	void shootEnemyBullet();

	float speedX;
	//timer to shoot a bullet
	float timer;
	bool up;
	class Ship* shipTarget;
	std::vector<class Bullet*>* bullets;
};