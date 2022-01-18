// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Ball.h"
#include "Menu.h"
#include "Music.h"
#include "Command.h"
#include "Capsule.h"
#include "Render.h"

void closeTextures() {
	closeTextureBall();
	closeMenu();
	closeCommand();
	closeFPS();
	closeAllCommands();
}

void close(SDL_Window* window, SDL_Renderer* renderer) {
	closeTextures();
	closeMusic();
	closeCapsule();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	closeRenderer(window, renderer);
	SDL_Quit();
}