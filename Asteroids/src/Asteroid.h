#pragma once
#include <SDL.h>
class Asteroid {
public:
	Asteroid();
	double getMulX() const { return multiplicatorX; }
	void setMulX(const double mul) { multiplicatorX = mul; }
	double getMulY() const { return multiplicatorY; }
	void setMulY(const double mul) { multiplicatorY = mul; }
	float getAngle() const { return angle; }
	void setAngle(const float ang) { angle = ang; }
	float getSpeed() const { return speed; }
	void setSpeed(const float num) { speed = num; }
	float getOriginalAngle() const { return originalAngle; }
	void setOriginalAngle(const float ang) { originalAngle = ang; }
	float getX() const { return x; }
	void setX(const float newX) { x = newX; }
	float getY() const { return y; }
	void setY(const float newY) { y = newY; }
	int getW() const { return w; }
	void setW(const int newW) { w = newW; }
	int getH() const { return h; }
	void setH(const int newH) { h = newH; }

	void showAsteroid(SDL_Renderer* renderer);
	void moveAsteroid(float deltaTime);
private:
	double multiplicatorX; // distance to move the asteroid in X
	double multiplicatorY; // distance to move the asteroid in Y
	float angle;
	float speed;
	float originalAngle;
	float x;
	float y;
	int w;
	int h;
};