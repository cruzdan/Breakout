#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Menu.h"
#include "Paddle.h"
#include "GlobalVariables.h"

const int maxBalls = 8;

int actualBalls = 1;
SDL_Rect* ballRect;
SDL_Texture* ballTexture;
int* ballSpeedX;
int* ballSpeedY;
int ballSpeedChangeX;
int ballSPeedChangeY;
int maxBallSpeed;
int firstSpeedChangeX;
int firstSpeedChangeY;

void centerBall(int ballIndex) {
	ballRect[ballIndex].x = paddle.x + paddle.w / 2 - ballRect[ballIndex].w / 2;
	ballRect[ballIndex].y = paddle.y - ballRect[ballIndex].h;
}

void closeTextureBall() {
	SDL_DestroyTexture(ballTexture);
	delete[] ballRect;
	delete[] ballSpeedX;
	delete[] ballSpeedY;
}

void initBallSpeed(int ballIndex) {
	if (rand() % 2 < 1)
		ballSpeedX[ballIndex] = ballSpeedChangeX + ballSpeedChangeX;
	else
		ballSpeedX[ballIndex] = -(ballSpeedChangeX + ballSpeedChangeX);
	ballSpeedY[ballIndex] = -(ballSPeedChangeY + ballSPeedChangeY);
}

void adNewBall() {
	if (actualBalls < maxBalls) {
		centerBall(actualBalls);
		initBallSpeed(actualBalls);
		actualBalls++;
	}
}

void initBall() {
	ballRect = new SDL_Rect[maxBalls];
	ballSpeedX = new int[maxBalls];
	ballSpeedY = new int[maxBalls];
	for (int i = 0; i < maxBalls; i++) {
		ballRect[i].w = boardWidth / 40;
		ballRect[i].h = SCREEN_HEIGHT / 30;
	}

	ballSpeedChangeX = SCREEN_WIDTH / 256;
	ballSPeedChangeY = SCREEN_HEIGHT / 144;

	firstSpeedChangeX = ballSpeedChangeX / 2;
	firstSpeedChangeY = ballSPeedChangeY / 2;

	initBallSpeed(0);
	ballRect[0].x = boardWidth / 2 - ballRect[0].w / 2;
	ballRect[0].y = paddle.y - ballRect[0].h;

	maxBallSpeed = ballSpeedChangeX * 4;
}

SDL_Point* getActualBallPercentages(SDL_Point* percentages) {
	for (int i = 0; i < actualBalls; i++) {
		int centerX = ballRect[i].x + ballRect[i].w / 2;
		int centerY = ballRect[i].y + ballRect[i].h / 2;
		percentages[i].x = (centerX * 100) / SCREEN_WIDTH;
		percentages[i].y = (centerY * 100) / SCREEN_HEIGHT;
	}
	return percentages;
}

void reziseBalls() {
	for (int i = 0; i < maxBalls; i++) {
		ballRect[i].w = boardWidth / 40;
		ballRect[i].h = SCREEN_HEIGHT / 30;
	}
}

void changeBallMovementWithBrick(SDL_Rect brick, int ballIndex) {
	if (ballSpeedY[ballIndex] > 0 && ballRect[ballIndex].y < brick.y) {
		ballSpeedY[ballIndex] = -ballSpeedY[ballIndex];
	}
	else if (ballRect[ballIndex].y + ballRect[ballIndex].h > brick.y + brick.h) {
		ballSpeedY[ballIndex] = -ballSpeedY[ballIndex];
	}
	else if (ballSpeedX[ballIndex] > 0 && ballRect[ballIndex].x < brick.x) {
		ballSpeedX[ballIndex] = -ballSpeedX[ballIndex];
	}
	else if (ballRect[ballIndex].x + ballRect[ballIndex].w > brick.x + brick.w) {
		ballSpeedX[ballIndex] = -ballSpeedX[ballIndex];
	}
}

void showBalls(SDL_Renderer* renderer) {
	for (int i = 0; i < actualBalls; i++) {
		SDL_RenderCopy(renderer, ballTexture, NULL, &ballRect[i]);
	}
}

void incrementBallSpeed() {
	SDL_Point* speedMultiplies = new SDL_Point[actualBalls];
	for (int i = 0; i < actualBalls; i++) {
		speedMultiplies[i].x = ballSpeedX[i] / ballSpeedChangeX;
		speedMultiplies[i].y = ballSpeedY[i] / ballSPeedChangeY;
	}
	ballSpeedChangeX += firstSpeedChangeX;
	ballSPeedChangeY += firstSpeedChangeY;
	for (int i = 0; i < actualBalls; i++) {
		ballSpeedX[i] = speedMultiplies[i].x * ballSpeedChangeX;
		ballSpeedY[i] = speedMultiplies[i].y * ballSPeedChangeY;
	}
	delete[] speedMultiplies;
}

void decrementBallSpeed() {
	SDL_Point* speedMultiplies = new SDL_Point[actualBalls];
	for (int i = 0; i < actualBalls; i++) {
		speedMultiplies[i].x = ballSpeedX[i] / ballSpeedChangeX;
		speedMultiplies[i].y = ballSpeedY[i] / ballSPeedChangeY;
	}
	if (ballSpeedChangeX - firstSpeedChangeX > 0 && ballSPeedChangeY - firstSpeedChangeY > 0) {
		ballSpeedChangeX -= firstSpeedChangeX;
		ballSPeedChangeY -= firstSpeedChangeY;
	}
	for (int i = 0; i < actualBalls; i++) {
		ballSpeedX[i] = speedMultiplies[i].x * ballSpeedChangeX;
		ballSpeedY[i] = speedMultiplies[i].y * ballSPeedChangeY;
	}
	delete[] speedMultiplies;
}

//get the actual ball speed in termns of ballSpeedChangeX and ballSPeedChangeY
SDL_Point* getBallSpeedMultiplicators(SDL_Point* ballMultiplicator) {
	for (int i = 0; i < actualBalls; i++) {
		ballMultiplicator[i].x = ballSpeedX[i] / ballSpeedChangeX;
		ballMultiplicator[i].y = ballSpeedY[i] / ballSPeedChangeY;
	}
	return ballMultiplicator;
}

//set the paddleSpeed in a multiplicator of ballSPeedChange
void setMultiplicatorBallSpeed(SDL_Point* ballMultiplicator) {
	for (int i = 0; i < actualBalls; i++) {
		ballSpeedX[i] = ballMultiplicator[i].x * ballSpeedChangeX;
		ballSpeedY[i] = ballMultiplicator[i].y * ballSPeedChangeY;
	}
}

void restartBall() {
	actualBalls = 1;
	centerBall(0);
	initBallSpeed(0);
}