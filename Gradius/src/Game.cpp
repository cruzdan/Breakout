// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL_image.h>
#include <SDL_mixer.h>
#include "Game.h"
#include "Render.h"
#include "Textures.h"
#include "Shield.h"
#include "Menu.h"
#include "ScrollBackground.h"
#include "Bullet.h"
#include "Missile.h"
#include "Upgrade.h"
#include "Mountain.h"
#include <time.h>
#include "Enemy.h"
#include "Enemy0.h"
#include "Enemy1.h"
#include "Enemy2.h"
#include "Enemy3.h"
#include "Enemy4.h"
#include "Enemy5.h"
#include "Enemy6.h"
#include "Enemy7.h"
#include "Enemy8.h"
#include "Enemy9.h"

Game::Game() :
	renderer(nullptr),
	window(nullptr),
	ticksCount(0),
	menu(nullptr),
	background(nullptr),
	level(nullptr),
	enemies(),
	enemies0(),
	ships(),
	actualLine(0),
	upgrades(),
	enemyBullets(),
	actualShipTarget(0),
	mountain(nullptr),
	enemies6(),
	deadPlayers(0)
{
	menu = new Menu();
	menu->setWidth(720);
	menu->setHieght(480);
	menu->setX((float)-menu->getWidth());
	menu->setBackgroundSpeed((float)menu->getWidth() / 6);
	menu->initPauseRects();

	background = new ScrollBackground();
	background->setX(0);
	background->setY(0);
	background->setW(menu->getWidth());
	background->setH((int)(menu->getHeight() * 0.89));
	background->setFirstSpriteX(288);
	background->setLastSpriteX(3616);
	background->setSpeed(32);
	background->setSpriteX(288);
	background->setSpriteY(16);
	background->setSpriteW(224);
	background->setSpriteH(208);

	level = new Level();
	mountain = new Mountain();
	level->addTotalPhaseRound(81);
	level->addTotalPhaseRound(0);

	std::vector<int> ups;
	std::vector<int> posit;
	EnemyData enemyData;

	for (int i = 1; i < 6; i++) {
		int m;
		if (i % 2 == 0) {
			m = 1;
		}
		else {
			m = 0;
		}
		addLevelEnemy0(m, i * 4);
	}


	for (int i = 1; i < 5; i++) {
		int m;
		if (i % 2 == 0) {
			m = 1;
		}
		else {
			m = -1;
		}
		addLevelEnemy1(i * 2 + 20, ups, m);
	}

	for (int i = 1; i < 4; i++) {
		int m;
		if (i % 2 == 0) {
			m = 1;
		}
		else {
			m = 0;
		}
		addLevelEnemy0(m, i * 3 + 28);
	}

	for (int i = 1; i < 4; i++) {
		int m;
		if (i % 2 == 0) {
			m = 1;
		}
		else {
			m = -1;
		}
		addLevelEnemy1(i * 2 + 37, ups, m);
	}

	addLevelEnemy2(45, ups);
	ups.clear();
	ups.push_back(0);
	ups.push_back(1);
	addLevelEnemy2(47, ups);
	ups.clear();
	addLevelEnemy2(49, ups);


	ups.clear();
	for (int i = 1; i < 4; i++) {
		int m;
		if (i % 2 == 0) {
			m = 1;
		}
		else {
			m = -1;
		}
		addLevelEnemy1(i * 2 + 50, ups, m);
	}

	enemyData.lifes = 1;
	posit.push_back(0);
	enemyData.positions = posit;
	enemyData.totalEnemies = 1;
	enemyData.type = 3;
	level->addProgressEnemyData({ 57,enemyData });
	level->addProgressEnemyData({ 58,enemyData });

	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	enemyData.totalEnemies = 1;
	enemyData.type = 4;
	ups.clear();
	ups.push_back(0);
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 59,enemyData });
	level->addProgressEnemyData({ 61,enemyData });


	ups.clear();
	addLevelEnemy1(65, ups, 1);
	addLevelEnemy1(67, ups, -1);

	enemyData.type = 5;
	enemyData.totalEnemies = 2;
	posit.clear();
	posit.push_back(0);
	posit.push_back(2);
	enemyData.positions = posit;
	level->addProgressEnemyData({ 68,enemyData });
	addLevelEnemy2(70, ups);
	ups.push_back(0);
	ups.push_back(1);
	addLevelEnemy2(72, ups);

	posit.clear();
	ups.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	enemyData.totalEnemies = 1;
	enemyData.type = 3;
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 74,enemyData });
	level->addProgressEnemyData({ 75,enemyData });

	ups.clear();
	posit.clear();
	enemyData.upgrade = ups;
	enemyData.lifes = 3;
	posit.push_back(2);
	enemyData.positions = posit;
	enemyData.type = 6;
	level->addProgressEnemyData({ 76,enemyData });
	addLevelEnemy2(78, ups);

	enemyData.type = 4;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 79,enemyData });

	ups.clear();
	ups.push_back(0);
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 80,enemyData });

	enemyData.type = 5;
	enemyData.totalEnemies = 2;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(0);
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 82,enemyData });

	ups.clear();
	addLevelEnemy2(84, ups);
	addLevelEnemy2(86, ups);
	addLevelEnemy2(88, ups);
	addLevelEnemy2(90, ups);
	addLevelEnemy2(92, ups);

	enemyData.type = 5;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(0);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 97,enemyData });

	enemyData.type = 5;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 99,enemyData });

	enemyData.type = 4;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	ups.push_back(0);
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 101,enemyData });

	ups.clear();
	addLevelEnemy1(103, ups, -1);
	addLevelEnemy1(105, ups, 1);
	addLevelEnemy1(107, ups, -1);

	addLevelEnemy2(109, ups);
	addLevelEnemy2(111, ups);

	enemyData.type = 3;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 113,enemyData });
	level->addProgressEnemyData({ 115,enemyData });

	enemyData.type = 6;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 3;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 117,enemyData });

	addLevelEnemy1(121, ups, -1);
	addLevelEnemy1(123, ups, 1);
	addLevelEnemy2(125, ups);
	addLevelEnemy2(127, ups);

	enemyData.type = 4;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 131,enemyData });

	addLevelEnemy1(133, ups, -1);
	addLevelEnemy2(135, ups);
	ups.push_back(0);
	ups.push_back(1);
	addLevelEnemy2(137, ups);

	enemyData.type = 5;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(0);
	enemyData.positions = posit;
	ups.clear();
	ups.push_back(0);
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 139,enemyData });

	ups.clear();
	addLevelEnemy1(141, ups, -1);

	enemyData.type = 5;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 144,enemyData });

	enemyData.type = 3;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(0);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 146,enemyData });
	level->addProgressEnemyData({ 147,enemyData });

	enemyData.type = 6;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 3;
	posit.clear();
	posit.push_back(0);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 149,enemyData });

	addLevelEnemy2(151, ups);
	ups.push_back(0);
	ups.push_back(1);
	addLevelEnemy2(153, ups);

	ups.clear();
	addLevelEnemy1(155, ups, -1);

	enemyData.type = 5;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 156,enemyData });

	enemyData.type = 5;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(0);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 158,enemyData });

	enemyData.type = 3;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 159,enemyData });

	ups.push_back(0);
	level->addProgressEnemyData({ 160, enemyData });

	enemyData.type = 6;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 3;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 161,enemyData });

	enemyData.type = 5;
	enemyData.totalEnemies = 2;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(0);
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 163,enemyData });

	enemyData.type = 5;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(0);
	enemyData.positions = posit;
	ups.clear();
	ups.push_back(0);
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 165,enemyData });

	enemyData.type = 4;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 167,enemyData });

	enemyData.type = 5;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(0);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 169,enemyData });

	enemyData.type = 4;
	enemyData.totalEnemies = 1;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(2);
	enemyData.positions = posit;
	ups.clear();
	ups.push_back(0);
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 171,enemyData });

	ups.clear();
	enemyData.upgrade = ups;
	level->addProgressEnemyData({ 173,enemyData });

	enemyData.type = 8;
	enemyData.totalEnemies = 2;
	enemyData.lifes = 1;
	posit.clear();
	posit.push_back(0);
	posit.push_back(1);
	enemyData.positions = posit;
	ups.clear();
	enemyData.upgrade = ups;

	srand((unsigned int)time(0));

	level->addTotalPhaseRound(100);
	for (int i = 0; i < 100; i++) {
		level->addTimeRound(0.25);
		level->addTimeEnemyData(enemyData);
	}
}

