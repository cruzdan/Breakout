#include "Menu.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include "Update.h"
#include "GlobalVariables.h"
#include "Paddle.h"
#include "Capsule.h"

void restart(SDL_Renderer* renderer) {
	paddleSpeed = 0;
	timer = 0;
	initBrickLives();
	score = 0;
	writeScore(renderer);
	level = 1;
	writeLevel(renderer);
	lifes = 3;
	writeLife(renderer);
	centerPaddle();
	restartBall();
	serve = true;
	restartCapsules();
	restartBullets();
	initBackgroundIndex();
	loadBackgroundImage(renderer);
	initCapsules(1 + rand() % totalRectangles, totalRectangles);
}