// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "Paddle.h"
#include "Ball.h"
#include "Menu.h"
#include "Brick.h"
#include "Update.h"
#include "Command.h"
#include "Capsule.h"
#include "Render.h"

bool init(SDL_Window** window, SDL_Renderer** renderer) {
	if (!initRenderer(window, renderer, getScreenWidth(), getScreenHeight()))
		return false;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());

		SDL_Quit();
		return false;
	}

	if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		SDL_Log("Unable to initialize SDL_image: %s", SDL_GetError());
		return false;
	}

	if (TTF_Init() < 0) {
		SDL_Log("Unable to initialize SDL_ttf: %s", SDL_GetError());
		return false;
	}

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		SDL_Log("Audio is not working");
	}
	Mix_VolumeMusic(SDL_MIX_MAXVOLUME / 2);

	SDL_Log("start process is completed");
	return true;
}

void initVariables(SDL_Renderer* renderer) {
	initMenu(renderer);
	initPaddle();
	initBall();
	createRectangles();
	initCommandLine();
	initCapsuleVariables(renderer);
}