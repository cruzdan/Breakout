// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include "GlobalVariables.h"
#include "Menu.h"
#include "Ball.h"
#include "Paddle.h"
#include "Render.h"

//Menu 0: Start
SDL_Texture* pongText;
SDL_Texture* player1Text;
SDL_Texture* player2Text;
SDL_Texture* menuExitText;
SDL_Rect pongRect;
SDL_Rect player1Rect;
SDL_Rect player2Rect;
SDL_Rect menuExitRect;

//Menu 1: Game
SDL_Texture* scoreText;
SDL_Texture* puntuation1Text;
SDL_Texture* puntuation2Text;
SDL_Texture* indication1Text;
SDL_Texture* indication2Text;
SDL_Rect menu;
SDL_Rect scoreRect;
SDL_Rect puntuation1Rect;
SDL_Rect puntuation2Rect;
SDL_Rect indication1Rect;
SDL_Rect indication2Rect;
int score1 = 0;
int score2 = 0;

//Menu 2: Pause
SDL_Texture* menuText2_0;
SDL_Texture* menuText2_1;
SDL_Texture* menuText2_2;
SDL_Texture* menuText2_3;
SDL_Texture* menuText2_4;
SDL_Texture* menuText2_5;
SDL_Texture* menuText2_6;
SDL_Texture* menuText2_7;
SDL_Rect menu2_0Rect;
SDL_Rect menu2_1Rect;
SDL_Rect menu2_2Rect;
SDL_Rect menu2_3Rect;
SDL_Rect menu2_4Rect;
SDL_Rect menu2_5Rect;
SDL_Rect menu2_6Rect;
SDL_Rect menu2_7Rect;
SDL_Rect board;

//pause
SDL_Texture* textStart;
SDL_Rect startRect;

void assignPropertiesPauseMenu(SDL_Rect* rect, int y) {
	rect->x = 0;
	rect->y = y;
	rect->h = menu.h / 4;
}

void assignProperties(SDL_Rect* rect, int w, int h, int x, int y) {
	rect->w = w;
	rect->h = h;
	rect->x = x;
	rect->y = y;
}

void updateScore(SDL_Renderer* renderer) {
	SDL_Color color = { 255,255,255 };
	std::string route = "fonts/Oswald-BoldItalic.ttf";
	int fontSize = SCREEN_HEIGHT / 30;

	generateTextTexture(color, route, fontSize, std::to_string(score1), &puntuation1Text, renderer);
	generateTextTexture(color, route, fontSize, std::to_string(score2), &puntuation2Text, renderer);
}

