#include <SDL.h>
#include "GlobalVariables.h"
#include "Menu.h"
SDL_Rect paddle;
int paddleSpeed, maxSpeed, changeSpeed;

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

void updatePaddle() {
	//move paddle
	if (paddleSpeed > 0) {
		if (paddle.x + paddle.w + paddleSpeed <= boardWidth) {
			paddle.x += paddleSpeed;
			//doww speed
			paddleSpeed -= changeSpeed / 2;
		}
		else
			paddleSpeed = 0;
	}
	else if (paddleSpeed != 0){
		if (paddle.x + paddleSpeed > 0) {
			paddle.x += paddleSpeed;
			paddleSpeed += changeSpeed / 2;
		}
		else
			paddleSpeed = 0;
	}
}

void initPaddle() {
	paddleSpeed = 0;
	maxSpeed = (SCREEN_WIDTH / 72) * 5;
	changeSpeed = SCREEN_WIDTH / 288;

	paddle.w = boardWidth / 4;
	paddle.h = SCREEN_HEIGHT / 60;
	paddle.x = boardWidth / 2 - paddle.w / 2;
	paddle.y = int(SCREEN_HEIGHT * 0.9);
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

//get the speed in percentage of the screen width
void getActualPaddleSpeed(int* speed) {
	*speed = paddleSpeed * 100 / SCREEN_WIDTH;
}

//set the paddle speed with the width percentage of the window
void setPaddleSpeed(int percentageX) {
	paddleSpeed = (percentageX / 100) * SCREEN_WIDTH;
}

void incrementPaddleSpeed() {
	changeSpeed += SCREEN_WIDTH / 288;
}

void decrementPaddleSpeed() {
	if(changeSpeed - SCREEN_WIDTH / 288 >= 0)
		changeSpeed -= SCREEN_WIDTH / 288;
}