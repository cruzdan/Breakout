// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL.h>
#include <SDL_image.h>
#include "Menu.h"
#include "Paddle.h"
#include <vector>
#include "Ball.h"

const int maxBalls = 8;
std::vector<class Ball*> balls;
int actualBalls = 1;
SDL_Texture* ballTexture;
float ballSpeedChangeX;
float ballSPeedChangeY;
float maxBallSpeed;
float firstSpeedChangeX;
float firstSpeedChangeY;

void closeTextureBall() {
	SDL_DestroyTexture(ballTexture);
}

void initBallSpeed(Ball* ball) {
	if (rand() % 2 < 1)
		ball->setSpeedX(ballSpeedChangeX + ballSpeedChangeX);
	else
		ball->setSpeedX(-(ballSpeedChangeX + ballSpeedChangeX));
	ball->setSpeedY(-(ballSPeedChangeY + ballSPeedChangeY));
}

void addNewBall() {
	if (actualBalls < maxBalls) {
		int ballWidth = boardWidth / 40;
		int ballHeight = getScreenHeight() / 30;
		class Ball ball;
		ball.setX((float)(paddle.x + paddle.w / 2 - ballWidth / 2));
		ball.setY((float)(paddle.y - ballHeight));
		ball.setWidth(ballWidth);
		ball.setHeight(ballHeight);
		balls.push_back(new Ball(ball));
		initBallSpeed(balls.at(actualBalls));
		actualBalls++;
	}
}

void initBall() {
	balls.clear();
	ballSpeedChangeX = (getScreenWidth() * 50.0f / 256);
	ballSPeedChangeY = (getScreenHeight() * 50.0f / 144);
	firstSpeedChangeX = ballSpeedChangeX / 2.0f;
	firstSpeedChangeY = ballSPeedChangeY / 2.0f;
	int ballWidth = boardWidth / 40;
	int ballHeight = getScreenHeight() / 30;
	Ball ball;
	ball.setX((float)(boardWidth / 2 - ballWidth / 2));
	ball.setY((float)(paddle.y - ballHeight));
	ball.setWidth(ballWidth);
	ball.setHeight(ballHeight);
	balls.push_back(new Ball(ball));
	initBallSpeed(balls.at(0));
	maxBallSpeed = ballSpeedChangeX * 5.0f;
}

SDL_Point* getActualBallPercentages(SDL_Point* percentages) {
	int i = 0;
	for (auto ball : balls) {
		int centerX = (int)(ball->getX() + ball->getWidth() / 2);
		int centerY = (int)(ball->getY() + ball->getHeight() / 2);
		percentages[i].x = (centerX * 100) / getScreenWidth();
		percentages[i].y = (centerY * 100) / getScreenHeight();
		i++;
	}
	return percentages;
}

void reziseBalls() {
	for (auto ball : balls) {
		ball->setWidth(boardWidth / 40);
		ball->setHeight(getScreenHeight() / 30);
	}
}

void changeBallMovementWithBrick(SDL_Rect brick, Ball* ball, float time) {
	if (ball->getSpeedY() > 0 && ball->getY() < brick.y) {
		ball->setSpeedY(-ball->getSpeedY());
		ball->setY(ball->getY() + ball->getSpeedY() * time);
	}
	else if (ball->getSpeedY() <= 0 && ball->getY() + ball->getHeight() > brick.y + brick.h) {
		ball->setSpeedY(-ball->getSpeedY());
		ball->setY(ball->getY() + ball->getSpeedY() * time);
	}
	if (ball->getSpeedX() > 0 && ball->getX() < brick.x) {
		ball->setSpeedX(-ball->getSpeedX());
		ball->setX(ball->getX() + ball->getSpeedX() * time);
	}
	else if (ball->getSpeedX() <= 0 && ball->getX() + ball->getWidth() > brick.x + brick.w) {
		ball->setSpeedX(-ball->getSpeedX());
		ball->setX(ball->getX() + ball->getSpeedX() * time);
	}
}

void showBalls(SDL_Renderer* renderer) {
	for (auto ball : balls) {
		SDL_Rect rect;
		rect.x = (int)ball->getX();
		rect.y = (int)ball->getY();
		rect.w = ball->getWidth();
		rect.h = ball->getHeight();
		SDL_RenderCopy(renderer, ballTexture, NULL, &rect);
	}
}