void Game::addLevelEnemy0(int pos, int progress) {
	EnemyData enemyData;
	std::vector<int> positions;
	std::vector<int> upgrades;
	int total = 4;

	for (int i = 0; i < total; i++) {
		positions.push_back(pos);
	}
	/*
	struct EnemyData {
	int type;
	int totalEnemies;
	//vector of size = total enemies, positions of the enemies: up,middle,down
	std::vector<int> positions; 
	//index of the elements with an upgrade
	std::vector<int> upgrade;
	int lifes;
	int speedY;
};
	*/
	enemyData.type = 0;
	enemyData.totalEnemies = total;
	enemyData.positions = positions;
	enemyData.upgrade = upgrades;
	enemyData.lifes = 1;
	level->addProgressEnemyData({ progress,enemyData });
}

void Game::addLevelEnemy1(int progress, std::vector<int> upgrades, int speedY) {
	EnemyData enemyData;
	enemyData.type = 1;
	enemyData.totalEnemies = 3;
	enemyData.upgrade = upgrades;
	enemyData.lifes = 1;
	enemyData.speedY = speedY;
	level->addProgressEnemyData({ progress,enemyData });
}

void Game::addLevelEnemy2(int progress, std::vector<int> upgrades) {
	EnemyData enemyData;
	enemyData.type = 2;
	enemyData.totalEnemies = 2;
	enemyData.upgrade = upgrades;
	enemyData.lifes = 1;
	level->addProgressEnemyData({ progress,enemyData });
}

void Game::loadTextures(SDL_Renderer* renderer) {
	SDL_Color white = { 255,255,255 };
	loadTransparentImage(renderer, "images/sprites.png", &shipTexture, 0, 0, 0);
	loadImage(renderer, "images/menu0.png", &imageMenuTexture);
	loadImage(renderer, "images/Gradius-Stage1-Volcano map.png", &levelOneTexture);
	loadImage(renderer, "images/NES - Gradius - HUD.png", &menuTexture);
	loadTransparentImage(renderer, "images/enemies.png", &enemyTexture, 0, 0, 0);
	loadTransparentImage(renderer, "images/enemies2.png", &enemyTexture2, 0, 0, 0);
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(menu->getHeight() * 0.04), "H I", &menuTextTexture[1], renderer);
	menu->initPauseTextures(renderer);
}

void Game::closeTextures() {
	SDL_DestroyTexture(shipTexture);
	SDL_DestroyTexture(imageMenuTexture);
	SDL_DestroyTexture(levelOneTexture);
	for (int i = 0; i < 2; i++) {
		SDL_DestroyTexture(menuTextTexture[i]);
	}
	SDL_DestroyTexture(menuTexture);
	SDL_DestroyTexture(enemyTexture);
	SDL_DestroyTexture(enemyTexture2);
}

bool Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		SDL_Quit();
		return false;
	}

	if (!initRenderer(&window, &renderer, menu->getWidth(), menu->getHeight()))
		return false;

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init() < 0) {
		SDL_Log("Unable to initialize SDL_ttf: %s", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_Log("Audio is not working");
	}

	SDL_SetWindowTitle(window, "Gradius");
	ticksCount = SDL_GetTicks();
	SDL_Log("start process is completed");
	
	loadTextures(renderer);

	return true;
}


void Game::loop() {
	while (!menu->getGameOver()) {
		int fps = 60;
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + (1000 / fps)));

		float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}
		ticksCount = SDL_GetTicks();

		const Uint8* keys = SDL_GetKeyboardState(NULL);


		switch (menu->getIndex()) {
		case 0:
			keyCP(keys);
			menu->updateCP(deltaTime);
			menu->showCP(renderer);
			break;
		case 1:
			menu->keyIG(deltaTime, keys);
			for (auto ship : ships) {
				if(!ship->getDead())
					ship->detectKey(deltaTime, keys);
			}
			update(deltaTime);
			show(renderer);
			for (auto ship : ships) {
				ship->setDirection(0);
			}
			break;
		case 2:
			menu->showPause(renderer);
			menu->keyPause(keys);
			break;
		}
	}
}

