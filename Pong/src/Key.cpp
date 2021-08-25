#include <SDL.h>
#include "Music.h"
#include "Menu.h"
#include "Paddle.h"
#include "Ball.h"
const unsigned char* keys;
int menuIndex = 0;
int gameOver = 0;
int players;

void initKeyboard() {
	keys = SDL_GetKeyboardState(NULL);
}

void detectKeyPause() {
	SDL_Event event;
	int typeEvent;
	if (SDL_PollEvent(&event)) {
		typeEvent = event.type;
		if (typeEvent == SDL_KEYDOWN) {
			if (keys[SDL_SCANCODE_ESCAPE]) {
				menuIndex = 1;
				updateMusic();
			}
		}
		else if (typeEvent == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {

				int mouseX;
				int mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				SDL_Rect mouseRect;
				mouseRect.x = mouseX;
				mouseRect.y = mouseY;
				mouseRect.w = 1;
				mouseRect.h = 1;

				if (SDL_HasIntersection(&mouseRect, &menu2_6Rect)) {
					menuIndex = 0;
				}
				else if (SDL_HasIntersection(&mouseRect, &menu2_7Rect)) {
					gameOver = 1;
				}
			}
		}
		else if (typeEvent == SDL_QUIT) {
			gameOver = 1;
		}
	}
}

void detectKeyGame_1() {
	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) gameOver = true;
	}
	if (keys[SDL_SCANCODE_W]) {
		movePaddleUp(&paddle1);
	}
	if (keys[SDL_SCANCODE_S]) {
		movePaddleDown(&paddle1);
	}
	if (keys[SDL_SCANCODE_ESCAPE]) {
		menuIndex = 2;
		updateMusic();
	}
	if (keys[SDL_SCANCODE_R]) {
		score1 = 0;
		score2 = 0;
		timer = 0;
		serve = true;
		centerBall();
		centerPaddles();
	}
}

void detectKeyGame_2() {

	SDL_Event e;
	while (SDL_PollEvent(&e)) {
		if (e.type == SDL_QUIT) gameOver = true;
	}
	if (keys[SDL_SCANCODE_DOWN]) {
		movePaddleDown(&paddle2);
	}
	if (keys[SDL_SCANCODE_UP]) {
		movePaddleUp(&paddle2);
	}
	if (keys[SDL_SCANCODE_W]) {
		movePaddleUp(&paddle1);
	}
	if (keys[SDL_SCANCODE_S]) {
		movePaddleDown(&paddle1);
	}
	if (keys[SDL_SCANCODE_ESCAPE]) {
		menuIndex = 2;
		updateMusic();
	}
	if (keys[SDL_SCANCODE_R]) {
		score1 = 0;
		score2 = 0;
		timer = 0;
		serve = true;
		centerBall();
		centerPaddles();
	}
}

void detectKeyStart() {
	
	SDL_Event event;
	int typeEvent;
	if (SDL_PollEvent(&event)) {
		typeEvent = event.type;
		if (typeEvent == SDL_KEYDOWN) {
			if (keys[SDL_SCANCODE_ESCAPE]) {
				gameOver = 1;
			}
		}
		else if (typeEvent == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT) {
				int mouseX;
				int mouseY;
				SDL_GetMouseState(&mouseX, &mouseY);
				SDL_Rect mouseRect;
				mouseRect.x = mouseX;
				mouseRect.y = mouseY;
				mouseRect.w = 1;
				mouseRect.h = 1;

				if (SDL_HasIntersection(&mouseRect, &player1Rect)) {
					menuIndex = 1;
					players = 1;
					updateMusic();
				}
				else if (SDL_HasIntersection(&mouseRect, &player2Rect)) {
					menuIndex = 1;
					players = 2;
					updateMusic();
				}
				else if (SDL_HasIntersection(&mouseRect, &menuExitRect)) {
					gameOver = 1;
				}
			}
		}
		else if (typeEvent == SDL_QUIT) {
			gameOver = 1;
		}
	}
}