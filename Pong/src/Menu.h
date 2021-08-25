#pragma once
#include <SDL.h>
extern SDL_Rect board;
extern SDL_Rect menu;
extern int score1;
extern int score2;
extern SDL_Rect menu2_6Rect;
extern SDL_Rect menu2_7Rect;
extern SDL_Rect player1Rect;
extern SDL_Rect player2Rect;
extern SDL_Rect menuExitRect;
//set the SDL_Rect rect on the specified y, with x = 0, and h = menu.h / 4 on the pause menu
void assignPropertiesPauseMenu(SDL_Rect* rect, int y);
void assignProperties(SDL_Rect* rect, int w, int h, int x, int y);
//update the score
void updateScore();
void initMenu();
//init Pause menu
void initPauseMenu();
//init Game menu
void initGameMenu();
//init Start menu
void initStartMenu();
void drawStartMenu();
void drawGameMenu();
void drawPauseMenu();
//this method writes the timer square to start the game
void countStart();
void closeMenu();