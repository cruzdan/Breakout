#pragma once
#include "Enemy.h"
#include "Vecs.h"
#include <vector>

class Enemy6 : public Enemy {
public:
	Enemy6();

	void setSpeedX(const float newSpeedX) { speedX = newSpeedX; }
	void setTimeShoot(const float time) { timeShoot = time; }
	void setEnemies(std::vector<class Enemy*>* newEnemies) { enemies = newEnemies; }
	void setShipTarget(class Ship* ship) { shipTarget = ship; }
	void setBullets(std::vector<class Bullet*>* newBullets) { bullets = newBullets; }
	void setUp(const bool newUp) { up = newUp; }

	float getSpeedX() const { return speedX; }
	float getTimeShoot() const { return timeShoot; }
	bool getUp() const { return up; }

	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;
	void setBlueSprite();
	void setRedSprite();

private:
	void addEnemy7();
	float speedX;
	float timer;
	float timeShoot;
	Vec4 sprite;
	class Ship* shipTarget;
	std::vector<class Enemy*>* enemies;
	std::vector<class Bullet*>* bullets;
	bool up;
};