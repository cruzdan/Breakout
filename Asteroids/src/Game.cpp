// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Menu.h"
#include "Ship.h"
#include "Sprite.h"
#include "Bullet.h"
#include "Asteroid.h"
#include "Game.h"

const double PI = 3.14159265;

Game::Game()
	:window(nullptr),
	renderer(nullptr),
	gameOver(false),
	menu(nullptr),
	ship(nullptr),
	lifes(3),
	ticksCount(0),
	SCREEN_WIDTH(1080),
	SCREEN_HEIGHT(720),
	timerAsteroids(0)
{
}

bool Game::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Error", SDL_GetError(), NULL);
		std::cout << "SDL did not initialize " << std::endl;
		SDL_Quit();
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Image",
			"The image PNG is not working", NULL);
		return false;
	}

	if (TTF_Init() < 0) {
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Ttf",
			"The ttf is not working", NULL);
		return false;
	}
	if (SDL_CreateWindowAndRenderer(SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_RESIZABLE,
		&window, &renderer) < 0) {
		std::cout << "window or renderer are not initialized " << std::endl;
		return false;
	}
	SDL_SetWindowTitle(window, "Asteroids");

	srand((unsigned int)time(NULL));
	loadImage(renderer);
	menu = new Menu(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
	ship = new Ship();
	ship->setMaxSpeed((float)SCREEN_WIDTH * 60.0f / 288);
	ship->setChangeVel((float)SCREEN_WIDTH / 120);
	int shipW = SCREEN_WIDTH / 50;
	int shipH = SCREEN_HEIGHT / 20;
	ship->setX((float)(SCREEN_WIDTH / 2 - shipW / 2));
	ship->setY((float)(SCREEN_HEIGHT / 2 - shipH / 2));
	ship->setW(shipW);
	ship->setH(shipH);
	ticksCount = SDL_GetTicks();

	SDL_Log("start process is completed");
	return true;
}

void Game::show() {
	menu->showBackground(renderer);
	switch (menu->getIndexMenu()) {
	case 0:
		menu->showMenu0(renderer);
		break;
	case 1:
		menu->showMenu1(renderer, lifes);
		ship->show(renderer);
		for (auto ast : asteroids) {
			ast->showAsteroid(renderer);
		}
		for (auto bullet : ship->getBullets()) {
			bullet->showBullet(renderer);
		}
		ship->showMenuBullets(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, ship->getW() / 2, ship->getH() / 2);
		break;
	case 2:
		menu->showMenu2(renderer);
		break;
	}
	SDL_RenderPresent(renderer);
}

void Game::collisionBulletAsteroids() {
	if (ship->getBullets().size() > 0) {
		std::size_t i = ship->getBullets().size() - 1;
		while (true) {

			if (asteroids.size() > 0) {

				std::size_t j = asteroids.size() - 1;
				while (true) {

					SDL_Rect rect = { (int)asteroids[j]->getX(),(int)asteroids[j]->getY(),asteroids[j]->getW(),asteroids[j]->getH() };
					SDL_Rect shipRect;
					Bullet* bullet = ship->getBullets()[i];
					shipRect.x = (int)bullet->getX();
					shipRect.y = (int)bullet->getY();
					shipRect.w = bullet->getW();
					shipRect.h = bullet->getH();
					if (SDL_HasIntersection(&rect, &shipRect)) {

						ship->deleteBullet(ship->getBullets()[i]);

						int lastw, lasth;
						float lastSpeed, lastOAngle, lastx, lasty;
						lastw = asteroids[j]->getW();
						lasth = asteroids[j]->getH();
						lastx = asteroids[j]->getX();
						lasty = asteroids[j]->getY();
						lastOAngle = asteroids[j]->getOriginalAngle();
						lastSpeed = asteroids[j]->getSpeed();
						deleteAsteroid(asteroids[j]);

						menu->incrementScore(renderer, SCREEN_HEIGHT / 6);
						if (menu->getScore() % 50 == 0 && lifes < 8)
							lifes++;

						//the big asteroids spawn 2 tiny asteroids
						if (lastw > SCREEN_HEIGHT / 8) {
							//first asteroid
							float newX, newY, newAngle;
							int newWidth, newHeight;
							newWidth = lastw / 2;
							newHeight = newWidth;
							newX = (float)(lastx + lastw / 2 - newWidth / 2);
							newY = (float)(lasty + lasth / 2 - newHeight / 2);
							newAngle = lastOAngle - 22;

							Asteroid* asteroid1 = new Asteroid();
							asteroid1->setAngle(0);
							asteroid1->setX(newX);
							asteroid1->setY(newY);
							asteroid1->setW(newWidth);
							asteroid1->setH(newHeight);
							asteroid1->setMulX(cos(newAngle * PI / 180));
							asteroid1->setMulY(sin(newAngle * PI / 180));
							asteroid1->setSpeed(lastSpeed);
							addAsteroid(asteroid1);

							//second asteroid
							Asteroid* asteroid2 = new Asteroid();
							newAngle += 45;
							asteroid2->setAngle(0);
							asteroid2->setX(newX);
							asteroid2->setY(newY);
							asteroid2->setW(newWidth);
							asteroid2->setH(newHeight);
							asteroid2->setMulX(cos(newAngle * PI / 180));
							asteroid2->setMulY(sin(newAngle * PI / 180));
							asteroid2->setSpeed(lastSpeed);
							addAsteroid(asteroid2);
						}
						break;
					}
					if (j == 0)
						break;
					else
						j--;
				}
			}
			if (i == 0)
				break;
			else
				i--;
		}
	}
}