void Game::keyCP(const Uint8* keys) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		int typeEvent = event.type;
		if (typeEvent == SDL_QUIT) {
			menu->setGameOver(true);
		}
		else if (typeEvent == SDL_KEYDOWN) {
			if (keys[SDL_SCANCODE_W] || keys[SDL_SCANCODE_UP]) {
				menu->setPlayers(1);
			}
			if (keys[SDL_SCANCODE_S] || keys[SDL_SCANCODE_DOWN]) {
				menu->setPlayers(2);
			}
			if (keys[SDL_SCANCODE_SPACE]) {
				if (menu->getPhase() == 0) {
					menu->setPhase(1);
					menu->setX(0);
				}
				else {
					menu->setIndex(1);
					Ship ship;
					ship.setX((float)(menu->getWidth() / 3.6));
					ship.setY((float)(menu->getHeight() / 2.4));
					ship.setW(menu->getWidth() / 9);
					ship.setH(menu->getHeight() / 12);
					ship.setLifes(3);
					ship.setSpeedX((float)background->getW() / 6);
					ship.setSpeedY((float)background->getH() / 4);
					ship.setfirstX(0);
					ship.setfirstY(0);
					ship.setEndX(background->getW());
					ship.setEndY(background->getH());
					ship.getShield()->setW(ship.getW() / 3);
					ship.getShield()->setH(ship.getH());
					ship.setKeyUp(SDL_SCANCODE_W);
					ship.setKeyDown(SDL_SCANCODE_S);
					ship.setKeyRight(SDL_SCANCODE_D);
					ship.setKeyLeft(SDL_SCANCODE_A);
					ship.setKeyShoot(SDL_SCANCODE_F);
					ship.setKeySelectUpgrade(SDL_SCANCODE_G);
					ship.setMenuRect(6, (int)(menu->getWidth() * 0.156), (int)(menu->getHeight() * 0.93), (int)(menu->getWidth() * 0.026), (int)(menu->getHeight() * 0.04));
					ship.setMenuRect(7, (int)(menu->getWidth() * 0.343), (int)(menu->getHeight() * 0.93), (int)(menu->getWidth() * 0.213), (int)(menu->getHeight() * 0.04));
					ship.initMenuTexture((int)(menu->getHeight() * 0.04), renderer);
					ship.setIncrementSpeedX((float)background->getW() / 6);
					ship.setIncrementSpeedY((float)background->getH() / 4);
					ship.setLevel(level);
					ship.setTimeInvincible(2);
					for (int i = 0; i < 6; i++) {
						ship.setSpriteRect(i, 6 + 32 * i, 82, 31, 6);
					}
					if (menu->getPlayers() == 1) {
						for (int i = 0; i < 6; i++) {
							ship.setMenuRect(i, (int)((i + 1) * 0.125 * menu->getWidth()), (int)(0.9 * menu->getHeight()), (int)(0.121 * menu->getWidth()), (int)(0.031 * menu->getHeight()));
						}
						addShip(new Ship(ship));
						generateTextTexture({ 255,255,255 }, "ttf/Oswald-BoldItalic.ttf", (int)(menu->getHeight() * 0.04), "1 P", &menuTextTexture[0], renderer);
					}
					else {
						int heightP = (int)(0.023 * menu->getHeight());
						for (int i = 0; i < 6; i++) {
							ship.setMenuRect(i, (int)((i + 1) * 0.125 * menu->getWidth()), (int)(0.877 * menu->getHeight()), (int)(0.121 * menu->getWidth()), heightP);
						}
						addShip(new Ship(ship));
						Ship ship2;
						ship2.setX((float)(menu->getWidth() / 3.6));
						ship2.setY((float)(menu->getHeight() / 2.0));
						ship2.setW(menu->getWidth() / 9);
						ship2.setH(menu->getHeight() / 12);
						ship2.setLifes(3);
						ship2.setSpeedX((float)background->getW() / 6);
						ship2.setSpeedY((float)background->getH() / 4);
						ship2.setfirstX(0);
						ship2.setfirstY(0);
						ship2.setEndX(background->getW());
						ship2.setEndY(background->getH());
						ship2.getShield()->setW(ship2.getW() / 3);
						ship2.getShield()->setH(ship2.getH());
						ship2.setKeyUp(SDL_SCANCODE_UP);
						ship2.setKeyDown(SDL_SCANCODE_DOWN);
						ship2.setKeyRight(SDL_SCANCODE_RIGHT);
						ship2.setKeyLeft(SDL_SCANCODE_LEFT);
						ship2.setKeyShoot(SDL_SCANCODE_K);
						ship2.setKeySelectUpgrade(SDL_SCANCODE_L);
						ship2.setMenuRect(6, (int)(menu->getWidth() * 0.208), (int)(menu->getHeight() * 0.93), (int)(menu->getWidth() * 0.026), (int)(menu->getHeight() * 0.04));
						ship2.setMenuRect(7, (int)(menu->getWidth() * 0.718), (int)(menu->getHeight() * 0.93), (int)(menu->getWidth() * 0.213), (int)(menu->getHeight() * 0.04));
						ship2.initMenuTexture((int)(menu->getHeight() * 0.04), renderer);
						ship2.setIncrementSpeedX((float)background->getW() / 6);
						ship2.setIncrementSpeedY((float)background->getH() / 4);
						for (int i = 0; i < 6; i++) {
							ship2.setMenuRect(i, (int)((i + 1) * 0.125 * menu->getWidth()), (int)(0.915 * menu->getHeight() - heightP / 2), (int)(0.121 * menu->getWidth()), heightP);
							ship2.setSpriteRect(i, 6 + 32 * i, 82, 31, 6);
						}
						ship2.setLevel(level);
						ship2.setTimeInvincible(2);
						addShip(new Ship(ship2));
						generateTextTexture({ 255,255,255 }, "ttf/Oswald-BoldItalic.ttf", (int)(menu->getHeight() * 0.04), "2 P", &menuTextTexture[0], renderer);
					}
				}
			}
			if (keys[SDL_SCANCODE_ESCAPE]) {
				menu->setGameOver(true);
			}
		}
	}
}

void Game::update(float deltaTime) {
	for (auto ship : ships) {
		if (!ship->getDead()) {
			ship->update(deltaTime);
			int actualShipCoordX = (int)(level->getProgress() + (ship->getX() + (float)ship->getW()) / (background->getW() / 14));
			if (!ship->getInvincible() && actualShipCoordX >= 64 && actualShipCoordX <= 207) {
				int actualShipCoordY = (int)((ship->getY() + ship->getH() / 2) / (background->getH() / 13) + 1);
				if (actualShipCoordY <= 1 || actualShipCoordY >= 13) {
					ship->setLifes(ship->getLifes() - 1);
					ship->changeLifeTexture((int)(background->getH() * 0.04), renderer);
					if (ship->getLifes() < 1) {
						ship->setDead(true);
						deadPlayers++;
						if (deadPlayers >= menu->getPlayers())
							restart();
						else {
							ship->clearBullets();
							ship->clearMissiles();
							ship->clearOptions();
							ship->setYellowUpgrades();
						}
						return;
					}
					else {
						ship->setInvincible(true);
					}
				}
			}
		}
	}
	
	for (auto enemy : enemies) {
		enemy->update(deltaTime);
	}
	for (auto enemy : enemies0) {
		enemy->update(deltaTime);
	}
	for (auto enemy : enemies6) {
		enemy->update(deltaTime);
	}
	for (auto upgrade : upgrades) {
		upgrade->update(deltaTime);
	}
	for (auto bullet : enemyBullets) {
		bullet->update(deltaTime);
	}

	switch (level->getActualPhase()) {
	case 0:
		updateLevelRoundsByProgress(deltaTime);
		break;
	case 1:
		moveBackgroundToMountains(deltaTime);
		break;
	case 2:
		updateLevelRoundsByTime(deltaTime);
		break;
	case 3:
		moveBackgroundToBoss(deltaTime);
		break;
	case 4:
		checkBossDefeated();
		break;
	}

	checkCollisionEnemyToShip();
	checkCollisionShipBulletsToEnemy();
	checkCollisionShieldToEnemy();
	checkCollisionUpgradeToShip();
	checkCollisionEnemyBulletsToShip();
	checkCollisionEnemyBulletsToShield();
	checkShipMapCollision();
	checkBulletMapCollision();
	checkEnemyBulletMapCollision();

	for (auto enemy : enemies) {
		if (enemy->getDead()) {
			if (enemy->getUpgrade())
				generateUpgrade(enemy->getX() + enemy->getW() / 2, enemy->getY() + enemy->getH() / 2);
			deleteEnemy(enemy);
		}
	}
	for (auto enemy : enemies0) {
		if (enemy->getDead()) {
			deleteEnemy0(enemy);
		}
	}
	for (auto enemy : enemies6) {
		if (enemy->getDead()) {
			deleteEnemy6(enemy);
			if (enemy->getUpgrade())
				generateUpgrade(enemy->getX() + enemy->getW() / 2, enemy->getY() + enemy->getH() / 2);
		}
	}
	for (auto upgrade : upgrades) {
		if (upgrade->getDead()) {
			deleteUpgrade(upgrade);
		}
	}
	for (auto bullet : enemyBullets) {
		if (bullet->getDead()) {
			deleteEnemyBullet(bullet);
		}
	}
}

