#pragma once
#include "Bullet.h"
#include "Vecs.h"

class EnemyBullet : public Bullet {
public:
	EnemyBullet();

	void setSpeedX(const float newSX) { speedX = newSX; }
	void setSpeedY(const float newSY) { speedY = newSY; }
	void setBoss(const bool newB) { boss = newB; }

	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }

	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;
private:
	float speedY;
	float speedX;
	class Sprites* sprites;
	Vec4 sprite;
	bool boss;
};