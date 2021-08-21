#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <SDL_image.h>
#include "Ball.h"
#include "Menu.h"
#include "Joystick.h"
#include "Music.h"
#include "Command.h"

void closeTextures() {
	closeTextureBall();
	closeMenu();
	closeCommand();
	closeFPS();
}

void close(SDL_Window* window, SDL_Renderer* renderer) {
	closeJoystick();
	closeTextures();
	closeMusic();
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}