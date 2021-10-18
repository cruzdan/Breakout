#include <SDL.h>
#include "Menu.h"
#include "Ball.h"
#include "Music.h"
#include "Init.h"
#include "Key.h"
#include "Close.h"
#include "Update.h"
#include "Show.h"
#include "Brick.h"
#include "Paddle.h"
#include "Image.h"
#include "Capsule.h"
#include "Command.h"

SDL_Window* window;
SDL_Renderer* renderer;

int main(int argc, char* args[]) {
	if (!init(&window, &renderer))
		return -1;

	Uint32 ticksCount;
	ticksCount = SDL_GetTicks();

	loadMusic();
	loadImage(renderer, &ballTexture, "images/ball1.png");
	initRandom();
	initBrickTextures(renderer);
	initBrickRows();
	initVariables(renderer);
	initBrickLives(); 
	initBrickImageType();
	writeGameMenu(renderer);
	writePauseMenu(renderer);
	writeAllCommands(renderer);
	initBackgroundIndex();
	loadBackgroundImage(renderer);
	initCapsules(1 + rand() % totalRectangles, totalRectangles);
	Mix_PlayMusic(music, -1);

	while (!gameOver) {

		int fps = 60;
		while (!SDL_TICKS_PASSED(SDL_GetTicks(), ticksCount + (1000 / fps)))
			;

		float deltaTime = (SDL_GetTicks() - ticksCount) / 1000.0f;
		if (deltaTime > 0.05f)
		{
			deltaTime = 0.05f;
		}
		ticksCount = SDL_GetTicks();

		int actualFPS = (int)(1 / deltaTime);
		if (menuIndex == 0) {
			if (!serve) {
				update(renderer, deltaTime);
			}
			else {
				start(deltaTime);
				countStart(renderer);
				updatePaddle(deltaTime);
			}
			detectGameKey(renderer, actualFPS);
		}
		else {
			detectPauseKey(renderer, actualFPS);
		}
		show(renderer);
		if(fpsActive)
			writeFPSText(renderer, actualFPS);
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