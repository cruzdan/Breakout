// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Menu.h"
#include "Brick.h"
#include "Paddle.h"
#include "Ball.h"
#include "Update.h"
#include "Paddle.h"
#include "Capsule.h"
#include "Render.h"

void restart(SDL_Renderer* renderer) {
	paddleSpeed = 0;
	timer = 0;
	level = 1;
	score = 0;
	lifes = 3;
	generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", getScreenHeight() / 30, std::to_string(level), &textLevelPuntuation, renderer);
	generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", getScreenHeight() / 30, std::to_string(score), &textPuntuation, renderer);
	generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", getScreenHeight() / 30, std::to_string(lifes), &textLifeNumber, renderer);
	createRectangles();
	centerPaddle();
	restartBall();
	serve = true;
	restartCapsules();
	restartBullets();
	initBackgroundIndex();
	loadBackgroundImage(renderer);
	initCapsules(1 + rand() % totalRectangles, totalRectangles);
}