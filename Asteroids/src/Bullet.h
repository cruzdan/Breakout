#pragma once
#include <SDL.h>

class Bullet {
public:
	Bullet();
	double getMulX() const { return multiplicatorX; }
	void setMulX(const double mul) { multiplicatorX = mul; }
	double getMulY() const { return multiplicatorY; }
	void setMulY(const double mul) { multiplicatorY = mul; }
	float getAngle() const { return angle; }
	void setAngle(const float ang) { angle = ang; }
	float getX() const { return x; }
	void setX(const float newX) { x = newX; }
	float getY() const { return y; }
	void setY(const float newY) { y = newY; }
	int getW() const { return w; }
	void setW(const int newW) { w = newW; }
	int getH() const { return h; }
	void setH(const int newH) { h = newH; }
	float getSpeed() const { return speed; }
	void setSpeed(const float newSpeed) { speed = newSpeed; }

	void showBullet(SDL_Renderer* renderer);
	void moveBullet(float deltaTime);

private:
	double multiplicatorX; //distance to move the bullet in X
	double multiplicatorY; //distance to move the bullet in Y
	float angle;
	float x;
	float y;
	int w;
	int h;
	float speed;
};