void Game::show(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	background->show(renderer);
	for (auto ship : ships) {
		if(!ship->getDead())
			ship->show(renderer);
	}
	for (auto bullet : enemyBullets) {
		bullet->show(renderer);
	}
	for (auto enemy : enemies) {
		enemy->show(renderer);
	}
	for (auto enemy : enemies0) {
		enemy->show(renderer);
	}
	for (auto enemy : enemies6) {
		enemy->show(renderer);
	}
	for (auto upgrade : upgrades) {
		upgrade->show(renderer);
	}
	menu->showIG(renderer, ships);
	SDL_RenderPresent(renderer);
}

void Game::moveBackgroundToMountains(float deltaTime) {
	background->update(deltaTime);
	level->update(background->getSpriteX() - background->getFirstSpriteX(), 16);
	if (level->getProgress() >= 193) {
		level->setActualPhase(level->getActualPhase() + 1);
	}
}

void Game::updateLevelRoundsByTime(float deltaTime) {
	level->setTimer(level->getTimer() + deltaTime);
	if (level->getTimer() >= level->getTimeRounds().at(level->getActualRound())) {
		level->setTimer(0);

		generateEnemy(level->getTimeEnemyData().at(level->getActualRound()));
		if (level->getActualRound() < level->getTotalPhaseRounds().at(level->getActualPhase()) - 1) {
			level->setActualRound(level->getActualRound() + 1);
		}
		else {
			level->setActualRound(0);
			level->setActualPhase(level->getActualPhase() + 1);
		}
	}
}

void Game::moveBackgroundToBoss(float deltaTime) {
	background->update(deltaTime);
	level->update(background->getSpriteX() - background->getFirstSpriteX(), 16);
	if (level->getProgress() < 1) {
		level->setActualPhase(level->getActualPhase() + 1);
		generateEnemy9();
	}
}

void Game::checkBossDefeated() {
	if (enemies.size() < 1) {
		level->setActualPhase(0);
	}
}

void Game::updateLevelRoundsByProgress(float deltaTime) {
	background->update(deltaTime);
	level->update(background->getSpriteX() - background->getFirstSpriteX(), 16);
	if ((int)level->getProgress() == level->getPhaseProgressEnemies().at(level->getActualProgressEnemy()).progress) {

		generateEnemy(level->getPhaseProgressEnemies().at(level->getActualProgressEnemy()).enemyData);

		if (level->getActualProgressEnemy() < level->getTotalPhaseRounds().at(level->getActualPhase()) - 1) {
			level->setActualProgressEnemy(level->getActualProgressEnemy() + 1);
		}
		else {
			level->setActualProgressEnemy(0);
			level->setActualPhase(level->getActualPhase() + 1);
		}
	}
}

void Game::generateUpgrade(float x, float y) {
	Upgrade* upgrade = new Upgrade();
	upgrade->setW(background->getW() / 18);
	upgrade->setH(background->getH() / 12);
	upgrade->setX(x - upgrade->getW() / 2);
	upgrade->setY(y - upgrade->getH() / 2);
	upgrade->setSpeed((float)(-background->getW() / 7));
	upgrade->setfirstX(0);
	upgrade->setEndX(background->getW());
	addUpgrade(upgrade);
}

void Game::generateEnemy(EnemyData enemyData) {
	switch (enemyData.type) {
	case 0:
		generateEnemy0(enemyData);
		break;
	case 1:
		generateEnemy1(enemyData);
		break;
	case 2:
		generateEnemy2(enemyData);
		break;
	case 3:
		generateEnemy3(enemyData);
		break;
	case 4:
		generateEnemy4(enemyData);
		break;
	case 5:
		generateEnemy5(enemyData);
		break;
	case 6:
		generateEnemy6(enemyData);
		break;
	case 8:
		generateEnemy8(enemyData);
		break;
	}
}

void Game::generateEnemy0(EnemyData enemyData) {
	for (int i = 0; i < enemyData.totalEnemies; i++) {
		Enemy0* enemy = new Enemy0();
		enemy->setW(background->getW() / 18);
		enemy->setH(background->getH() / 12);
		enemy->setX((float)(background->getW() + (enemy->getW() * 1.5) * i));
		if (enemyData.positions.at(i) == 0)
			enemy->setY((float)(background->getH() * 0.15));
		else
			enemy->setY((float)(background->getH() * 0.85 - enemy->getH()));
		enemy->setfirstX(0);
		enemy->setfirstY(0);
		enemy->setEndX(background->getW());
		enemy->setEndY(background->getH());
		enemy->setSpeedX((float)(-background->getW() * 0.4166));
		enemy->setScore(100);
		enemy->setLifes(enemyData.lifes);
		enemy->setLine(actualLine);
		addEnemy0(enemy);
	}
	lineEnemies0[actualLine] = enemyData.totalEnemies;
	if (actualLine < 4)
		actualLine++;
	else
		actualLine = 0;
}

void Game::generateEnemy1(EnemyData enemyData) {
	for (int i = 0; i < enemyData.totalEnemies; i++) {
		Enemy1* enemy = new Enemy1();
		enemy->setW(background->getW() / 18);
		enemy->setH(background->getH() / 12);
		enemy->setX((float)(background->getW() + enemy->getW()));
		float enemyH = (float)(i * background->getH() * 0.2);
		enemy->setY((float)(background->getH() * 0.3  + enemyH - enemy->getH() / 2));
		enemy->setfirstX(0);
		enemy->setfirstY(0);
		enemy->setEndX(background->getW());
		enemy->setEndY(background->getH());
		enemy->setScore(100);
		enemy->setLifes(enemyData.lifes);
		enemy->setSpeedX((float)(-background->getW() / 6));
		if(enemyData.speedY > 0)
			enemy->setSpeedY((float)(background->getH() / 4));
		else
			enemy->setSpeedY((float)(-background->getH() / 4));
		enemy->setLimitUpY((int)(enemy->getY() - background->getH() * 0.15));
		enemy->setLimitDownY((int)(enemy->getY() + background->getH() * 0.15));
		bool upgrade = false;
		for (int ind : enemyData.upgrade) {
			if (ind == i) {
				//the enemy has an upgrade
				upgrade = true;
				break;
			}
		}
		enemy->setUpgrade(upgrade);
		enemy->setSprites();
		enemy->setActualSprite();
		addEnemy(enemy);
	}
}

void Game::generateEnemy2(EnemyData enemyData) {
	for (int i = 0; i < enemyData.totalEnemies; i++) {
		Enemy2* enemy = new Enemy2();
		enemy->setW(background->getW() / 18);
		enemy->setH(background->getH() / 12);
		enemy->setX((float)(background->getW() + enemy->getW()));
		float enemyH = (float)(i * background->getH() * 0.3);
		enemy->setY((float)(background->getH() * 0.3 + enemyH - enemy->getH() / 2));
		enemy->setfirstX(0);
		enemy->setfirstY(0);
		enemy->setEndX(background->getW());
		enemy->setEndY(background->getH());
		enemy->setScore(100);
		enemy->setLifes(enemyData.lifes);
		enemy->setSpeedX((float)(-background->getW() / 4));
		enemy->setCenter((int)(background->getH() * 0.3 + enemyH));
		enemy->setLongitude((float)(background->getH() / 10));
		bool upgrade = false;
		for (int ind : enemyData.upgrade) {
			if (ind == i) {
				//the enemy has an upgrade
				upgrade = true;
				break;
			}
		}
		enemy->setUpgrade(upgrade);
		enemy->setSprites();
		addEnemy(enemy);
	}
}

