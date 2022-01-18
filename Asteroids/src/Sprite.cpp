// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Sprite.h"
#include "SDL_image.h"
#include <iostream>
SDL_Texture* backgroundTexture;
SDL_Texture* shipTexture;
SDL_Texture* rocketTexture;
SDL_Texture* asteroidTexture;

//menu 0
SDL_Texture* titleTexture;
SDL_Texture* playTexture;
SDL_Texture* controlsTexture;
SDL_Texture* exitTexture;

//menu 1
SDL_Texture* scoreTexture;
SDL_Texture* lifeTexture;
SDL_Texture* numberScore;

//menu 2
SDL_Texture* instruction1Texture;
SDL_Texture* instruction2Texture;
SDL_Texture* instruction3Texture;
SDL_Texture* instruction4Texture;

void loadImage(SDL_Renderer* renderer) {
	SDL_Surface* image = 0;

	image = IMG_Load("images/background.png");
	if (!image) {
		std::cout << "failed in load background image" << std::endl;
	}
	backgroundTexture = SDL_CreateTextureFromSurface(renderer, image);

	image = IMG_Load("images/ship.png");
	if (!image) {
		std::cout << "failed in load ship image" << std::endl;
	}
	shipTexture = SDL_CreateTextureFromSurface(renderer, image);

	image = IMG_Load("images/rocket.png");
	if (!image) {
		std::cout << "failed in load rocket image" << std::endl;
	}
	else {
		SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 255, 255, 255));
		rocketTexture = SDL_CreateTextureFromSurface(renderer, image);
	}

	image = IMG_Load("images/asteroid.png");
	if (!image) {
		std::cout << "failed in load asteroid image" << std::endl;
	}
	asteroidTexture = SDL_CreateTextureFromSurface(renderer, image);

	SDL_FreeSurface(image);
}

void closeSprite() {
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(shipTexture);
	SDL_DestroyTexture(rocketTexture);
	SDL_DestroyTexture(asteroidTexture);
	SDL_DestroyTexture(scoreTexture);
	SDL_DestroyTexture(numberScore);
	SDL_DestroyTexture(lifeTexture);
	SDL_DestroyTexture(titleTexture);
	SDL_DestroyTexture(playTexture);
	SDL_DestroyTexture(controlsTexture);
	SDL_DestroyTexture(exitTexture);
	SDL_DestroyTexture(instruction1Texture);
	SDL_DestroyTexture(instruction2Texture);
	SDL_DestroyTexture(instruction3Texture);
	SDL_DestroyTexture(instruction4Texture);
}