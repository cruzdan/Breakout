#include <SDL_image.h>
#include <iostream>
#include "GlobalVariables.h"
#include "Menu.h"
#include "Music.h"
#include "Paddle.h"
int ballSpeedX = SCREEN_WIDTH / 98;
int ballSpeedY = SCREEN_WIDTH / 98;
SDL_Rect ballImageRect;
SDL_Texture* ballImageTexture;
SDL_Rect ball;
bool serve = true;
int timer = 0;

void centerBall() {
	ball.x = board.w / 2 - ball.w / 2;
	ball.y = menu.h + board.h / 2 - ball.h / 2;
}

void moveBall() {
	int xI = ball.x + ballSpeedX;
	int xF = xI + ball.w;
	int yI = ball.y + ballSpeedY;
	int yF = yI + ball.h;

	if (SDL_HasIntersection(&ball, &paddle1) || SDL_HasIntersection(&ball, &paddle2)) {
		ballSpeedX = -ballSpeedX;
		Mix_PlayChannel(1, sound, 0);
	}
	else {
		if (xI < board.x) {
			score2++;
			centerBall();
			centerPaddles();
			updateScore();
			serve = true;
		}
		else if (xF > board.x + board.w) {
			score1++;
			centerBall();
			centerPaddles();
			updateScore();
			serve = true;
		}
	}

	ball.x += ballSpeedX;
	if (yI < board.y || yF > board.y + board.h) {
		ballSpeedY = -ballSpeedY;
	}
	ball.y += ballSpeedY;
}

void initBall() {
	ball.w = board.w / 30;
	ball.h = ball.w;
	ball.x = menu.w / 2 - ball.w / 2;
	ball.y = menu.h + board.h / 2 - ball.h / 2;
}

void loadImageBall() {
	extern SDL_Renderer* renderer;
	SDL_Surface* image;
	image = IMG_Load("images/ball1.png");
	if (!image) {
		std::cout << "the image can't be loaded" << std::endl;
	}
	ballImageTexture = SDL_CreateTextureFromSurface(renderer, image);
	assignProperties(&ballImageRect, image->w, image->h, 0, 0);
	SDL_FreeSurface(image);
}

void closeBall() {
	SDL_DestroyTexture(ballImageTexture);
}

void start(int time) {
	timer += time;
	if (timer >= 3000) {
		timer = 0;
		serve = false;
	}
}