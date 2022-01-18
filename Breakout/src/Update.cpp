// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL_mixer.h>
#include "Ball.h"
#include "Menu.h"
#include "Restart.h"
#include "Paddle.h"
#include "Music.h"
#include "Brick.h"
#include "Paddle.h"
#include "Capsule.h"
#include "Render.h"

//rect is the ball or the bullet
bool checkRectCollisionBrick(SDL_Rect rect, int* position) {
	int posX, posY, pos;
	posX = rect.x / (bricks.at(0)->getW() + freeSizeX);
	posY = (rect.y - initialBrickY) / (bricks.at(0)->getH() + freeSizeY);
	pos = posX + posY * totalRectanglesX;
	SDL_Rect brect;
	brect.w = bricks.at(0)->getW();
	brect.h = bricks.at(0)->getH();
	if (pos >= 0 && pos < totalRectangles) {
		brect.x = (int)bricks.at(pos)->getX();
		brect.y = (int)bricks.at(pos)->getY();
		if (bricks.at(pos)->getLifes() > 0 && SDL_HasIntersection(&rect, &brect)) {
			*position = pos;
			return true;
		}
	}

	posX = (rect.x + rect.w) / (brect.w + freeSizeX);
	posY = (rect.y - initialBrickY) / (brect.h + freeSizeY);
	pos = posX + posY * totalRectanglesX;
	if (pos >= 0 && pos < totalRectangles) {
		brect.x = (int)bricks.at(pos)->getX();
		brect.y = (int)bricks.at(pos)->getY();
		if (bricks.at(pos)->getLifes() > 0 && SDL_HasIntersection(&rect, &brect)) {
			*position = pos;
			return true;
		}
	}

	posX = rect.x / (brect.w + freeSizeX);
	posY = (rect.y + rect.h - initialBrickY) / (brect.h + freeSizeY);
	pos = posX + posY * totalRectanglesX;
	if (pos >= 0 && pos < totalRectangles) {
		brect.x = (int)bricks.at(pos)->getX();
		brect.y = (int)bricks.at(pos)->getY();
		if (bricks.at(pos)->getLifes() > 0 && SDL_HasIntersection(&rect, &brect)) {
			*position = pos;
			return true;
		}
	}

	posX = (rect.x + rect.w) / (brect.w + freeSizeX);
	posY = (rect.y + rect.h - initialBrickY) / (brect.h + freeSizeY);
	pos = posX + posY * totalRectanglesX;
	if (pos >= 0 && pos < totalRectangles) {
		brect.x = (int)bricks.at(pos)->getX();
		brect.y = (int)bricks.at(pos)->getY();
		if (bricks.at(pos)->getLifes() > 0 && SDL_HasIntersection(&rect, &brect)) {
			*position = pos;
			return true;
		}
	}
	return false;
}

void nextLevel(SDL_Renderer* renderer) {
	level++;
	generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", getScreenHeight() / 30, std::to_string(level), &textLevelPuntuation, renderer);
	centerPaddle();
	restartBall();
	createRectangles();
	restartCapsules();
	restartBullets();
	initBackgroundIndex();
	loadBackgroundImage(renderer);
	initCapsules(1 + rand() % totalRectangles, totalRectangles);
	timer = 0;
	serve = true;
}

//rect is the ball or the bullet, ball indicates if the rect is of a ball
bool checkRectCollisionBricks(SDL_Rect rect, SDL_Renderer* renderer, bool ball, int ballIndex, float time) {
	//detect the collision of the ball with the bricks
	if (rect.y <= lastBrickY && rect.y + rect.h >= bricks.at(0)->getY()) {
		int pos = 0;
		if (checkRectCollisionBrick(rect, &pos)) {
			Mix_PlayChannel(1, sound, 0);
			score++;
			generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", getScreenHeight() / 30, std::to_string(score), &textPuntuation, renderer);
			bricks.at(pos)->setLifes(bricks.at(pos)->getLifes() - 1);
			if (bricks.at(pos)->getLifes() < 1) {
				checkBrickWithCapsule(pos);
				actualBricks--;
			}
			if (actualBricks < 1) {
				nextLevel(renderer);
				return true;
			}
			if (ball) {
				SDL_Rect brect;
				brect.x = (int)bricks.at(pos)->getX();
				brect.y = (int)bricks.at(pos)->getY();
				brect.w = bricks.at(pos)->getW();
				brect.h = bricks.at(pos)->getH();
				changeBallMovementWithBrick(brect, balls.at(ballIndex), time);
			}
			return true;
		}
	}
	return false;
}

void update(SDL_Renderer* renderer, float time) {
	int i = 0;
	for (auto ball : balls) {
		float xI = ball->getX() + ball->getSpeedX() * time;
		float xF = xI + ball->getWidth();
		float yI = ball->getY() + ball->getSpeedY() * time;
		float yF = yI + ball->getHeight();
		if (xI < 0 || xF > boardWidth) {
			ball->setSpeedX(-ball->getSpeedX());
			xI = ball->getX() + ball->getSpeedX() * time;
		}
		else if (yI < 0) {
			ball->setSpeedY(-ball->getSpeedY());
			yI = ball->getY() + ball->getSpeedY() * time;
		}
		else if (yF > getScreenHeight()) {
			if (actualBalls < 2) {
				//the player loses a life
				lifes--;
				if (lifes == 0) {
					restart(renderer);
					return;
				}
				else {
					centerPaddle();
					restartBall();
					serve = true;
					restartCapsules();
					restartBullets();
					generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", getScreenHeight() / 30, std::to_string(lifes), &textLifeNumber, renderer);
					return;
				}
			}
			else {
				//delete a ball
				deleteBallElement(&balls, ball);
				actualBalls--;
				break;
			}
		}
		SDL_Rect rect;
		rect.x = (int)ball->getX();
		rect.y = (int)ball->getY();
		rect.w = ball->getWidth();
		rect.h = ball->getHeight();
		if (SDL_HasIntersection(&rect, &paddle)) {
			Mix_PlayChannel(1, sound, 0);
			ball->setSpeedY(-abs(ball->getSpeedY()));
			if (xF < paddle.x + paddle.w / 3) {
				if (ball->getSpeedX() - ballSpeedChangeX / 2 > -maxBallSpeed)
					ball->setSpeedX(ball->getSpeedX() - ballSpeedChangeX / 2);
			}
			else if (xF > paddle.x + 2 * paddle.w / 3) {
				if (ball->getSpeedX() + ballSpeedChangeX / 2 < maxBallSpeed)
					ball->setSpeedX(ball->getSpeedX() + ballSpeedChangeX / 2);
			}
		}
		ball->setX(xI);
		ball->setY(yI);
		checkRectCollisionBricks(rect, renderer, true, i, time);
		if (actualBalls < 2)
			break;
		i++;
	}
	updatePaddle(time);
	updateCapsules(renderer, time);
	updateBullets(renderer, time);
}