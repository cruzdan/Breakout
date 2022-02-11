#pragma once
#include "Bullet.h"

class Missile : public Bullet {
public:
	Missile();

	void setSpeedX(const int newSpeedX) { speedX = newSpeedX; }
	void setSpeedY(const int newSpeedY) { speedY = newSpeedY; }
	void setAngle(const int newAngle) { angle = newAngle; }
	void setID(const int newId) { id = newId; }
	void setLevel(class Level* newLevel) { level = newLevel; }

	int getSpeedX() const { return speedX; }
	int getSpeedY() const { return speedY; }
	int getAngle() const { return angle; }
	int getID() const { return id; }

	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;
	void moveRight(float deltaTime);
	void moveDown(float deltaTime);
private:
	void checkOutOfScreen();
	int speedX;
	int speedY;
	int angle;
	//0->missile to right, 1->down and right
	int state;
	int id;
	class Mountain* mountain;
	class Level* level;
};