void Game::generateEnemy3(EnemyData enemyData) {
	Enemy3* enemy = new Enemy3();
	enemy->setW(background->getW() / 18);
	enemy->setH(background->getH() / 12);
	enemy->setX((float)(background->getW() + enemy->getW()));
	if (enemyData.positions.at(0) == 0)
		enemy->setY((float)background->getH() / 15);
	else
		enemy->setY((float)(14 * background->getH() / 15 - enemy->getH()));
	enemy->setfirstX(0);
	enemy->setfirstY(0);
	enemy->setEndX(background->getW());
	enemy->setEndY(background->getH());
	enemy->setScore(100);
	enemy->setLifes(enemyData.lifes);
	enemy->setSpeedX((float)(-background->getW() / 7));
	enemy->setShipTarget(ships.at(actualShipTarget));
	if (menu->getPlayers() > 1) {
		updateActualShipTarget();
	}
	enemy->setBullets(&enemyBullets);
	if (enemyData.positions.at(0) == 0)
		enemy->setUp(true);
	addEnemy(enemy);
}

void Game::generateEnemy4(EnemyData enemyData) {
	Enemy4* enemy = new Enemy4();
	enemy->setW(background->getW() / 18);
	enemy->setH(background->getH() / 12);
	enemy->setX((float)(background->getW() + enemy->getW()));
	if(enemyData.positions.at(0) == 0){ 
		enemy->setY((float)(background->getH() / 10)); 
		enemy->setCenter((int)enemy->getY());
	}
	else {
		enemy->setY((float)(9 * background->getH() / 10 - enemy->getH()));
		enemy->setCenter((int)enemy->getY());
	}
	enemy->setfirstX(0);
	enemy->setfirstY(0);
	enemy->setEndX(background->getW());
	enemy->setEndY(background->getH());
	enemy->setScore(100);
	enemy->setLifes(enemyData.lifes);
	enemy->setSpeedX((float)(-background->getW() / 2));
	enemy->setLongitude((float)(background->getH() / 5));
	bool upgrade = false;
	for (int ind : enemyData.upgrade) {
		if (ind == 0) {
			//the enemy has an upgrade
			upgrade = true;
			break;
		}
	}
	enemy->setUpgrade(upgrade);
	enemy->setSprites();
	addEnemy(enemy);
}

void Game::generateEnemy5(EnemyData enemyData) {

	for (int i = 0; i < enemyData.totalEnemies; i++) {
		Enemy5* enemy = new Enemy5();
		enemy->setW(background->getW() / 18);
		enemy->setH(background->getH() / 12);
		enemy->setX((float)(-enemy->getW()));
		if (enemyData.positions.at(i) == 0) {
			enemy->setY((float)(background->getH() / 13));
			enemy->setUp(true);
		}
		else {
			enemy->setY((float)(12 * background->getH() / 13 - enemy->getH()));
			enemy->setUp(false);
		}
		enemy->setfirstX(0);
		enemy->setfirstY(0);
		enemy->setEndX(background->getW());
		enemy->setEndY(background->getH());
		enemy->setScore(100);
		enemy->setLifes(enemyData.lifes);
		bool upgrade = false;
		for (int ind : enemyData.upgrade) {
			if (ind == i) {
				//the enemy has an upgrade
				upgrade = true;
				break;
			}
		}
		enemy->setUpgrade(upgrade);
		enemy->setLevel(level);
		enemy->setShipTarget(ships.at(actualShipTarget));
		if (menu->getPlayers() > 1) {
			updateActualShipTarget();
		}
		enemy->setBullets(&enemyBullets);
		enemy->setSpeedX((float)(background->getW() / 4));
		enemy->setSpeedY((float)(background->getH() / 2));
		enemy->setPausedSpeedX((float)(-background->getW() / 7));
		enemy->setTimeShoot(0.5);
		enemy->setSprites();
		enemy->setMountainIndex(mountain->getMountainIndexOnRate((int)level->getProgress(), 14));
		if (enemy->getMountainIndex() > -1) {
			if (enemy->getMountainIndex() == 1) {
				enemy->setSizeCoordX((float)(background->getW() / 14));
				enemy->setSizeCoordY((float)(background->getH() / 13));

				enemy->setTopY(12);
				enemy->setLastTopX(113);
				enemy->setBottomY(12);
				enemy->setCoordFirstMountainX(108);
				enemy->setCoordReverseFirstMountainX(113);
				enemy->setReverseLastTopX(108);
			}
			else {
				enemy->setSizeCoordX(((float)background->getW() / 14.0f));
				enemy->setSizeCoordY(((float)background->getH() / 13.0f));

				enemy->setTopY(13 - mountain->getTotalY(enemy->getMountainIndex()));
				enemy->setLastTopX(mountain->getLastRightMountainCoordinate(enemy->getMountainIndex()));
				enemy->setBottomY(12);
				enemy->setCoordFirstMountainX(mountain->getCoordinates(enemy->getMountainIndex()).at(0).x);
				int ind = mountain->getTotalX(enemy->getMountainIndex()) - 1;
				enemy->setCoordReverseFirstMountainX(mountain->getCoordinates(enemy->getMountainIndex()).at(ind).x);
				enemy->setReverseLastTopX(mountain->getLastLeftMountainCoordinate(enemy->getMountainIndex()));
			}
		}
		addEnemy(enemy);
	}
}

void Game::generateEnemy6(EnemyData enemyData) {
	Enemy6* enemy = new Enemy6();
	enemy->setW(background->getW() / 9);
	enemy->setH(background->getH() / 8);
	enemy->setX((float)(background->getW() + enemy->getW()));
	if(enemyData.positions.at(0) == 0){
		enemy->setY((float)(background->getH() / 13));
		enemy->setUp(true);
	}
	else{
		enemy->setY((float)(12 * background->getH() / 13 - enemy->getH()));
		enemy->setUp(false);
	}
	enemy->setfirstX(0);
	enemy->setfirstY(0);
	enemy->setEndX(background->getW());
	enemy->setEndY(background->getH());
	enemy->setScore(100);
	enemy->setLifes(enemyData.lifes);
	enemy->setSpeedX((float)(-background->getW() / 7));
	enemy->setTimeShoot(1.0);
	enemy->setBlueSprite();
	enemy->setEnemies(&enemies);
	enemy->setShipTarget(ships.at(actualShipTarget));
	if (menu->getPlayers() > 1)
		updateActualShipTarget();
	enemy->setBullets(&enemyBullets);
	addEnemy6(enemy);
}

void Game::generateEnemy8(EnemyData enemyData) {
	//position 0 -> left, 1->right
	for (int i = 0; i < enemyData.totalEnemies; i++) {
		Enemy8* enemy = new Enemy8();
		enemy->setW(background->getW() / 36);
		enemy->setH(background->getH() / 36);
		enemy->setY((float)background->getH() / 1.40f - enemy->getH() / 2);
		if (enemyData.positions.at(i) == 0) {
			enemy->setX((float)background->getW() / 4.87f - enemy->getW() / 2);
			enemy->setMountainX((float)background->getW() / 4.87f - enemy->getW() / 2);
		}
		else {
			enemy->setX((float)background->getW() / 1.29f - enemy->getW() / 2);
			enemy->setMountainX((float)background->getW() / 1.29f - enemy->getW() / 2);
		}
		enemy->setfirstX(0);
		enemy->setfirstY(0);
		enemy->setEndX(background->getW());
		enemy->setEndY(background->getH());
		enemy->setScore(100);
		enemy->setLifes(enemyData.lifes);
		if (rand() % 2 == 0)
			enemy->setSpeedX((float)background->getW() / 4.0f);
		else
			enemy->setSpeedX((float)-background->getW() / 4.0f);
		enemy->setCenter((int)(background->getH() / 1.40f - enemy->getH() / 2));
		enemy->setLongitude((float)((rand() % 10 + 1) * 0.1f) * enemy->getCenter());
		enemy->setSpeedY(enemy->getLongitude() * 10);

		addEnemy(enemy);
	}
	
}