void initMenu(SDL_Renderer* renderer) {
	assignProperties(&menu, SCREEN_WIDTH, SCREEN_HEIGHT / 5, 0, 0);
	assignProperties(&board, SCREEN_WIDTH, SCREEN_HEIGHT - menu.h, 0, menu.h);
	assignProperties(&scoreRect, menu.w / 3, menu.h / 2, menu.w / 3, 0);
	assignProperties(&puntuation1Rect, menu.h / 5, menu.h / 2, menu.w / 3, menu.h / 2);
	assignProperties(&puntuation2Rect, puntuation1Rect.w, puntuation1Rect.h,
		menu.w / 8 + menu.w / 2, puntuation1Rect.y);
	int startRectSide = board.w / 5;
	assignProperties(&startRect, startRectSide, startRectSide,
		board.w / 2 - startRectSide / 2, menu.h + board.h / 2 - startRectSide / 2);
	pongRect.x = int(SCREEN_WIDTH * 0.4);
	pongRect.y = int(SCREEN_HEIGHT * 0.1);
	pongRect.w = int(SCREEN_WIDTH - 2 * pongRect.x);
	pongRect.h = int(SCREEN_HEIGHT * 0.1);

	player1Rect.x = int(SCREEN_WIDTH * 0.3);
	player1Rect.y = int(pongRect.y + pongRect.h + SCREEN_HEIGHT * 0.1);
	player1Rect.w = int(SCREEN_WIDTH - 2 * player1Rect.x);
	player1Rect.h = int(SCREEN_HEIGHT * 0.1);

	player2Rect.x = player1Rect.x;
	player2Rect.y = int(player1Rect.y + player1Rect.h + SCREEN_HEIGHT * 0.1);
	player2Rect.w = player1Rect.w;
	player2Rect.h = player1Rect.h;

	menuExitRect.y = int(player2Rect.y + player2Rect.h + SCREEN_HEIGHT * 0.1);
	menuExitRect.w = player2Rect.w / 2;
	menuExitRect.h = player2Rect.h;
	menuExitRect.x = int(SCREEN_WIDTH / 2 - menuExitRect.w / 2);

	assignProperties(&indication1Rect, menu.w / 6, menu.h / 4, 0, 0);
	assignProperties(&indication2Rect, indication1Rect.w, indication1Rect.h,
		scoreRect.x + scoreRect.w, 0);

	int spaceY = menu.h / 4;
	assignPropertiesPauseMenu(&menu2_0Rect, 0);
	menu2_0Rect.x = int(SCREEN_WIDTH / 2 - menu2_0Rect.w / 2);
	assignPropertiesPauseMenu(&menu2_1Rect, menu2_0Rect.y + menu2_0Rect.h + spaceY);
	assignPropertiesPauseMenu(&menu2_2Rect, menu2_1Rect.y + menu2_1Rect.h + spaceY);
	assignPropertiesPauseMenu(&menu2_3Rect, menu2_2Rect.y + menu2_2Rect.h + spaceY);
	assignPropertiesPauseMenu(&menu2_4Rect, menu2_3Rect.y + menu2_3Rect.h + spaceY);
	assignPropertiesPauseMenu(&menu2_5Rect, menu2_4Rect.y + menu2_4Rect.h + spaceY);
	assignPropertiesPauseMenu(&menu2_6Rect, menu2_5Rect.y + menu2_5Rect.h + spaceY);
	assignPropertiesPauseMenu(&menu2_7Rect, menu2_6Rect.y + menu2_6Rect.h + spaceY);

	initStartMenu(renderer);
	initGameMenu(renderer);
	initPauseMenu(renderer);
	updateScore(renderer);
}

void initPauseMenu(SDL_Renderer* renderer) {
	SDL_Color color = { 255,255,255 };
	std::string route = "fonts/Oswald-BoldItalic.ttf";
	int fontSize = SCREEN_HEIGHT / 30;

	generateTextTexture(color, route, fontSize, "Pause", &menuText2_0, &menu2_0Rect, renderer);
	generateTextTexture(color, route, fontSize, "Press w to move paddle 1 up", &menuText2_1, &menu2_1Rect, renderer);
	generateTextTexture(color, route, fontSize, "Press s to move paddle 1 down", &menuText2_2, &menu2_2Rect, renderer);
	generateTextTexture(color, route, fontSize, "Press up to move paddle 2 up", &menuText2_3, &menu2_3Rect, renderer);
	generateTextTexture(color, route, fontSize, "Press down to move paddle 2 down", &menuText2_4, &menu2_4Rect, renderer);
	generateTextTexture(color, route, fontSize, "Press ESC to resume", &menuText2_5, &menu2_5Rect, renderer);
	generateTextTexture(color, route, fontSize, "Click here to go to main menu", &menuText2_6, &menu2_6Rect, renderer);
	generateTextTexture(color, route, fontSize, "Click here to exit", &menuText2_7, &menu2_7Rect, renderer);
}

void initGameMenu(SDL_Renderer* renderer) {
	SDL_Color color = { 255,255,255 };
	std::string route = "fonts/Oswald-BoldItalic.ttf";
	int fontSize = SCREEN_HEIGHT / 30;

	generateTextTexture(color, route, fontSize, "Score", &scoreText, renderer);
	generateTextTexture(color, route, fontSize, "Press R to restart", &indication1Text, renderer);
	generateTextTexture(color, route, fontSize, "Press ESC to pause", &indication2Text, renderer);
}

