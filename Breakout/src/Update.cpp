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
#include "Delete.h"

#include <iostream>

//rect is the ball or the bullet
bool checkRectCollisionBrick(SDL_Rect rect, int* position) {
	int posX, posY, pos;
	posX = rect.x / (brick.w + freeSizeX);
	posY = (rect.y - initialBrickY) / (brick.h + freeSizeY);
	pos = posX + posY * totalRectanglesX;

	if (brickLives[pos] > 0 && SDL_HasIntersection(&rect, &rectangles[pos])) {
		*position = pos;
		return true;
	}

	posX = (rect.x + rect.w) / (brick.w + freeSizeX);
	posY = (rect.y - initialBrickY) / (brick.h + freeSizeY);
	pos = posX + posY * totalRectanglesX;

	if (brickLives[pos] > 0 && SDL_HasIntersection(&rect, &rectangles[pos])) {
		*position = pos;
		return true;
	}

	posX = rect.x / (brick.w + freeSizeX);
	posY = (rect.y + rect.h - initialBrickY) / (brick.h + freeSizeY);
	pos = posX + posY * totalRectanglesX;

	if (brickLives[pos] > 0 && SDL_HasIntersection(&rect, &rectangles[pos])) {
		*position = pos;
		return true;
	}

	posX = (rect.x + rect.w) / (brick.w + freeSizeX);
	posY = (rect.y + rect.h - initialBrickY) / (brick.h + freeSizeY);
	pos = posX + posY * totalRectanglesX;

	if (brickLives[pos] > 0 && SDL_HasIntersection(&rect, &rectangles[pos])) {
		*position = pos;
		return true;
	}
	return false;
}

//rect is the ball or the bullet, ball indicates if the rect is a ball, and ball index is the ballRect index
bool checkRectCollisionBricks(SDL_Rect rect, SDL_Renderer* renderer, bool ball, int ballIndex) {
	//detect the collision of the ball with the bricks
	if (rect.y <= lastBrickY && rect.y + rect.h >= rectangles[0].y) {
		int pos = 0;
		if (checkRectCollisionBrick(rect, &pos)) {

			

			Mix_PlayChannel(1, sound, 0);
			score++;
			brickLives[pos]--;
			if (brickLives[pos] < 1) {
				checkBrickWithCapsule(pos);
				actualBricks--;
			}
				
			
			writeScore(renderer);
			if (actualBricks < 1) {
				level++;
				writeLevel(renderer);
				centerPaddle();
				restartBall();
				initBrickLives();
				restartCapsules();
				restartBullets();
				initBackgroundIndex();
				loadBackgroundImage(renderer);
				initCapsules(1 + rand() % totalRectangles, totalRectangles);
				timer = 0;
				serve = true;
				return true;
			}
			if (ball)
				changeBallMovementWithBrick(rectangles[pos], ballIndex);
			return true;
		}
	}
	return false;
}

void update(SDL_Renderer* renderer, int time) {
	for (int i = 0; i < actualBalls; i++) {
		int xI = ballRect[i].x + ballSpeedX[i];
		int xF = xI + ballRect[i].w;
		int yI = ballRect[i].y + ballSpeedY[i];
		int yF = yI + ballRect[i].h;
		if (xI < 0 || xF > boardWidth) {
			ballSpeedX[i] = -ballSpeedX[i];
		}
		else if (yI < 0) {
			ballSpeedY[i] = -ballSpeedY[i];
		}
		else if (yF > SCREEN_HEIGHT) {
			if (actualBalls < 2) {
				//the player loses a life
				ballSpeedY[i] = -ballSpeedY[i];
				lifes--;
				if (lifes == 0) {
					restart(renderer);
					return;
				}
				else {
					writeLife(renderer);
					centerPaddle();
					restartBall();
					serve = true;
					restartCapsules();
					restartBullets();
					return;
				}
			}
			else {
				//delete a ball
				deleteElementOfRectArray(ballRect, i, actualBalls);
				deleteElementOfIntArray(ballSpeedX, i, actualBalls);
				deleteElementOfIntArray(ballSpeedY, i, actualBalls);
				actualBalls--;
			}
		}
		
		if (SDL_HasIntersection(&ballRect[i], &paddle)) {
			Mix_PlayChannel(1, sound, 0);
			ballSpeedY[i] = -abs(ballSpeedY[i]);
			
			if (xF < paddle.x + paddle.w / 3) {
				if (ballSpeedX[i] - ballSpeedChangeX > -maxBallSpeed)
					ballSpeedX[i] -= ballSpeedChangeX;
			}
			else if (xF > paddle.x + 2 * paddle.w / 3)
				if (ballSpeedX[i] + ballSpeedChangeX < maxBallSpeed)
					ballSpeedX[i] += ballSpeedChangeX;
		}
		ballRect[i].x += ballSpeedX[i];
		ballRect[i].y += ballSpeedY[i];
		checkRectCollisionBricks(ballRect[i], renderer, true, i);
	}
	updatePaddle();
	updateCapsules(renderer);
	updateBullets(renderer, time);
}