void Game::generateEnemy9() {
	Enemy9* enemy = new Enemy9();
	enemy->setW(background->getW() / 6);
	enemy->setH(background->getH() / 4);
	enemy->setX((float)background->getW());
	enemy->setY((float)(background->getH() / 2 - enemy->getH() / 2));
	enemy->setfirstX(0);
	enemy->setfirstY(0);
	enemy->setEndX(background->getW());
	enemy->setEndY(background->getH());
	enemy->setScore(1000);
	enemy->setLifes(100);
	enemy->setSpeedX(-(float)background->getW() / 3.0f);
	enemy->setSpeedY((float)(background->getH() / 2.666));
	enemy->setTimeShoot(1.0);
	enemy->setShipTarget(ships.at(actualShipTarget));
	enemy->setMovement(menu->getPlayers() - 1);
	if (menu->getPlayers() > 1)
		updateActualShipTarget();
	enemy->setBullets(&enemyBullets);

	addEnemy(enemy);
}

void Game::updateActualShipTarget() {
	if (deadPlayers > 0) {
		int i = 0;
		for (auto ship : ships) {
			if (!ship->getDead())
				break;
			i++;
		}
		actualShipTarget = i;
	}
	else {
		if (actualShipTarget == 0) {
			actualShipTarget = 1;
		}
		else {
			actualShipTarget = 0;
		}
	}
	
}

void Game::checkCollisionEnemyToShip() {
	for (auto ship : ships) {
		if (!ship->getDead()) {
			SDL_Rect shipRect = { (int)ship->getX(),(int)ship->getY(),ship->getW(),ship->getH() };
			for (auto enemy : enemies) {
				SDL_Rect enemyRect = { (int)enemy->getX(), (int)enemy->getY(), enemy->getW(), enemy->getH() };
				if (!ship->getInvincible() && SDL_HasIntersection(&enemyRect, &shipRect) && !enemy->getDead()) {
					ship->setLifes(ship->getLifes() - 1);
					ship->changeLifeTexture((int)(background->getH() * 0.04), renderer);
					if (ship->getLifes() < 1) {
						ship->setDead(true);
						deadPlayers++;
						if (deadPlayers >= menu->getPlayers())
							restart();
						else {
							ship->clearBullets();
							ship->clearMissiles();
							ship->clearOptions();
							ship->setYellowUpgrades();
						}
						return;
					}
					else {
						ship->setInvincible(true);
					}
					return;
				}
			}
			for (auto enemy : enemies0) {
				SDL_Rect enemyRect = { (int)enemy->getX(), (int)enemy->getY(), enemy->getW(), enemy->getH() };
				if (!ship->getInvincible() && SDL_HasIntersection(&enemyRect, &shipRect) && !enemy->getDead()) {
					ship->setLifes(ship->getLifes() - 1);
					ship->changeLifeTexture((int)(background->getH() * 0.04), renderer);
					if (ship->getLifes() < 1) {
						ship->setDead(true);
						deadPlayers++;
						if (deadPlayers >= menu->getPlayers())
							restart();
						else {
							ship->clearBullets();
							ship->clearMissiles();
							ship->clearOptions();
							ship->setYellowUpgrades();
						}
						return;
					}
					else {
						ship->setInvincible(true);
					}
				}
			}
			for (auto enemy : enemies6) {
				SDL_Rect enemyRect = { (int)enemy->getX(), (int)enemy->getY(), enemy->getW(), enemy->getH() };
				if (!ship->getInvincible() && SDL_HasIntersection(&enemyRect, &shipRect) && !enemy->getDead()) {
					ship->setLifes(ship->getLifes() - 1);
					ship->changeLifeTexture((int)(background->getH() * 0.04), renderer);
					if (ship->getLifes() < 1) {
						ship->setDead(true);
						deadPlayers++;
						if (deadPlayers >= menu->getPlayers())
							restart();
						else {
							ship->clearBullets();
							ship->clearMissiles();
							ship->clearOptions();
							ship->setYellowUpgrades();
						}
						return;
					}
					else {
						ship->setInvincible(true);
					}
				}
			}
		}
	}
}

