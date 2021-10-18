#pragma once
#include <string>

class Menu {
public:
	Menu(SDL_Renderer* renderer, int totalWidth, int totalHeight);
	void showBackground(SDL_Renderer* renderer);
	void showMenu0(SDL_Renderer* renderer);
	void showMenu1(SDL_Renderer* renderer, int lifes);
	void showMenu2(SDL_Renderer* renderer);
	void completeRestartMenu(SDL_Renderer* renderer, int height);
	void detectMenuKeys(const Uint8* keys, bool* gameOver);
	int getIndexMenu() const { return indexMenu; }
	void setIndexMenu(const int index) { indexMenu = index; }
	int getScore() const { return score; }
	void incrementScore(SDL_Renderer* renderer, int height);
private:
	void generateMenu(SDL_Renderer* renderer, int totalHeight);
	void changeTextScore(SDL_Renderer* renderer, std::string newText, int height);
	SDL_Rect backgroundRect;
	int indexMenu = 0;
	int score = 0;
	int k = 9; //number to increment the width of the numberScoreRect: it takes the numbers 9,99,999,etc

	//menu 0 
	SDL_Rect menu0Rects[4];
	/*
	0-> title
	1-> play
	2-> controls
	3-> exit
	*/

	//menu 1 (game)
	SDL_Rect gameRects[4];
	/*
	0-> score (text)
	1-> life
	2-> ship life
	3-> score (number)
	*/

	//menu 2 (controls)
	SDL_Rect instructionRects[4];
};