void Game::collisionShipAsteroids(SDL_Renderer* renderer, int x, int y, int w, int h) {
	int i = 0;
	SDL_Rect ship;
	ship.x = x;
	ship.y = y;
	ship.w = w;
	ship.h = h;
	for (auto ast : asteroids) {
		SDL_Rect rect = { (int)ast->getX(),(int)ast->getY(),ast->getW(),ast->getH() };
		if (SDL_HasIntersection(&ship, &rect)) {
			lifes--;
			restart();
			return;
		}
		i++;
	}
}

void Game::update(float deltaTime) {
	ship->move();
	if (ship->getBullets().size() > 0) {
		std::size_t i = ship->getBullets().size() - 1;
		while (true) {
			ship->getBullets()[i]->moveBullet(deltaTime);
			SDL_Rect rect;
			Bullet* bullet = ship->getBullets()[i];
			rect.x = (int)bullet->getX();
			rect.y = (int)bullet->getY();
			rect.w = bullet->getW();
			rect.h = bullet->getH();
			if (checkRectOutOfScreen(rect))
				ship->deleteBullet(ship->getBullets()[i]);
			if (i == 0)
				break;
			else
				i--;
		}
	}

	if (asteroids.size() > 0) {
		std::size_t i = asteroids.size() - 1;
		while (true) {
			asteroids[i]->moveAsteroid(deltaTime);
			SDL_Rect rect = { (int)asteroids[i]->getX(),(int)asteroids[i]->getY(),asteroids[i]->getW(),asteroids[i]->getH() };
			if (checkRectOutOfScreen(rect))
				deleteAsteroid(asteroids[i]);
			if (i == 0)
				break;
			else
				i--;
		}
	}

	checkShip();
	ship->decrementVelocity(deltaTime);
	checkNewAsteroid(deltaTime);
	collisionBulletAsteroids();
	collisionShipAsteroids(renderer, (int)ship->getX(), (int)ship->getY(), ship->getW(), ship->getH());
	ship->incrementBullet(deltaTime);
	ship->downShipShoot(deltaTime);
}

void Game::closeGame() {
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	closeSprite();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

void Game::loop() {
	while (!gameOver) {
		int fps = 60;
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + (1000 / fps)))
			;

		float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}
		ticksCount = SDL_GetTicks();

		const Uint8* keys = SDL_GetKeyboardState(NULL);
		menu->detectMenuKeys(keys, &gameOver);
		if (menu->getIndexMenu() == 1) {
			ship->detectKey(keys, deltaTime);
			update(deltaTime);
		}
		show();
	}
}

//restart when all lifes are lost
void Game::completeRestartGame() {
	lifes = 3;
}

void Game::setTimerAsteroids(float time) {
	timerAsteroids = time;
}

void Game::addAsteroid(class Asteroid* asteroid) {
	asteroids.push_back(asteroid);
}

void Game::deleteAsteroid(class Asteroid* asteroid) {
	auto index = std::find(asteroids.begin(), asteroids.end(), asteroid);
	if (index != asteroids.end())
		asteroids.erase(index);
}