void incrementBallSpeed() {
	SDL_Point* speedMultiplies = new SDL_Point[actualBalls];
	for (int i = 0; i < actualBalls; i++) {
		auto ball = balls.at(i);
		speedMultiplies[i].x = (int)(ball->getSpeedX() / ballSpeedChangeX);
		speedMultiplies[i].y = (int)(ball->getSpeedY() / ballSPeedChangeY);
	}
	ballSpeedChangeX += firstSpeedChangeX;
	ballSPeedChangeY += firstSpeedChangeY;
	for (int i = 0; i < actualBalls; i++) {
		auto ball = balls.at(i);
		ball->setSpeedX(speedMultiplies[i].x * ballSpeedChangeX);
		ball->setSpeedY(speedMultiplies[i].y * ballSPeedChangeY);
	}
	delete[] speedMultiplies;
}

void decrementBallSpeed() {
	SDL_Point* speedMultiplies = new SDL_Point[actualBalls];
	for (int i = 0; i < actualBalls; i++) {
		auto ball = balls.at(i);
		speedMultiplies[i].x = (int)(ball->getSpeedX() / ballSpeedChangeX);
		speedMultiplies[i].y = (int)(ball->getSpeedY() / ballSPeedChangeY);
	}
	if (ballSpeedChangeX - firstSpeedChangeX > 0 && ballSPeedChangeY - firstSpeedChangeY > 0) {
		ballSpeedChangeX -= firstSpeedChangeX;
		ballSPeedChangeY -= firstSpeedChangeY;
	}
	for (int i = 0; i < actualBalls; i++) {
		auto ball = balls.at(i);
		ball->setSpeedX(speedMultiplies[i].x * ballSpeedChangeX);
		ball->setSpeedY(speedMultiplies[i].y * ballSPeedChangeY);
	}
	delete[] speedMultiplies;
}

//get the actual ball speed in termns of ballSpeedChange
SDL_Point* getBallSpeedMultiplicators(SDL_Point* ballMultiplicator) {
	int i = 0;
	for (auto ball : balls) {
		ballMultiplicator[i].x = (int)(ball->getSpeedX() / ballSpeedChangeX);
		ballMultiplicator[i].y = (int)(ball->getSpeedY() / ballSPeedChangeY);
		i++;
	}
	return ballMultiplicator;
}

//get the actual ball speed in termns of Width and height
float* getBallSpeedMultiplicatorsX(float* ballMultiplicatorX) {
	int i = 0;
	for (auto ball : balls) {
		ballMultiplicatorX[i] = ball->getSpeedX() / (float)getScreenWidth();
		i++;
	}
	return ballMultiplicatorX;
}

float* getBallSpeedMultiplicatorsY(float* ballMultiplicatorY) {
	int i = 0;
	for (auto ball : balls) {
		ballMultiplicatorY[i] = ball->getSpeedY() / (float)getScreenHeight();
		i++;
	}
	return ballMultiplicatorY;
}

//set the paddleSpeed in a multiplicator of width and height
void setMultiplicatorBallSpeed(float* ballMultiplicatorX, float* ballMultiplicatorY) {
	int i = 0;
	for (auto ball : balls) {
		ball->setSpeedX(ballMultiplicatorX[i] * getScreenWidth());
		ball->setSpeedY(ballMultiplicatorY[i] * getScreenHeight());
		i++;
	}
}

//set the paddleSpeed in a multiplicator of ballSPeedChange
void setMultiplicatorBallSpeed(SDL_Point* ballMultiplicator) {
	int i = 0;
	for (auto ball : balls) {
		ball->setSpeedX(ballMultiplicator[i].x * ballSpeedChangeX);
		ball->setSpeedY(ballMultiplicator[i].y * ballSPeedChangeY);
		i++;
	}
}

void restartBall() {
	balls.clear();
	int ballWidth = boardWidth / 40;
	int ballHeight = getScreenHeight() / 30;
	Ball ball;
	ball.setX((float)(boardWidth / 2 - ballWidth / 2));
	ball.setY((float)(paddle.y - ballHeight));
	ball.setWidth(ballWidth);
	ball.setHeight(ballHeight);
	balls.push_back(new Ball(ball));
	initBallSpeed(balls.at(0));
	actualBalls = 1;
}

void deleteBallElement(std::vector<class Ball*>* balls, class Ball* ball) {
	auto index = std::find(balls->begin(), balls->end(), ball);
	if (index != balls->end())
		balls->erase(index);
}