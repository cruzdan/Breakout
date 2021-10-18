#pragma once
#include <SDL.h>
#include <vector>

class Game {
public:
	Game();
	int getLifes() const { return lifes; }
	void setLifes(const int value) { lifes = value; }
	int getWidth() const { return SCREEN_WIDTH; }
	void setWidth(const int width) { SCREEN_WIDTH = width; }
	int getHeight() const { return SCREEN_HEIGHT; }
	void setHeight(const int height) { SCREEN_HEIGHT = height; }
	bool init();
	void loop();
	void closeGame();
	void completeRestartGame();
	void restart();
private:
	void show();
	void update(float deltaTime);
	void collisionBulletAsteroids();
	void collisionShipAsteroids(SDL_Renderer* renderer, SDL_Rect ship);
	void setTimerAsteroids(float deltaTime);
	void checkNewAsteroid(float deltaTime);
	void restartAsteroids();
	void addAsteroid(class Asteroid* asteroid);
	void deleteAsteroid(class Asteroid* asteroid);
	void generateAsteroid(int width, int height);
	bool checkRectOutOfScreen(SDL_Rect rect);
	void checkShip();
	void restartShip();

	SDL_Window* window;
	SDL_Renderer* renderer;
	bool gameOver;
	int lifes;
	Uint32 ticksCount;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;

	float timerAsteroids;

	class Ship* ship;
	class Menu* menu;
	std::vector<class Asteroid*> asteroids;
};