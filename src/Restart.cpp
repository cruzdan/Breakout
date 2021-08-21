#include "Menu.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include "Update.h"
#include "GlobalVariables.h"
#include "Paddle.h"

void restart(SDL_Renderer* renderer) {
	paddleSpeed = 0;
	timer = 0;
	activateBricks();
	score = 0;
	writeScore(renderer);
	level = 1;
	writeLevel(renderer);
	lifes = 3;
	writeLife(renderer);
	centerPaddle();
	centerBall();
	serve = true;
	ballSpeedY = -SCREEN_WIDTH / 98;
}