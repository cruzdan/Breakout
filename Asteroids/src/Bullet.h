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
	SDL_Rect getRect() const { return rect; }
	void setRect(const int x, const int y, const int w, const int h) { rect = { x,y,w,h }; }
	float getSpeed() const { return speed; }
	void setSpeed(const float newSpeed) { speed = newSpeed; }

	void showBullet(SDL_Renderer* renderer);
	void moveBullet(float deltaTime);

private:
	double multiplicatorX; //distance to move the bullet in X
	double multiplicatorY; //distance to move the bullet in Y
	float angle;
	SDL_Rect rect;
	float speed;
};