#pragma once
#include <SDL.h>
#include <vector>
#include "Ship.h"
#include "Level.h"

class Game {
public:
	Game();
	bool init();
	void loop();
	void close();
	
private:
	void update(float deltaTime);
	void show(SDL_Renderer* renderer);
	void addShip(class Ship* ship);
	void deleteShip(class Ship* ship);
	void addEnemy(class Enemy* enemy);
	void deleteEnemy(class Enemy* enemy);
	void addEnemy0(class Enemy0* enemy);
	void deleteEnemy0(class Enemy0* enemy);
	void addEnemy6(class Enemy6* enemy);
	void deleteEnemy6(class Enemy6* enemy);
	void addUpgrade(class Upgrade* upgrade);
	void deleteUpgrade(class Upgrade* upgrade);
	void deleteEnemyBullet(class Bullet* bullet);
	void updateLevelRoundsByTime(float deltaTime);
	void updateLevelRoundsByProgress(float deltaTime);
	void keyCP(const uint8_t* keys);
	void loadTextures(SDL_Renderer* renderer);
	void closeTextures();
	void generateUpgrade(float x, float y);
	void generateEnemy(EnemyData enemyData);
	void generateEnemy0(EnemyData enemyData);
	void generateEnemy1(EnemyData enemyData);
	void generateEnemy2(EnemyData enemyData);
	void generateEnemy3(EnemyData enemyData);
	void generateEnemy4(EnemyData enemyData);
	void generateEnemy5(EnemyData enemyData);
	void generateEnemy6(EnemyData enemyData);
	void generateEnemy8(EnemyData enemyData);
	void generateEnemy9();
	void checkBossDefeated();
	void addLevelEnemy0(int pos, int progress);
	//speed positive to indicate speed y to down, speed y to up in other case 
	void addLevelEnemy1(int progress, std::vector<int> upgrades, int speedY);
	void addLevelEnemy2(int progress, std::vector<int> upgrades);
	void checkCollisionEnemyToShip();
	void checkCollisionShipBulletsToEnemy();
	void checkCollisionShieldToEnemy();
	void checkCollisionUpgradeToShip();
	void checkCollisionEnemyBulletsToShip();
	void checkCollisionEnemyBulletsToShield();
	void checkShipMapCollision();
	void checkBulletMapCollision();
	void checkEnemyBulletMapCollision();
	void updateActualShipTarget();
	void moveBackgroundToMountains(float deltaTime);
	void moveBackgroundToBoss(float deltaTime);
	void partialRestart();
	void restart();

	SDL_Renderer* renderer;
	SDL_Window* window;
	Uint32 ticksCount;
	std::vector<class Ship*> ships;
	std::vector<class Enemy0*> enemies0;
	std::vector<class Enemy6*> enemies6;
	std::vector<class Enemy*> enemies;
	class Menu* menu;
	class ScrollBackground* background;
	class Level* level;
	//index to get an upgrade with the enemy 0
	int actualLine;
	//remaining enemies to get an upgrade
	int lineEnemies0[5];
	std::vector<class Upgrade*> upgrades;
	std::vector<class Bullet*> enemyBullets;
	int actualShipTarget;
	class Mountain* mountain;
	int deadPlayers;
};