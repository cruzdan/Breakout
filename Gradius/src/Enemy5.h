#pragma once
#include "Enemy.h"
#include <vector>
#include "Vecs.h"

class Enemy5 : public Enemy {
public:
	Enemy5();

	void setSpeedX(const float newSpeedX) { speedX = newSpeedX; }
	void setSpeedY(const float newSpeedY) { speedY = newSpeedY; }
	void setPaused(const bool newPaused) { paused = newPaused; }
	void setMovement(const int newMovement) { movement = newMovement; }
	void setTopY(const int newTY) { topY = newTY; }
	void setLastTopX(const int newLTX) { lastTopX = newLTX; }
	void setBottomY(const int newBottom) { bottomY = newBottom; }
	void setMountainIndex(const int newMI) { mountainIndex = newMI; }
	void setCoordFirstMountainX(const int newCoord) { coordFirstMountainX = newCoord; }
	void setCoordReverseFirstMountainX(const int newCoord) { coordReverseFirstMountainX = newCoord; }
	void setLevel(class Level* newLevel) { level = newLevel; }
	void setSizeCoordX(const float newSize) { sizeCoordX = newSize; }
	void setSizeCoordY(const float newSize) { sizeCoordY = newSize; }
	void setPausedSpeedX(const float speed) { pausedSpeedX = speed; }
	void setTimeShoot(const float time) { timeShoot = time; }
	void setReverseLastTopX(const int newLTX) { reverseLastTopX = newLTX; }
	void setShipTarget(class Ship* ship) { shipTarget = ship; }
	void setBullets(std::vector<class Bullet*>* newBullets) { bullets = newBullets; }
	void setUp(const bool newUp) { up = newUp; }

	float getSpeedX() const { return speedX; }
	float getSpeedY() const { return speedY; }
	bool getPaused() const { return paused; }
	int getMovement() const { return movement; }
	int getTopY() const { return topY; }
	int getLastTopX() const { return lastTopX; }
	int getBottomY() const { return bottomY; }
	int getMountainIndex() const { return mountainIndex; }
	int getCoordFirstMountainX() const { return coordFirstMountainX; }
	int getCoordReverseFirstMountainX() const { return coordReverseFirstMountainX; }
	float getPausedSpeedX() const { return pausedSpeedX; }
	int getReverseLastTopX() const { return reverseLastTopX; }
	bool getUp() const { return up; }

	void update(float deltaTime) override;
	void show(SDL_Renderer* renderer) override;
	void setSprites();
private:
	void checkClimbMountain();
	void climb(float deltaTime);
	void checkLastXTopMountain();
	void down(float deltaTime);
	void shootEnemyBullet();
	
	float speedX;
	float speedY;
	bool paused;
	//0->horizontal,1->climb,2->top mountain, 3->down mountain
	int movement;
	int mountainIndex;
	//coordinate y of the mountain to tart to climb the mountain
	int topY;
	//coordinate x of the mountain to move horizontal on the top of the mountain and start down the mountain
	int lastTopX;
	//coordinate y to down the mountain and start to move horizontal
	int bottomY;
	//coordinate to start to climb the mountain
	int coordFirstMountainX;
	//indicates is the enemy had climbed the mountain
	bool climbed;
	float sizeCoordX;
	float sizeCoordY;
	class Level* level;
	float pausedSpeedX;
	float timer;
	float timeShoot;
	//number of bullets shooted
	int shoots;
	//coordinate to start to climb the mountain when the enemy is returning
	int coordReverseFirstMountainX;
	//coordinate x of the mountain to move horizontal on the top of the mountain and start down the mountain when the enemy is returning
	int reverseLastTopX;
	class Ship* shipTarget;
	std::vector<class Bullet*>* bullets;
	class Sprites* sprites;
	Vec4 sprite;
	bool up;
};