void Game::generateAsteroid(int width, int height) {
	Asteroid* asteroid = new Asteroid();

	int newW = (rand() % (height / 4) + height / 24) / 2;
	int newH = newW;
	int newX;
	int newY;
	asteroid->setW(newW);
	asteroid->setH(newH);
	double enemyAngle = rand() % 90;

	switch (rand() % 4) {
	case 0:
		//the asteroid appears on the superior side
		newX = rand() % height;
		newY = 1 - newH;
		asteroid->setX((float)newX);
		asteroid->setY((float)newY);
		asteroid->setMulX(cos((enemyAngle + 45) * PI / 180));
		asteroid->setMulY(sin((enemyAngle + 45) * PI / 180));
		asteroid->setAngle((float)(enemyAngle + 45 - 90));
		asteroid->setOriginalAngle((float)(enemyAngle + 45));
		break;
	case 1:
		//the asteroid appears on the left side
		newX = 1 - newW;
		newY = rand() % height;
		asteroid->setX((float)newX);
		asteroid->setY((float)newY);
		asteroid->setMulX(cos((enemyAngle - 45) * PI / 180));
		asteroid->setMulY(sin((enemyAngle - 45) * PI / 180));
		asteroid->setAngle((float)(enemyAngle - 45 - 90));
		asteroid->setOriginalAngle((float)(enemyAngle - 45));
		break;
	case 2:
		//the asteroid appears on the inferior side
		newX = rand() % width;
		newY = height - 1;
		asteroid->setX((float)newX);
		asteroid->setY((float)newY);
		asteroid->setMulX(cos((enemyAngle + 225) * PI / 180));
		asteroid->setMulY(sin((enemyAngle + 225) * PI / 180));
		asteroid->setAngle((float)(enemyAngle + 225 - 90));
		asteroid->setOriginalAngle((float)(enemyAngle + 225));
		break;
	case 3:
		//the asteroid appears on the right side
		newX = width - 1;
		newY = rand() % height;
		asteroid->setX((float)newX);
		asteroid->setY((float)newY);
		asteroid->setMulX(cos((enemyAngle + 135) * PI / 180));
		asteroid->setMulY(sin((enemyAngle + 135) * PI / 180));
		asteroid->setOriginalAngle((float)(enemyAngle + 135));
		break;
	}
	asteroid->setSpeed(((float)(rand() % (height / 64) + 1)) * 30);
	addAsteroid(asteroid);
}

//every 0.5 seconds an asteroid is generated
void Game::checkNewAsteroid(float deltaTime) {
	timerAsteroids += deltaTime;
	if (timerAsteroids > 0.5) {
		timerAsteroids = 0;
		generateAsteroid(getWidth(), getHeight());
	}
}

void Game::restartAsteroids() {
	while (asteroids.size() > 0) {
		asteroids.pop_back();
	}
}

bool Game::checkRectOutOfScreen(SDL_Rect rect) {
	if (rect.x > SCREEN_WIDTH || rect.x + rect.w < 0
		|| rect.y > SCREEN_HEIGHT || rect.y + rect.h < 0) {
		return true;
	}
	return false;
}

//this method moves the ship to the contrary side when the ship are on the edges of the game
void Game::checkShip() {
	if (ship->getX() + ship->getW() < 0)
		ship->setX((float)(SCREEN_WIDTH - 1));
	else if (ship->getX() >= SCREEN_WIDTH)
		ship->setX((float)(-ship->getW()));
	if (ship->getY() + ship->getH() < 0)
		ship->setY((float)(SCREEN_HEIGHT - 1));
	else if (ship->getY() >= SCREEN_HEIGHT)
		ship->setY((float)(-ship->getH()));
}

void Game::restartShip() {
	ship->setX((float)(SCREEN_WIDTH / 2 - ship->getW() / 2));
	ship->setY((float)(SCREEN_HEIGHT / 2 - ship->getH() / 2));
	ship->setAngle(0);
	ship->setSpeed(0);
}

void Game::restart() {
	restartAsteroids();
	ship->restartBullets();
	restartShip();
	if (lifes <= 0) {
		ship->completeRestartBullets();
		completeRestartGame();
		menu->completeRestartMenu(renderer, SCREEN_HEIGHT / 6);
	}
}