#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Ball.h"
#include "Menu.h"
#include "Music.h"
#include "Command.h"
#include "Capsule.h"

void closeTextures() {
	closeTextureBall();
	closeMenu();
	closeCommand();
	closeFPS();
}

void close(SDL_Window* window, SDL_Renderer* renderer) {
	closeTextures();
	closeMusic();
	closeCapsule();
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}