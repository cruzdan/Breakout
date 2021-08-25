#include <SDL.h>
#include "GlobalVariables.h"
#include "Ball.h"
#include "Menu.h"

int paddleVelocity = SCREEN_WIDTH / 180;
SDL_Rect paddle1;
SDL_Rect paddle2;

void moveArtificialPaddle() {
	if (ballSpeedY > 0 && paddle2.y + paddle2.h + paddleVelocity <= board.y + board.h) {
		paddle2.y += paddleVelocity;
	}
	else if (ballSpeedY < 0 && paddle2.y - paddleVelocity >= board.y) {
		paddle2.y -= paddleVelocity;
	}
}

void movePaddleUp(SDL_Rect* paddle) {
	if (paddle->y - paddleVelocity >= board.y) {
		paddle->y -= paddleVelocity;
	}
}

void movePaddleDown(SDL_Rect* paddle) {
	if (paddle->y + paddle->h + paddleVelocity <= board.y + board.h) {
		paddle->y += paddleVelocity;
	}
}

void centerPaddles() {
	paddle1.y = menu.h + board.h / 2 - paddle1.h / 2;
	paddle2.y = paddle1.y;
}

void initPaddle() {
	paddle1 = { SCREEN_WIDTH / 72, menu.h + board.h / 2 - paddle1.h / 2, SCREEN_WIDTH / 360, SCREEN_HEIGHT / 8 };
	paddle2 = { menu.w - paddle2.w - paddle1.x, paddle1.y, paddle1.w, paddle1.h };
}