#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Menu.h"
#include "Paddle.h"
#include "GlobalVariables.h"

SDL_Rect ballRect;
SDL_Surface* ballImage;
SDL_Texture* ballTexture;
int ballSpeedX;
int ballSpeedY;
int ballSpeedChange;
int maxBallSpeed;

void centerBall() {
	ballRect.x = boardWidth / 2 - ballRect.w / 2;
	ballRect.y = paddle.y - ballRect.h;
}

void closeTextureBall() {
	SDL_DestroyTexture(ballTexture);
}

void initBall() {
	ballRect.w = boardWidth / 40;
	ballRect.h = SCREEN_HEIGHT / 30;
	ballRect.x = boardWidth / 2 - ballRect.w / 2;
	ballRect.y = paddle.y - ballRect.h;

	ballSpeedX = SCREEN_WIDTH / 128;
	ballSpeedY = -SCREEN_HEIGHT / 72;
	ballSpeedChange = ballSpeedX / 2;
	maxBallSpeed = ballSpeedChange * 4;
}

void changeBallMovementWithBrick(SDL_Rect rect, SDL_Rect brick) {
	if (ballSpeedY > 0 && rect.y < brick.y) {
		ballSpeedY = -ballSpeedY;
	}
	else if (rect.y + rect.h > brick.y + brick.h) {
		ballSpeedY = -ballSpeedY;
	}
	else if (ballSpeedX > 0 && rect.x < brick.x) {
		ballSpeedX = -ballSpeedX;
	}
	else if (rect.x + rect.w > brick.x + brick.w) {
		ballSpeedX = -ballSpeedX;
	}
}

void incrementBallSpeedX() {
	if (ballSpeedX > 0)
		ballSpeedX += ballSpeedChange;
	else
		ballSpeedX -= ballSpeedChange;
}

void incrementBallSpeedY() {
	int incrementY = SCREEN_HEIGHT / 72;
	if (ballSpeedY > 0)
		ballSpeedY += incrementY;
	else
		ballSpeedY -= incrementY;
}

void decrementBallSpeedX() {
	if (ballSpeedX > 0) {
		if (ballSpeedX - ballSpeedChange > 0)
			ballSpeedX -= ballSpeedChange;
	}
	else if (ballSpeedX + ballSpeedChange < 0)
		ballSpeedX += ballSpeedChange;
}

void decrementBallSpeedY() {
	int incrementY = SCREEN_HEIGHT / 72;
	if (ballSpeedY > 0) {
		if (ballSpeedY - incrementY > 0)
			ballSpeedY -= incrementY;
	}
	else if (ballSpeedY + incrementY < 0)
		ballSpeedY += incrementY;
}

//get the actual speed paddle in termns of changeSpeed
int getMultiplicatorBallSpeed() {
	return (ballSpeedX / ballSpeedChange);
}

//set the paddleSpeed in a multiplicator of changeSpeed
void setMultiplicatorBallSpeed(int balleMultiplicator) {
	ballSpeedX = balleMultiplicator * ballSpeedChange;
}