// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "GlobalVariables.h"
#include "Music.h"
#include "Key.h"
#include "Menu.h"
#include "Ball.h"
#include "Paddle.h"
#include "Init.h"
#include "Render.h"

void initVariables(SDL_Renderer* renderer) {
	initMenu(renderer);
	initPaddle();
	initBall(renderer);
}

void closeTextures() {
	closeMenu();
	closeBall();
}

void close(SDL_Renderer* renderer, SDL_Window* window) {
	closeTextures();
	closeRenderer(window, renderer);
	closeMusic();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	if (!initRenderer(&window, &renderer, SCREEN_WIDTH, SCREEN_HEIGHT))
		return -1;
	if (!init())
		return -1;
	initSounds();
	initKeyboard();
	loadImage(renderer, "images/ball1.png", &ballImageTexture);
	initVariables(renderer);

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	unsigned int frameStart;
	int frameTime = 0;

	while (!gameOver) {

		frameStart = SDL_GetTicks();
		switch (menuIndex) {

		case 0:
			drawStartMenu(renderer);
			detectKeyStart();
			break;

		case 1:
			if (!serve) {
				moveBall(renderer);
			}
			else {
				start(frameDelay);
				countStart(renderer);
			}
			if (players == 1) {
				detectKeyGame_1();
				moveArtificialPaddle();
			}
			else {
				detectKeyGame_2();
			}
			drawGameMenu(renderer);
			break;

		case 2:
			detectKeyPause();
			drawPauseMenu(renderer);
		}

		frameTime = SDL_GetTicks() - frameStart;

		if (frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
	close(renderer, window);
	return 0;
}