#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include "GlobalVariables.h"
#include "Joystick.h"
#include "Music.h"
#include "Key.h"
#include "Menu.h"
#include "Ball.h"
#include "Paddle.h"
#include "Init.h"

SDL_Window* window;
SDL_Renderer* renderer;

void initVariables() {
	initMenu();
	initPaddle();
	initBall();
}

void closeTextures() {
	closeMenu();
	closeBall();
}

void close() {
	closeTextures();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	closeMusic();
	closeJoystick();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char* args[]) {
	if (!init(&window, &renderer))
		return -1;
	initSounds();
	initKeyboard();
	loadImageBall();
	initVariables();
	initJoystick();

	const int FPS = 60;
	const int frameDelay = 1000 / FPS;

	unsigned int frameStart;
	int frameTime = 0;

	while (!gameOver) {

		frameStart = SDL_GetTicks();
		switch (menuIndex) {

		case 0:
			drawStartMenu();
			detectKeyStart();
			break;

		case 1:
			if (!serve) {
				moveBall();
			}
			else {
				start(frameDelay);
				countStart();
			}
			if (players == 1) {
				if (totalJoysticks > 0)
					detectKeyJoystick(joystick1, &paddle1);
				detectKeyGame_1();
				moveArtificialPaddle();
			}
			else {
				if (totalJoysticks > 0) {
					if (totalJoysticks > 1) {
						detectKeyJoystick(joystick2, &paddle2);
					}
					detectKeyJoystick(joystick1, &paddle1);
				}

				detectKeyGame_2();
			}
			drawGameMenu();
			break;

		case 2:
			detectKeyPause();
			drawPauseMenu();
		}

		frameTime = SDL_GetTicks() - frameStart;

		if(frameDelay > frameTime)
			SDL_Delay(frameDelay - frameTime);
	}
	close();
	return 0;
}