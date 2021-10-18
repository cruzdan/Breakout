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
	lifes(3),
	ticksCount(0),
	SCREEN_WIDTH(720),
	SCREEN_HEIGHT(480),
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
	ship->setMaxSpeed((float)SCREEN_WIDTH * 60.0f / 144);
	ship->setChangeVel((float)SCREEN_WIDTH / 60);
	int shipW = SCREEN_WIDTH / 25;
	int shipH = SCREEN_HEIGHT / 10;
	ship->setRect(SCREEN_WIDTH / 2 - shipW / 2, SCREEN_HEIGHT / 2 - shipH / 2, shipW, shipH);
	ticksCount = SDL_GetTicks();

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
		ship->showMenuBullets(renderer, SCREEN_WIDTH, SCREEN_HEIGHT, ship->getRect().w / 2, ship->getRect().h / 2);
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

					SDL_Rect rect = asteroids[j]->getRect();
					SDL_Rect shipRect = ship->getBullets()[i]->getRect();
					if (SDL_HasIntersection(&rect, &shipRect)) {

						ship->deleteBullet(ship->getBullets()[i]);

						int lastw, lasth, lastx, lasty;
						float lastSpeed, lastOAngle;
						lastw = asteroids[j]->getRect().w;
						lasth = asteroids[j]->getRect().h;
						lastx = asteroids[j]->getRect().x;
						lasty = asteroids[j]->getRect().y;
						lastOAngle = asteroids[j]->getOriginalAngle();
						lastSpeed = asteroids[j]->getSpeed();
						deleteAsteroid(asteroids[j]);

						menu->incrementScore(renderer, SCREEN_HEIGHT / 6);
						if (menu->getScore() % 50 == 0 && lifes < 8)
							lifes++;

						//the big asteroids spawn 2 tiny asteroids
						if (lastw > SCREEN_HEIGHT / 4) {
							//first asteroid
							int newX, newY, newWidth, newHeight;
							float newAngle;
							newWidth = lastw / 2;
							newHeight = newWidth;
							newX = lastx + lastw / 2 - newWidth / 2;
							newY = lasty + lasth / 2 - newHeight / 2;
							newAngle = lastOAngle - 22;

							Asteroid* asteroid1 = new Asteroid();
							asteroid1->setAngle(0);
							asteroid1->setRect({ newX,newY,newWidth,newHeight });
							asteroid1->setMulX(cos(newAngle * PI / 180));
							asteroid1->setMulY(sin(newAngle * PI / 180));
							asteroid1->setSpeed(lastSpeed);
							addAsteroid(asteroid1);

							//second asteroid
							Asteroid* asteroid2 = new Asteroid();
							newAngle += 45;
							asteroid2->setAngle(0);
							asteroid2->setRect({ newX,newY,newWidth,newHeight });
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

void Game::collisionShipAsteroids(SDL_Renderer* renderer, SDL_Rect ship) {
	int i = 0;
	for (auto ast : asteroids) {
		SDL_Rect rect = ast->getRect();
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
			if (checkRectOutOfScreen(ship->getBullets()[i]->getRect()))
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
			if (checkRectOutOfScreen(asteroids[i]->getRect()))
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
	collisionShipAsteroids(renderer, ship->getRect());
	ship->incrementBullet(deltaTime);
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
		int fps = 30;
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + (1000 / fps) ))
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
	class Asteroid* asteroid = new Asteroid();
	SDL_Rect rect;

	rect.w = rand() % (height / 4) + height / 24;
	rect.h = rect.w;
	float enemyAngle = (float)(rand() % 90);

	switch (rand() % 4) {
	case 0:
		//the asteroid appears on the superior side
		rect.x = rand() % height;
		rect.y = 0;
		asteroid->setRect(rect);
		asteroid->setMulX(cos((enemyAngle + 45) * PI / 180));
		asteroid->setMulY(sin((enemyAngle + 45) * PI / 180));
		asteroid->setAngle(enemyAngle + 45 - 90);
		asteroid->setOriginalAngle(enemyAngle + 45);
		break;
	case 1:
		//the asteroid appears on the left side
		rect.x = 0;
		rect.y = rand() % height;
		asteroid->setRect(rect);
		asteroid->setMulX(cos((enemyAngle - 45) * PI / 180));
		asteroid->setMulY(sin((enemyAngle - 45) * PI / 180));
		asteroid->setAngle(enemyAngle - 45 - 90);
		asteroid->setOriginalAngle(enemyAngle - 45);
		break;
	case 2:
		//the asteroid appears on the inferior side
		rect.x = rand() % width;
		rect.y = height - rect.h;
		asteroid->setRect(rect);
		asteroid->setMulX(cos((enemyAngle + 225) * PI / 180));
		asteroid->setMulY(sin((enemyAngle + 225) * PI / 180));
		asteroid->setAngle(enemyAngle + 225 - 90);
		asteroid->setOriginalAngle(enemyAngle + 225);
		break;
	case 3:
		//the asteroid appears on the right side
		rect.x = width - rect.w;
		rect.y = rand() % height;
		asteroid->setRect(rect);
		asteroid->setMulX(cos((enemyAngle + 135) * PI / 180));
		asteroid->setMulY(sin((enemyAngle + 135) * PI / 180));
		asteroid->setOriginalAngle(enemyAngle + 135);
		break;
	}
	asteroid->setSpeed(((float)(rand() % (height / 64) + 1)) * 60);
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
	if (ship->getRect().x + ship->getRect().w < 0)
		ship->setRectX(SCREEN_WIDTH - 1);
	else if (ship->getRect().x >= SCREEN_WIDTH)
		ship->setRectX(-ship->getRect().w);
	if (ship->getRect().y + ship->getRect().h < 0)
		ship->setRectY(SCREEN_HEIGHT - 1);
	else if (ship->getRect().y >= SCREEN_HEIGHT)
		ship->setRectY(-ship->getRect().h);
}

void Game::restartShip() {
	ship->setRectX(SCREEN_WIDTH / 2 - ship->getRect().w / 2);
	ship->setRectY(SCREEN_HEIGHT / 2 - ship->getRect().h / 2);
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