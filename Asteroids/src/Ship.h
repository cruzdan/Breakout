#pragma once
#include <SDL.h>
#include <vector>

class Ship {
public:
	Ship();
	SDL_Rect getRect() const { return rect; }
	void setRect(const int x, const int y, const int w, const int h) { rect = { x,y,w,h }; }
	void setRectX(const int x) { rect.x = x; }
	void setRectY(const int y) { rect.y = y; }
	float getAngle() const { return angle; }
	void setAngle(const float ang) { angle = ang; }
	float getSpeed() const { return speed; }
	void setSpeed(const float newSpeed) { speed = newSpeed; }
	double getMulX() const { return mulX; }
	void setMulX(const double mul) { mulX = mul; }
	double getMulY() const { return mulY; }
	void setMulY(const double mul) { mulY = mul; }
	float getTimerShip() const { return timerShip; }
	void setTimerShip(const float timer) { timerShip = timer; }
	float getMaxSpeed() const { return maxSpeed; }
	void setMaxSpeed(const float speed) { maxSpeed = speed; }
	float getChangeAngle() const { return changeAngle; }
	void setChangeAngle(const float ang) { changeAngle = ang; }
	float getChangeVel() const { return changeVel; }
	void setChangeVel(const float vel) { changeVel = vel; }
	std::vector<class Bullet*> getBullets() { return bullets; }

	void detectKey(const Uint8* keys, float deltaTime);
	void show(SDL_Renderer* renderer);
	void decrementVelocity(float deltaTime);
	void move();

	void incrementBullet(float deltaTime);
	void restartBullets();
	void completeRestartBullets();
	void addBullet(class Bullet* bullet);
	void deleteBullet(class Bullet* bullet);
	void showMenuBullets(SDL_Renderer* renderer, int lastMenuX, int lastMenuY, int bulletW, int bulletH);

private:
	void shoot();
	SDL_Rect rect;
	float angle;
	float speed;
	double mulX;//static distance to move the ship in X
	double mulY;//static distance to move the ship in Y
	float timerShip;//timer to count the seconds to decrement the ship velocity
	float maxSpeed;
	float changeAngle;
	float changeVel;
	float bulletTimer;
	int bulletsAvailable;

	std::vector<class Bullet*> bullets;
};