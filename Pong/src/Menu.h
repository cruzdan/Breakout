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
void updateScore(SDL_Renderer* renderer);
void initMenu(SDL_Renderer* renderer);
//init Pause menu
void initPauseMenu(SDL_Renderer* renderer);
//init Game menu
void initGameMenu(SDL_Renderer* renderer);
//init Start menu
void initStartMenu(SDL_Renderer* renderer);
void drawStartMenu(SDL_Renderer* renderer);
void drawGameMenu(SDL_Renderer* renderer);
void drawPauseMenu(SDL_Renderer* renderer);
//this method writes the timer square to start the game
void countStart(SDL_Renderer* renderer);
void closeMenu();