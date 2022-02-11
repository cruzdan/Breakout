#pragma once
#include <SDL.h>
#include <vector>
#include "Vecs.h"

class Ship {
public:
	Ship();

	void setX(const float newX) { x = newX; }
	void setY(const float newY) { y = newY; }
	void setW(const int newW) { w = newW; }
	void setH(const int newH) { h = newH; }
	void setDirection(const int newDir) { direction = newDir; }
	void setSpeedX(const float newSpeed) { speedX = newSpeed; }
	void setSpeedY(const float newSpeed) { speedY = newSpeed; }
	void setActualUpgrade(const int newAU) { actualUpgrade = newAU; }
	void setLifes(const int newLifes) { lifes = newLifes; }
	void setScore(const int newScore) { score = newScore; }
	void setfirstX(const int newFirstX) { firstX = newFirstX; }
	void setfirstY(const int newFirstY) { firstY = newFirstY; }
	void setEndX(const int newEndX) { endX = newEndX; }
	void setEndY(const int newEndY) { endY = newEndY; }
	void setKeyUp(const SDL_Scancode up) { keyUp = up; }
	void setKeyDown(const SDL_Scancode down) { keyDown = down; }
	void setKeyRight(const SDL_Scancode right) { keyRight = right; }
	void setKeyLeft(const SDL_Scancode left) { keyLeft = left; }
	void setKeyShoot(const SDL_Scancode shoot) { keyShoot = shoot; }
	void setKeySelectUpgrade(const SDL_Scancode select) { keySelectUpgrade = select; }
	void setMenuRect(int index, int x, int y, int w, int h);
	void setSpriteRect(int index, int x, int y, int w, int h);
	void setIncrementSpeedX(const float newSX) { incrementSpeedX = newSX; }
	void setIncrementSpeedY(const float newSY) { incrementSpeedY = newSY; }
	void setLevel(class Level* newLevel) { level = newLevel; }
	void setBulletTimer(const float newT) { bulletTimer = newT; }
	void setInvincible(const bool newI) { invincible = newI; }
	void setTimerInvincible(const float newT) { timerInvincible = newT; }
	void setTimeInvincible(const int newT) { timeInvincible = newT; }
	void setDead(const bool newD) { dead = newD; }

	float getX() const { return x; }
	float getY() const { return y; }
	int getW() const { return w; }
	int getH() const { return h; }
	int getDirection() const { return direction; }
	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }
	int getActualUpgrade() const { return actualUpgrade; }
	int getLifes() const { return lifes; }
	int getScore() const { return score; }
	int getFirstX() const { return firstX; }
	int getFirstY() const { return firstY; }
	int getEndX() const { return endX; }
	int getEndY() const { return endY; }
	Vec4 getMenuRect(int index);
	Vec4 getSpriteRect(int index);
	SDL_Texture* getMenuTexture(int index);
	float getIncrementSpeedX() const { return incrementSpeedX; }
	float getIncrementSpeedY() const { return incrementSpeedY; }
	bool getLaserUpgrade() const { return laserUpgrade; }
	bool getInvincible() const { return invincible; }
	float getTimerInvincible() const { return timerInvincible; }
	int getTimeInvincible() const { return timeInvincible; }
	bool getDead() const { return dead; }

	void update(float deltaTime);
	void show(SDL_Renderer* renderer);
	void detectKey(float deltaTime, const Uint8* keys);
	void addBullet(class Bullet* bullet);
	void deleteBullet(class Bullet* bullet);
	void addMissile(class Missile* missile);
	void deleteMissile(class Missile* missile);
	void moveShield();
	void addOption(float deltaTime);
	void deleteOption(class Option* option);
	void moveComponents();
	void getUpgrade();
	std::vector<class Bullet*> getBullets() { return bullets; }
	std::vector<class Missile*> getMissiles() { return missiles; }
	class Shield* getShield() const { return shield; }
	std::vector<class Option*> getOptions() { return options; }
	void changeLifeTexture(int height, SDL_Renderer* renderer);
	void changeScoreTexture(int height, SDL_Renderer* renderer);
	//init the life and score textures 
	void initMenuTexture(int height, SDL_Renderer* renderer);
	void decrementShieldUpgrade();
	void initUpgrades();
	void setYellowUpgrades();
	void clearBullets();
	void clearMissiles();
	void clearOptions();
private:
	void moveUp(int limit, float deltaTime);
	void moveDown(int limit, float deltaTime);
	void moveRight(int limit, float deltaTime);
	void moveLeft(int limit, float deltaTime);
	void shoot(float mx, float my);
	void shootHorizontalBullet(float mx, float my);
	void shootInclinedBullet(float mx, float my);
	void shootMissile(float mx, float my, int mId);
	void shootLaserBullet(float mx, float my);
	void updateBulletTimer(float deltaTime);
	void createOptionToShip(float deltaTime);
	void createOptionToOption(float deltaTime);
	void incrementSpeed();

	float x;
	float y;
	int w;
	int h;
	// 0->normal, 1->up, 2->down
	int direction; 
	float speedX;
	float speedY;
	float bulletTimer;
	int lifes;
	int score;
	//limits of ship's movement and bullets
	int firstX;
	int firstY;
	int endX;
	int endY;
	//indicates the actual index upgrade of the ship, -1 -> no upgrade
	int actualUpgrade;
	//indicates if a ship missile is on game
	bool hasMissile;
	SDL_Scancode keyUp;
	SDL_Scancode keyDown;
	SDL_Scancode keyRight;
	SDL_Scancode keyLeft;
	SDL_Scancode keyShoot;
	SDL_Scancode keySelectUpgrade;
	std::vector<class Bullet*> bullets;
	std::vector<class Missile*> missiles;
	class Shield* shield;
	std::vector<class Option*> options;
	/*
	Menu:
	0->speed
	1->missile
	2->double
	3->laser
	4->option
	5->shield
	6->lifes
	7->score
	*/
	Vec4 menuRects[8];
	Vec4 spriteRects[6];
	SDL_Texture* menuTextures[2];
	int maxUpgrades[6];
	int gettedUpgrades[6];
	float incrementSpeedX;
	float incrementSpeedY;
	bool missileUpgrade;
	bool doubleUpgrade;
	bool laserUpgrade;
	class Mountain* mountain;
	class Level* level;
	bool invincible;
	float timerInvincible;
	int timeInvincible;
	bool dead;
};