void Game::checkCollisionShipBulletsToEnemy() {
	for (auto ship : ships) {
		for (auto bullet : ship->getBullets()) {
			SDL_Rect bulletRect = { (int)bullet->getX(),(int)bullet->getY(),bullet->getW(),bullet->getH() };
			for (auto enemy : enemies) {
				SDL_Rect enemyRect = { (int)enemy->getX(),(int)enemy->getY(),enemy->getW(),enemy->getH() };
				if (SDL_HasIntersection(&enemyRect, &bulletRect) && !enemy->getDead()) {
					if (bullet->getDamage() == 1) {
						bullet->setDead(true);
					}
					enemy->setLifes(enemy->getLifes() - 1);
					if (enemy->getLifes() < 1) {
						ship->setScore(ship->getScore() + enemy->getScore());
						ship->changeScoreTexture((int)(menu->getHeight() * 0.04), renderer);
						enemy->setDead(true);
					}
					else {
						bullet->setDead(true);
					}
				}
			}
			for (auto enemy : enemies0) {
				SDL_Rect enemyRect = { (int)enemy->getX(),(int)enemy->getY(),enemy->getW(),enemy->getH() };
				if (SDL_HasIntersection(&enemyRect, &bulletRect) && !enemy->getDead()) {
					if (bullet->getDamage() == 1) {
						bullet->setDead(true);
					}
					enemy->setLifes(enemy->getLifes() - 1);
					if (enemy->getLifes() < 1) {
						ship->setScore(ship->getScore() + enemy->getScore());
						ship->changeScoreTexture((int)(menu->getHeight() * 0.04), renderer);
						enemy->setDead(true);
						lineEnemies0[enemy->getLine()]--;
						if (lineEnemies0[enemy->getLine()] <= 0) {
							float x;
							float y;
							x = (float)(enemyRect.x + enemyRect.w / 2);
							y = (float)(enemyRect.y + enemyRect.h / 2);
							generateUpgrade(x, y);
						}
					}
					else {
						bullet->setDead(true);
					}
				}
			}
			for (auto enemy : enemies6) {
				SDL_Rect enemyRect = { (int)enemy->getX(),(int)enemy->getY(),enemy->getW(),enemy->getH() };
				if (SDL_HasIntersection(&enemyRect, &bulletRect) && !enemy->getDead()) {
					bullet->setDead(true);
					enemy->setLifes(enemy->getLifes() - 1);
					if (enemy->getLifes() < 1) {
						ship->setScore(ship->getScore() + enemy->getScore());
						ship->changeScoreTexture((int)(menu->getHeight() * 0.04), renderer);
						enemy->setDead(true);
					}
					else if (enemy->getLifes() == 1) {
						enemy->setRedSprite();
					}
				}
			}
		}
		for (auto missile : ship->getMissiles()) {
			SDL_Rect missileRect = { (int)missile->getX(), (int)missile->getY(), missile->getW(), missile->getH() };
			for (auto enemy : enemies) {
				SDL_Rect enemyRect = { (int)enemy->getX(),(int)enemy->getY(),enemy->getW(),enemy->getH() };
				if (SDL_HasIntersection(&enemyRect, &missileRect) && !enemy->getDead()) {
					missile->setDead(true);
					enemy->setLifes(enemy->getLifes() - 1);
					if (enemy->getLifes() < 1) {
						ship->setScore(ship->getScore() + enemy->getScore());
						ship->changeScoreTexture((int)(menu->getHeight() * 0.04), renderer);
						enemy->setDead(true);
					}
				}
			}
			for (auto enemy : enemies0) {
				SDL_Rect enemyRect = { (int)enemy->getX(),(int)enemy->getY(),enemy->getW(),enemy->getH() };
				if (SDL_HasIntersection(&enemyRect, &missileRect) && !enemy->getDead()) {
					missile->setDead(true);
					enemy->setLifes(enemy->getLifes() - 1);
					if (enemy->getLifes() < 1) {
						ship->setScore(ship->getScore() + enemy->getScore());
						ship->changeScoreTexture((int)(menu->getHeight() * 0.04), renderer);
						enemy->setDead(true);
						lineEnemies0[enemy->getLine()]--;
						if (lineEnemies0[enemy->getLine()] <= 0) {
							float x;
							float y;
							x = (float)(enemyRect.x + enemyRect.w / 2);
							y = (float)(enemyRect.y + enemyRect.h / 2);
							generateUpgrade(x, y);
						}
					}
				}
			}
			for (auto enemy : enemies6) {
				SDL_Rect enemyRect = { (int)enemy->getX(),(int)enemy->getY(),enemy->getW(),enemy->getH() };
				if (SDL_HasIntersection(&enemyRect, &missileRect) && !enemy->getDead()) {
					missile->setDead(true);
					enemy->setLifes(enemy->getLifes() - 1);
					if (enemy->getLifes() < 1) {
						ship->setScore(ship->getScore() + enemy->getScore());
						ship->changeScoreTexture((int)(menu->getHeight() * 0.04), renderer);
						enemy->setDead(true);
					}
					else if (enemy->getLifes() == 1) {
						enemy->setRedSprite();
					}
				}
			}
		}
	}
}

void Game::checkCollisionShieldToEnemy() {
	for (auto ship : ships) {
		if (!ship->getDead() && ship->getShield()->getLifes() > 0) {
			SDL_Rect shieldRect = { (int)ship->getShield()->getX(), (int)ship->getShield()->getY(), ship->getShield()->getW(), ship->getShield()->getH() };
			for (auto enemy : enemies) {
				SDL_Rect enemyRect = { (int)enemy->getX(),(int)enemy->getY(),enemy->getW(),enemy->getH() };
				if (!enemy->getDead() && SDL_HasIntersection(&shieldRect, &enemyRect)) {
					ship->getShield()->setLifes(ship->getShield()->getLifes() - 1);
					enemy->setLifes(enemy->getLifes() - 1);
					if(enemy->getLifes() < 1)
						enemy->setDead(true);
					if (ship->getShield()->getLifes() == 3) {
						ship->getShield()->setRedSprites();
					}
					else if (ship->getShield()->getLifes() < 1) {
						ship->decrementShieldUpgrade();
						if(ship->getActualUpgrade() != 5)
							ship->setSpriteRect(5, 166, 82, 31, 6);
						else
							ship->setSpriteRect(5, 166, 91, 31, 6);
					}
				}
			}
			for (auto enemy : enemies0) {
				SDL_Rect enemyRect = { (int)enemy->getX(),(int)enemy->getY(),enemy->getW(),enemy->getH() };
				if (!enemy->getDead() &&  SDL_HasIntersection(&shieldRect, &enemyRect)) {
					ship->getShield()->setLifes(ship->getShield()->getLifes() - 1);
					enemy->setDead(true);
					lineEnemies0[enemy->getLine()]--;
					if (lineEnemies0[enemy->getLine()] <= 0) {
						float x;
						float y;
						x = (float)(enemyRect.x + enemyRect.w / 2);
						y = (float)(enemyRect.y + enemyRect.h / 2);
						generateUpgrade(x, y);
					}
					if (ship->getShield()->getLifes() == 3) {
						ship->getShield()->setRedSprites();
					}
					else if (ship->getShield()->getLifes() < 1) {
						ship->decrementShieldUpgrade();
						if (ship->getActualUpgrade() != 5)
							ship->setSpriteRect(5, 166, 82, 31, 6);
						else
							ship->setSpriteRect(5, 166, 91, 31, 6);
					}
				}
			}
			for (auto enemy : enemies6) {
				SDL_Rect enemyRect = { (int)enemy->getX(),(int)enemy->getY(),enemy->getW(),enemy->getH() };
				if (!enemy->getDead() && SDL_HasIntersection(&shieldRect, &enemyRect)) {
					ship->getShield()->setLifes(ship->getShield()->getLifes() - 1);
					enemy->setLifes(enemy->getLifes() - 1);
					if(enemy->getLifes() < 1)
						enemy->setDead(true);
					else if (enemy->getLifes() == 1){
						enemy->setRedSprite();
					}
					if (ship->getShield()->getLifes() == 3) {
						ship->getShield()->setRedSprites();
					}
					else if (ship->getShield()->getLifes() < 1) {
						ship->decrementShieldUpgrade();
						if (ship->getActualUpgrade() != 5)
							ship->setSpriteRect(5, 166, 82, 31, 6);
						else
							ship->setSpriteRect(5, 166, 91, 31, 6);
					}
				}
			}
		}
	}
}

void Game::checkCollisionUpgradeToShip() {
	for (auto upgrade : upgrades) {
		SDL_Rect upgradeRect = { (int)upgrade->getX(),(int)upgrade->getY(),upgrade->getW(),upgrade->getH() };
		for (auto ship : ships) {
			if (!ship->getDead()) {
				SDL_Rect shipRect = { (int)ship->getX(),(int)ship->getY(),ship->getW(),ship->getH() };
				if (SDL_HasIntersection(&upgradeRect, &shipRect)) {
					upgrade->setDead(true);
					ship->getUpgrade();
				}
			}
		}
	}
}

void Game::checkCollisionEnemyBulletsToShip() {
	for (auto bullet : enemyBullets) {
		SDL_Rect bulletRect = { (int)bullet->getX(),(int)bullet->getY(),bullet->getW(),bullet->getH() };
		for (auto ship : ships) {
			if (!ship->getDead() && !ship->getInvincible()) {
				SDL_Rect shipRect = { (int)ship->getX(),(int)ship->getY(),ship->getW(),ship->getH() };
				if (SDL_HasIntersection(&bulletRect, &shipRect)) {
					ship->setLifes(ship->getLifes() - 1);
					ship->changeLifeTexture((int)(background->getH() * 0.04), renderer);
					if (ship->getLifes() < 1) {
						ship->setDead(true);
						deadPlayers++;
						if (deadPlayers >= menu->getPlayers())
							restart();
						else {
							ship->clearBullets();
							ship->clearMissiles();
							ship->clearOptions();
							ship->setYellowUpgrades();
						}
						return;
					}
					else {
						ship->setInvincible(true);
						bullet->setDead(true);
					}
				}
			}
		}
	}
}

