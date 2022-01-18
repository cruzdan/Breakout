#pragma once

#include <SDL.h>
#include <stdlib.h>
#include <time.h>
#include <vector>

class Capsule {
public:
	void setX(const float x) { mx = x; }
	void setY(const float y) { my = y; }
	void setWidth(const int w) { mw = w; }
	void setHeight(const int h) { mh = h; }
	void setType(const int type) { mtype = type; }
	float getX() const { return mx; }
	float getY() const { return my; }
	int getWidth() const { return mw; }
	int getHeight() const { return mh; }
	int getType() const { return mtype; }
private:
	float mx;
	float my;
	int mw;
	int mh;
	int mtype;
};

class Bullet {
public:
	void setX(const float x) { mx = x; }
	void setY(const float y) { my = y; }
	void setW(const int w) { mw = w; }
	void setH(const int h) { mh = h; }
	float getX() const { return mx; }
	float getY() const { return my; }
	int getW() const { return mw; }
	int getH() const { return mh; }
private:
	float mx;
	float my;
	int mw;
	int mh;
};

void deleteCapsuleElement(std::vector<class Capsule*>* caps, class Capsule* cap);
void deleteBulletElement(std::vector<class Bullet*>* bulls, class Bullet* bull);
extern int actualCapsules;
extern std::vector<class Capsule*> capsules;
extern int actualBullets;
extern std::vector<class Bullet*> bullets;
extern SDL_Rect textShootTimerRect;
extern bool paddleShoot;
void initRandom();
void initCapsuleVariables(SDL_Renderer* renderer);
void initCapsules(int total, int max);
void checkBrickWithCapsule(int index);
void updateCapsules(SDL_Renderer* renderer, float deltaTime);
void showCapsules(SDL_Renderer* renderer);
void restartCapsules();
void restartBullets();
void closeCapsule();
void updateBullets(SDL_Renderer* renderer, float time);
void showBullets(SDL_Renderer* renderer);
void shoot();
SDL_Point* getActualCapsulePercentages(SDL_Point* percentages);
void resizeCapsules();
SDL_Point* getActualBulletPercentages(SDL_Point* percentages);
void resizeBullets();
void showTextScore(SDL_Renderer* renderer);
void changeTextShootActiveText(int seconds, SDL_Renderer* renderer);