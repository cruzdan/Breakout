#include <SDL.h>
#include "Menu.h"
#include "Ball.h"
#include "Joystick.h"
#include "Music.h"
#include "Init.h"
#include "Key.h"
#include "Close.h"
#include "Update.h"
#include "Show.h"
#include "Brick.h"
#include "FPS.h"
#include "Paddle.h"

SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char* args[]) {
	if (!init(&window, &renderer))
		return -1;
	loadMusic();
	loadImage(renderer);
	initVariables();
	activateBricks();
	loadJoystick();
	writeGameMenu(renderer);
	writePauseMenu(renderer);
	Mix_PlayMusic(music, -1);
	const int frameDelay = 1000 / 60;
	while (!gameOver) {
		beforeFPS();
		if (menuIndex == 0) {
			if (!serve) {
				update(renderer);
			}
			else {
				start(frameDelay);
				countStart(renderer);
				updatePaddle();
			}
			detectGameKey(renderer);
			if (totalJoysticks > 0)
				detectKeyJoystick();
		}
		else {
			detectPauseKey(renderer);
		}
		show(renderer);
		afterFPS(renderer);
	}
	close(window, renderer);
	return 0;
}

/*
Music: Happy Clappy Ukulele by Shane Ivers - https://www.silvermansound.com
Licensed under Creative Commons Attribution 4.0 International License
https://creativecommons.org/licenses/by/4.0/
Music promoted by https://www.chosic.com/
*/