void Game::checkCollisionEnemyBulletsToShield() {
	for (auto ship : ships) {
		if (ship->getShield()->getLifes() > 0) {
			SDL_Rect shieldRect = { (int)ship->getShield()->getX(),(int)ship->getShield()->getY(),ship->getShield()->getW(),ship->getShield()->getH() };
			for (auto bullet : enemyBullets) {
				SDL_Rect bulletRect = { (int)bullet->getX(),(int)bullet->getY(),bullet->getW(),bullet->getH() };
				if (SDL_HasIntersection(&shieldRect, &bulletRect)) {
					bullet->setDead(true);
					ship->getShield()->setLifes(ship->getShield()->getLifes() - 1);
					if (ship->getShield()->getLifes() == 3) {
						ship->getShield()->setRedSprites();
					}
					else if (ship->getShield()->getLifes() < 1) {
						ship->decrementShieldUpgrade();
						if (ship->getActualUpgrade() != 5)
							ship->setSpriteRect(5, 166, 82, 31, 6);
						else
							ship->setSpriteRect(5, 166, 91, 31, 6);
					}
				}
			}
		}
	}
}

void Game::checkShipMapCollision() {
	for (auto ship : ships) {
		if (!ship->getDead() && !ship->getInvincible()) {
			int shipCoordinateX = (int)(level->getProgress() + (ship->getX() + (float)ship->getW() / 2.0f) / (background->getW() / 14));
			int shipCoordinateY = (int)((ship->getY() + ship->getH() / 2) / (background->getH() / 13));
			int collisionIndex = mountain->getCollisionIndexOnRate(shipCoordinateX, 5);
			if (collisionIndex > -1) {
				if (mountain->hasCenterCollision(shipCoordinateX, shipCoordinateY + 1, collisionIndex)) {
					ship->setLifes(ship->getLifes() - 1);
					ship->changeLifeTexture((int)(background->getH() * 0.04), renderer);
					if (ship->getLifes() < 1) {
						ship->setDead(true);
						deadPlayers++;
						if (deadPlayers >= menu->getPlayers())
							restart();
						else {
							ship->clearBullets();
							ship->clearMissiles();
							ship->clearOptions();
							ship->setYellowUpgrades();
						}
						return;
					}
					else {
						ship->setInvincible(true);
					}
				}
			}
		}
	}
}

void Game::checkBulletMapCollision() {
	for (auto ship : ships) {
		for (auto bullet : ship->getBullets()) {
			int bulletCoordinateX = (int)(level->getProgress() + (bullet->getX() + (float)bullet->getW() / 2.0f) / (background->getW() / 14));
			int bulletCoordinateY = (int)((bullet->getY() + bullet->getH() / 2) / (background->getH() / 13));
			int collisionIndex = mountain->getCollisionIndexOnRate(bulletCoordinateX, 5);
			if (collisionIndex > -1) {
				if (mountain->hasCenterCollision(bulletCoordinateX, bulletCoordinateY + 1, collisionIndex)) {
					bullet->setDead(true);
				}
			}
		}
	}
}

void Game::checkEnemyBulletMapCollision() {
	for (auto bullet : enemyBullets) {
		int bulletCoordinateX = (int)(level->getProgress() + (bullet->getX() + (float)bullet->getW() / 2.0f) / (background->getW() / 14));
		int bulletCoordinateY = (int)((bullet->getY() + bullet->getH() / 2) / (background->getH() / 13));
		int collisionIndex = mountain->getCollisionIndexOnRate(bulletCoordinateX, 5);
		if (collisionIndex > -1) {
			if (mountain->hasCenterCollision(bulletCoordinateX, bulletCoordinateY + 1, collisionIndex)) {
				bullet->setDead(true);
			}
		}
	}
}

void Game::close() {
	closeRenderer(window,renderer);
	closeTextures();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::addShip(class Ship* ship) {
	ships.push_back(ship);
}

void Game::deleteShip(class Ship* ship) {
	auto index = std::find(ships.begin(), ships.end(), ship);
	if (index != ships.end())
		ships.erase(index);
}

void Game::addEnemy(class Enemy* enemy) {
	enemies.push_back(enemy);
}

void Game::deleteEnemy(class Enemy* enemy) {
	auto index = std::find(enemies.begin(), enemies.end(), enemy);
	if (index != enemies.end())
		enemies.erase(index);
}

void Game::addEnemy0(class Enemy0* enemy) {
	enemies0.push_back(enemy);
}

void Game::deleteEnemy0(class Enemy0* enemy) {
	auto index = std::find(enemies0.begin(), enemies0.end(), enemy);
	if (index != enemies0.end())
		enemies0.erase(index);
}

void Game::addEnemy6(class Enemy6* enemy) {
	enemies6.push_back(enemy);
}

void Game::deleteEnemy6(class Enemy6* enemy) {
	auto index = std::find(enemies6.begin(), enemies6.end(), enemy);
	if (index != enemies6.end())
		enemies6.erase(index);
}

void Game::addUpgrade(class Upgrade* upgrade) {
	upgrades.push_back(upgrade);
}

void Game::deleteUpgrade(class Upgrade* upgrade) {
	auto index = std::find(upgrades.begin(), upgrades.end(), upgrade);
	if (index != upgrades.end())
		upgrades.erase(index);
}

void Game::deleteEnemyBullet(class Bullet* bullet) {
	auto index = std::find(enemyBullets.begin(), enemyBullets.end(), bullet);
	if (index != enemyBullets.end())
		enemyBullets.erase(index);
}

void Game::restart() {
	deadPlayers = 0;
	enemies.clear();
	enemies0.clear();
	enemies6.clear();
	enemyBullets.clear();
	actualLine = 0;
	upgrades.clear();
	actualShipTarget = 0;
	background->setSpriteX((float)background->getFirstSpriteX());
	level->setActualProgressEnemy(0);
	level->setActualPhase(0);
	level->setTimer(0);
	level->setActualRound(0);
	ships.at(0)->setX((float)menu->getWidth() / 3.6f);
	ships.at(0)->setY((float)menu->getHeight() / 2.4f);
	if (ships.size() > 1) {
		ships.at(1)->setX((float)menu->getWidth() / 3.6f);
		ships.at(1)->setY((float)menu->getHeight() / 2.0f);
	}
	for (auto ship : ships) {
		ship->setDirection(0);
		ship->setSpeedX((float)background->getW() / 6);
		ship->setSpeedY((float)background->getH() / 4);
		ship->setBulletTimer(0);
		ship->setLifes(3);
		ship->setScore(0);
		ship->setActualUpgrade(-1);
		ship->clearBullets();
		ship->clearMissiles();
		ship->clearOptions();
		ship->getShield()->setLifes(0);
		for (int i = 0; i < 6; i++) {
			ship->setSpriteRect(i, 6 + 32 * i, 82, 31, 6);
		}
		ship->initMenuTexture((int)(menu->getHeight() * 0.04),renderer);
		ship->initUpgrades();
		ship->setInvincible(false);
		ship->setTimerInvincible(0);
		ship->setDead(false);
	}
}