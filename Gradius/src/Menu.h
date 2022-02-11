#pragma once
#include <SDL.h>
#include <vector>
#include "Ship.h"
#include "Vecs.h"

class Menu {
public:
	Menu();

	void setGameOver(const bool newGameOver) { gameOver = newGameOver; }
	void setIndex(const int newIndex) { index = newIndex; }
	void setPhase(const int newPhase) { phase = newPhase; }
	void setX(const float newX) { x = newX; }
	void setBackgroundSpeed(const float newSpeedBackground) { backgroundSpeed = newSpeedBackground; }
	void setWidth(const int newWidth) { width = newWidth; }
	void setHieght(const int newHeight) { height = newHeight; }
	void setPlayers(const int newP) { players = newP; }

	bool getGameOver() const { return gameOver; }
	int getIndex() const { return index; }
	int getPhase() const { return phase; }
	float getX() const { return x; }
	float getBackgroundSpeed() const { return backgroundSpeed; }
	int getWidth() const { return width; }
	int getHeight() const { return height; }
	int getPlayers() const { return players; }

	void showCP(SDL_Renderer* renderer);
	void updateCP(float deltaTIme);
	void keyIG(float deltaTime, const Uint8* keys);
	void showIG(SDL_Renderer* renderer, std::vector<class Ship*> ships);
	void keyPause(const Uint8* keys);
	void showPause(SDL_Renderer* renderer);
	void initPauseTextures(SDL_Renderer* renderer);
	void initPauseRects();
private:
	void showShipUpgradeImages(SDL_Renderer* renderer, Ship* ship);
	void showShipData(SDL_Renderer* renderer, Ship* ship);
	
	SDL_Texture* pauseTextures[11];
	Vec4 pauseRects[11];
	//0->choose players, 1->game, 2->pause
	bool gameOver;
	int players;
	int index;
	int phase;
	float x;
	float backgroundSpeed;
	int width;
	int height;
};