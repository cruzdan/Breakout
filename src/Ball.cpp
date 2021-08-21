#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Menu.h"
#include "Paddle.h"
#include "GlobalVariables.h"
SDL_Rect ballImageRect;
SDL_Rect ballRect;
SDL_Surface* ballImage;
SDL_Texture* ballTexture;

void centerBall() {
	ballRect.x = boardWidth / 2 - ballRect.w / 2;
	ballRect.y = paddle.y - ballRect.h;
}

void loadImage(SDL_Renderer* renderer) {
	ballImage = IMG_Load("images/ball1.png");
	if (!ballImage) {
		std::cout << "failed in load image" << std::endl;
	}
	ballTexture = SDL_CreateTextureFromSurface(renderer, ballImage);
	ballImageRect.x = 0;
	ballImageRect.y = 0;
	ballImageRect.w = ballImage->w;
	ballImageRect.h = ballImage->h;
	SDL_FreeSurface(ballImage);
}

void closeTextureBall() {
	SDL_DestroyTexture(ballTexture);
}

void initBall() {
	ballRect.w = SCREEN_WIDTH / 30;
	ballRect.h = SCREEN_HEIGHT / 20;;
	ballRect.x = boardWidth / 2 - ballRect.w / 2;
	ballRect.y = paddle.y - ballRect.h;
}
