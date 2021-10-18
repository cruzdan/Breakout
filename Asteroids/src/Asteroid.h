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
	SDL_Rect getRect() const { return rect; }
	void setRect(const SDL_Rect rec) { rect = rec; }

	void showAsteroid(SDL_Renderer* renderer);
	void moveAsteroid(float deltaTime);
private:
	double multiplicatorX; // distance to move the asteroid in X
	double multiplicatorY; // distance to move the asteroid in Y
	float angle;
	float speed;
	float originalAngle;
	SDL_Rect rect;
};