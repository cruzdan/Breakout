#include <SDL_mixer.h>
#include "Ball.h"
#include "Menu.h"
#include "Restart.h"
#include "Paddle.h"
#include "Music.h"
#include "Brick.h"
#include "GlobalVariables.h"
#include "Paddle.h"
#include "Capsule.h"

//rect is the ball or the bullet
bool checkRectCollisionBrick(SDL_Rect rect, int* position) {
	int posX, posY, pos;
	posX = rect.x / (brick.w + freeSizeX);
	posY = (rect.y - initialBrickY) / (brick.h + freeSizeY);
	pos = posX + posY * totalRectanglesX;

	if (brickStatus[pos] && SDL_HasIntersection(&rect, &rectangles[pos])) {
		*position = pos;
		return true;
	}

	posX = (rect.x + rect.w) / (brick.w + freeSizeX);
	posY = (rect.y - initialBrickY) / (brick.h + freeSizeY);
	pos = posX + posY * totalRectanglesX;

	if (brickStatus[pos] && SDL_HasIntersection(&rect, &rectangles[pos])) {
		*position = pos;
		return true;
	}

	posX = rect.x / (brick.w + freeSizeX);
	posY = (rect.y + rect.h - initialBrickY) / (brick.h + freeSizeY);
	pos = posX + posY * totalRectanglesX;

	if (brickStatus[pos] && SDL_HasIntersection(&rect, &rectangles[pos])) {
		*position = pos;
		return true;
	}

	posX = (rect.x + rect.w) / (brick.w + freeSizeX);
	posY = (rect.y + rect.h - initialBrickY) / (brick.h + freeSizeY);
	pos = posX + posY * totalRectanglesX;

	if (brickStatus[pos] && SDL_HasIntersection(&rect, &rectangles[pos])) {
		*position = pos;
		return true;
	}
	return false;
}

//rect is the ball or the bullet
bool checkRectCollisionBricks(SDL_Rect rect, SDL_Renderer* renderer, bool ball) {
	//detect the collision of the ball with the bricks
	if (rect.y <= lastBrickY && rect.y + rect.h >= rectangles[0].y) {
		int pos = 0;
		if (checkRectCollisionBrick(rect, &pos)) {

			checkBrickWithCapsule(pos);

			Mix_PlayChannel(1, sound, 0);
			brickStatus[pos] = false;
			score++;
			writeScore(renderer);
			if (score % totalRectangles == 0) {
				level++;
				writeLevel(renderer);
				centerPaddle();
				centerBall();
				activateBricks();
				restartCapsules();
				restartBullets();
				initCapsules(1 + rand() % totalRectangles, totalRectangles);
				ballSpeedY = -abs(ballSpeedY);
				timer = 0;
				serve = true;
			}
			if (ball)
				changeBallMovementWithBrick(rect, rectangles[pos]);
			return true;
		}
	}
	return false;
}

void update(SDL_Renderer* renderer, int time) {
	int xI = ballRect.x + ballSpeedX;
	int xF = xI + ballRect.w;
	int yI = ballRect.y + ballSpeedY;
	int yF = yI + ballRect.h;
	if (xI < 0 || xF > boardWidth) {
		ballSpeedX = -ballSpeedX;
	}
	else if (yI < 0) {
		ballSpeedY = -ballSpeedY;
	}
	else if (yF > SCREEN_HEIGHT) {
		//the player loses a life
		ballSpeedY = -ballSpeedY;
		lifes--;
		if (lifes == 0) {
			restart(renderer);
			return;
		}
		else {
			writeLife(renderer);
			centerPaddle();
			centerBall();
			serve = true;
			restartCapsules();
			restartBullets();
			return;
		}

	}
	if (SDL_HasIntersection(&ballRect, &paddle)) {
		Mix_PlayChannel(1, sound, 0);
		ballSpeedY = -abs(ballSpeedY);
		if (xF < paddle.x + paddle.w / 3) {
			if (ballSpeedX - ballSpeedChange > -maxBallSpeed)
				ballSpeedX -= ballSpeedChange;
		}
		else if (xF > paddle.x + 2 * paddle.w / 3)
			if (ballSpeedX + ballSpeedChange < maxBallSpeed)
				ballSpeedX += ballSpeedChange;
	}
	ballRect.x += ballSpeedX;
	ballRect.y += ballSpeedY;

	checkRectCollisionBricks(ballRect, renderer, true);
	updatePaddle();
	updateCapsules();
	updateBullets(renderer, time);
}