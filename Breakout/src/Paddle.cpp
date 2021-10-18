#include <SDL.h>
#include "GlobalVariables.h"
#include "Menu.h"

SDL_Rect paddle;
float paddleSpeed, maxSpeed, changeSpeed;

void initPaddle() {
	paddleSpeed = 0;
	maxSpeed = (SCREEN_WIDTH / 72) * 5 * 60.0f;
	changeSpeed = SCREEN_WIDTH * 25.0f / 288;

	paddle.w = boardWidth / 2;
	paddle.h = SCREEN_HEIGHT / 60;
	paddle.x = boardWidth / 2 - paddle.w / 2;
	paddle.y = int(SCREEN_HEIGHT * 0.9);
}

void centerPaddle() {
	paddle.x = boardWidth / 2 - paddle.w / 2;
}

void movePaddleRight() {
	if (paddleSpeed + changeSpeed < maxSpeed)
		paddleSpeed += changeSpeed;
	else
		paddleSpeed = 0;
}

void movePaddleLeft() {
	if (paddleSpeed - changeSpeed > -maxSpeed)
		paddleSpeed -= changeSpeed;
	else
		paddleSpeed = 0;
}

void updatePaddle(float deltaTime) {
	//move paddle
	if (paddleSpeed > 0) {
		if (paddle.x + paddle.w + paddleSpeed * deltaTime <= boardWidth) {
			paddle.x += (int)(paddleSpeed * deltaTime);
			//doww speed paddle
			if (paddleSpeed - changeSpeed / 2 > 0)
				paddleSpeed -= changeSpeed / 2;
			else
				paddleSpeed = 0;
		}
		else
			paddleSpeed = 0;
	}
	else if (paddleSpeed != 0){
		if (paddle.x + paddleSpeed * deltaTime > 0) {
			paddle.x += (int)(paddleSpeed * deltaTime);
			if (paddleSpeed + changeSpeed / 2 < 0)
				paddleSpeed += changeSpeed / 2;
			else
				paddleSpeed = 0;
		}
		else
			paddleSpeed = 0;
	}
}

//put the rect in the x and y percentage of the screen
void setWindowPaddleCoordinates(int percentageX) {
	paddle.x = (percentageX * SCREEN_WIDTH) / 100 - paddle.w / 2;
}

//get the coordinates in percentage of the screen of the rect(center)
void getActualPadddleCoordinates(int* x) {
	int centerRectX = paddle.x + paddle.w / 2;
	*x = 100 * centerRectX / SCREEN_WIDTH;
}

//get the actual speed paddle in termns of changeSpeed
int getMultiplicatorPaddleSpeed() {
	return (int)(paddleSpeed / changeSpeed);
}

//set the speed paddle in a multiplicator of changeSpeed
void setMultiplicatorPaddleSpeed(int paddleMultiplicator) {
	paddleSpeed = paddleMultiplicator * changeSpeed;
}

void incrementPaddleSpeed() {
	changeSpeed += SCREEN_WIDTH * 60 / 288;
}

void decrementPaddleSpeed() {
	paddleSpeed = 0;
	changeSpeed = 0;
}