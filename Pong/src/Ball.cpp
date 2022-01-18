// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL_image.h>
#include <iostream>
#include "GlobalVariables.h"
#include "Menu.h"
#include "Music.h"
#include "Paddle.h"
#include "Render.h"

int ballSpeedX = SCREEN_WIDTH / 130;
int ballSpeedY = SCREEN_WIDTH / 130;
SDL_Texture* ballImageTexture;
SDL_Rect ball;
bool serve = true;
int timer = 0;

void centerBall() {
	ball.x = board.w / 2 - ball.w / 2;
	ball.y = menu.h + board.h / 2 - ball.h / 2;
}

void moveBall(SDL_Renderer* renderer) {
	int xI = ball.x + ballSpeedX;
	int xF = xI + ball.w;
	int yI = ball.y + ballSpeedY;
	int yF = yI + ball.h;

	if (SDL_HasIntersection(&ball, &paddle1)) {
		ballSpeedX = abs(ballSpeedX);
		Mix_PlayChannel(1, sound, 0);
	}
	else if (SDL_HasIntersection(&ball, &paddle2)) {
		ballSpeedX = -abs(ballSpeedX);
		Mix_PlayChannel(1, sound, 0);
	}
	else {
		if (xI < board.x) {
			score2++;
			centerBall();
			centerPaddles();
			updateScore(renderer);
			serve = true;
		}
		else if (xF > board.x + board.w) {
			score1++;
			centerBall();
			centerPaddles();
			updateScore(renderer);
			serve = true;
		}
	}

	ball.x += ballSpeedX;
	if (yI < board.y || yF > board.y + board.h) {
		ballSpeedY = -ballSpeedY;
	}
	ball.y += ballSpeedY;
}

void initBall(SDL_Renderer* renderer) {
	loadImage(renderer, "images/ball1.png", &ballImageTexture);

	ball.w = board.w / 30;
	ball.h = ball.w;
	ball.x = menu.w / 2 - ball.w / 2;
	ball.y = menu.h + board.h / 2 - ball.h / 2;
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