// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
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
#include "Render.h"
#include "Capsule.h"
#include "Command.h"

int main(int argc, char* args[]) {
	SDL_Window* window;
	SDL_Renderer* renderer;
	if (!init(&window, &renderer))
		return -1;

	Uint32 ticksCount;
	ticksCount = SDL_GetTicks();
	loadMusic();
	loadImage(renderer, "images/ball1.png", &ballTexture);
	initRandom();
	initBrickTextures(renderer);
	initVariables(renderer);
	loadBackgroundImages(renderer);
	writeGameMenu(renderer);
	writePauseMenu(renderer);
	writeAllCommands(renderer);
	initBackgroundIndex();
	loadBackgroundImage(renderer);
	initCapsules(1 + rand() % totalRectangles, totalRectangles);
	Mix_PlayMusic(music, -1);
	while (!gameOver) {

		int fps = 120;
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
				start(deltaTime, renderer);
				updatePaddle(deltaTime);
			}
			detectGameKey(renderer, actualFPS, window);
		}
		else {
			detectPauseKey(renderer, actualFPS, window);
		}
		show(renderer);
		if (fpsActive)
			generateTextTexture({ 36,144,98 }, "fonts/OpenSans-Bold.ttf", fpsTextRect.h, std::to_string(fps), &fpsText, &fpsTextRect, renderer);
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