void initStartMenu(SDL_Renderer* renderer) {
	SDL_Color color = { 255,255,255 };
	std::string route = "fonts/Oswald-BoldItalic.ttf";
	int fontSize = SCREEN_HEIGHT / 30;

	generateTextTexture(color, route, fontSize, "PONG", &pongText, renderer);
	generateTextTexture(color, route, fontSize, "1 Player", &player1Text, renderer);
	generateTextTexture(color, route, fontSize, "2 Players", &player2Text, renderer);
	generateTextTexture(color, route, fontSize, "Exit", &menuExitText, renderer);
}

void drawStartMenu(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, pongText, NULL, &pongRect);
	SDL_RenderCopy(renderer, pongText, NULL, &pongRect);
	SDL_RenderCopy(renderer, player1Text, NULL, &player1Rect);
	SDL_RenderCopy(renderer, player2Text, NULL, &player2Rect);
	SDL_RenderCopy(renderer, menuExitText, NULL, &menuExitRect);
	SDL_RenderPresent(renderer);
}

void drawGameMenu(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0);
	SDL_RenderFillRect(renderer, &menu);
	SDL_SetRenderDrawColor(renderer, 250, 250, 250, 0);
	SDL_RenderFillRect(renderer, &paddle1);
	SDL_RenderFillRect(renderer, &paddle2);
	SDL_RenderCopy(renderer, scoreText, NULL, &scoreRect);
	SDL_RenderCopy(renderer, puntuation1Text, NULL, &puntuation1Rect);
	SDL_RenderCopy(renderer, puntuation2Text, NULL, &puntuation2Rect);
	SDL_RenderCopy(renderer, indication1Text, NULL, &indication1Rect);
	SDL_RenderCopy(renderer, indication2Text, NULL, &indication2Rect);
	if (serve)
		SDL_RenderCopy(renderer, textStart, NULL, &startRect);
	else
		SDL_RenderCopy(renderer, ballImageTexture, NULL, &ball);
	SDL_RenderPresent(renderer);
}

void drawPauseMenu(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 50, 50, 50, 0);
	SDL_RenderCopy(renderer, menuText2_0, NULL, &menu2_0Rect);
	SDL_RenderCopy(renderer, menuText2_1, NULL, &menu2_1Rect);
	SDL_RenderCopy(renderer, menuText2_2, NULL, &menu2_2Rect);
	SDL_RenderCopy(renderer, menuText2_3, NULL, &menu2_3Rect);
	SDL_RenderCopy(renderer, menuText2_4, NULL, &menu2_4Rect);
	SDL_RenderCopy(renderer, menuText2_5, NULL, &menu2_5Rect);
	SDL_RenderCopy(renderer, menuText2_6, NULL, &menu2_6Rect);
	SDL_RenderCopy(renderer, menuText2_7, NULL, &menu2_7Rect);
	SDL_RenderPresent(renderer);
}

void countStart(SDL_Renderer* renderer) {
	SDL_Color color = { 255,255,255 };
	std::string route = "fonts/Oswald-Stencil.ttf";
	int fontSize = SCREEN_HEIGHT / 15;

	int m = timer / 1000 + 1;
	generateTextTexture(color, route, fontSize, std::to_string(m), &textStart, renderer);
}

void closeMenu() {
	SDL_DestroyTexture(scoreText);
	SDL_DestroyTexture(puntuation1Text);
	SDL_DestroyTexture(puntuation2Text);
	SDL_DestroyTexture(textStart);
	SDL_DestroyTexture(indication1Text);
	SDL_DestroyTexture(indication2Text);
	SDL_DestroyTexture(menuText2_0);
	SDL_DestroyTexture(menuText2_1);
	SDL_DestroyTexture(menuText2_2);
	SDL_DestroyTexture(menuText2_3);
	SDL_DestroyTexture(menuText2_4);
	SDL_DestroyTexture(menuText2_5);
	SDL_DestroyTexture(menuText2_6);
	SDL_DestroyTexture(menuText2_7);
	SDL_DestroyTexture(pongText);
	SDL_DestroyTexture(player1Text);
	SDL_DestroyTexture(player2Text);
	SDL_DestroyTexture(menuExitText);
}