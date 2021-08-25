#include <SDL_mixer.h>
#include "Ball.h"
#include "Menu.h"
#include "Restart.h"
#include "Paddle.h"
#include "Music.h"
#include "Brick.h"
#include "GlobalVariables.h"
#include "Paddle.h"

int ballSpeedX;
int ballSpeedY;
int ballSpeedChange;
int maxBallSpeed;
int lastBrickY;

//set the ball speed when the size screen changes
void setNewBallSpeedWindow(int percentageX) {
	ballSpeedX = (percentageX * SCREEN_WIDTH) / 100;
}

//get the coordinates in percentage of the screen of the rect(center)
void getLastBallSpeed(int* speedX) {
	*speedX = 100 * ballSpeedX / SCREEN_WIDTH;
	if (*speedX == 0) {
		if (ballSpeedX > 0)
			*speedX = 1;
		else
			*speedX = -1;
	}
}

void initUpdateVariables() {
	ballSpeedX = SCREEN_WIDTH / 98;
	ballSpeedY = -SCREEN_HEIGHT / 72;
	ballSpeedChange = ballSpeedX / 2;
	maxBallSpeed = ballSpeedChange * 4;
	lastBrickY = SCREEN_HEIGHT / 2 - freeSizeY;
}

void update(SDL_Renderer* renderer) {
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
		}
		else {
			writeLife(renderer);
			centerPaddle();
			centerBall();
			serve = true;
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


	//detect the collision of the ball with the bricks
	if (ballRect.y <= lastBrickY) {
		int positionBrickX;
		int positionBrickY;
		int pos;

		positionBrickX = ballRect.x / (brick.w + freeSizeX);
		positionBrickY = ballRect.y / (brick.h + freeSizeY);
		pos = positionBrickX + positionBrickY * totalRectanglesX;

		SDL_Rect auxiliarBrick;
		auxiliarBrick = rectangles[pos];

		if (brickStatus[pos] && SDL_HasIntersection(&ballRect, &auxiliarBrick)) {
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
			}
			if (ballSpeedY > 0 && ballRect.y < auxiliarBrick.y) {
				ballSpeedY = -ballSpeedY;
			}
			else if (ballRect.y + ballRect.h > auxiliarBrick.y + auxiliarBrick.h) {
				ballSpeedY = -ballSpeedY;
			}
			else if (ballSpeedX > 0 && ballRect.x < auxiliarBrick.x) {
				ballSpeedX = -ballSpeedX;
			}
			else if (ballRect.x + ballRect.w > auxiliarBrick.x + auxiliarBrick.w) {
				ballSpeedX = -ballSpeedX;
			}
		}
	}
	updatePaddle();
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
		if(ballSpeedY - incrementY > 0)
			ballSpeedY -= incrementY;
	}
	else if(ballSpeedY + incrementY < 0)
		ballSpeedY += incrementY;
}