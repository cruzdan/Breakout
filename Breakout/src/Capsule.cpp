#include "Capsule.h"
#include "Brick.h"
#include "GlobalVariables.h"
#include "Paddle.h"
#include "iostream"
#include "Update.h"
#include "Delete.h"
#include "Ball.h"

#include <SDL_ttf.h>
#include <string>

int totalCapsules;//max capsules in level
int *brickCapsuleIndex;
int *powerUpType;//0 -> shoot, 1 -> extra ball
int actualCapsules = 0;//capsules actives in game
Capsule *capsules;
int capsuleWidth;
int capsuleHeight;
int capsuleSpeed;

//shoot
const int maxBullets = 6;
int actualBullets = 0;
SDL_Rect* bullets;
int bulletWidth;
int bulletHeight;
int bulletSpeed;
int shootTimer = 0;
int timerNextBullet = 0;
bool paddleShoot = false;

SDL_Texture* textShootTimer;
SDL_Rect textShootTimerRect;

void initRandom() {
	srand((int)time(NULL));
}

void initCapsuleVariables(SDL_Renderer* renderer) {
	capsuleWidth = rectangles[0].w / 2;
	capsuleHeight = rectangles[0].h / 2;
	capsuleSpeed = SCREEN_HEIGHT / 240;
	bulletWidth = SCREEN_WIDTH / 72;
	bulletHeight = SCREEN_HEIGHT / 72;
	bulletSpeed = SCREEN_HEIGHT / 72;

	changeTextShootActiveText(0, renderer);
}

//check if the element exists in the array, return the index of the first finding or -1 if the element does not exists in total elements of the array
int elementExistsIn(int* array, int element, int total) {
	for (int i = 0; i < total; i++) {
		if (array[i] == element)
			return i;
	}
	return -1;
}

//create "total" capsules (index of bricks) in a max range with a powerUpType
void initCapsules(int total, int max) {
	if (total > totalRectangles) {
		totalCapsules = totalRectangles;
		max = totalCapsules;
	}
	else {
		totalCapsules = total;
	}
	brickCapsuleIndex = new int[totalCapsules];
	powerUpType = new int[totalCapsules];
	capsules = new Capsule[totalCapsules];
	bullets = new SDL_Rect[maxBullets];
	for (int i = 0; i < totalCapsules; i++) {
		int random;
		int elementInArray;
		do {
			random = rand() % max;
			elementInArray = elementExistsIn(brickCapsuleIndex, random, i);
		} while (elementInArray > -1);
		brickCapsuleIndex[i] = random;
		powerUpType[i] = rand() % 2;
	}
}

//delete the element in the index of the array and rearrange the array.Max is the number of elements of the array
Capsule* deleteElementOfCapsuleArray(Capsule* array, int index, int max) {
	for (int i = index; i < max - 1; i++) {
		array[i] = array[i + 1];
	}
	return array;
}

//check if the element(index of brick) have a capsule and if it has, rearrange the arrays of brickCapsuleIndex and powerUpType
void checkBrickWithCapsule(int element) {
	int capsuleIndex = elementExistsIn(brickCapsuleIndex, element, totalCapsules);
	if (capsuleIndex > -1) {
		capsules[actualCapsules].rect = { rectangles[element].x + rectangles[element].w / 2 - capsuleWidth / 2,
			rectangles[element].y + rectangles[element].h / 2 - capsuleHeight / 2,capsuleWidth, capsuleHeight };
		capsules[actualCapsules].type = powerUpType[capsuleIndex];
		actualCapsules++;
		brickCapsuleIndex = deleteElementOfIntArray(brickCapsuleIndex, capsuleIndex, totalCapsules);
		powerUpType = deleteElementOfIntArray(powerUpType, capsuleIndex, totalCapsules);
	}
}

SDL_Point* getActualCapsulePercentages(SDL_Point* percentages) {
	for (int i = 0; i < actualCapsules; i++) {
		int centerX = capsules[i].rect.x + capsules[i].rect.w / 2;
		int centerY = capsules[i].rect.y + capsules[i].rect.h / 2;
		percentages[i].x = (centerX * 100) / SCREEN_WIDTH;
		percentages[i].y = (centerY * 100) / SCREEN_HEIGHT;
	}
	return percentages;
}

SDL_Point* getActualBulletPercentages(SDL_Point* percentages) {
	for (int i = 0; i < actualBullets; i++) {
		int centerX = bullets[i].x + bullets[i].w / 2;
		int centerY = bullets[i].y + bullets[i].h / 2;
		percentages[i].x = (centerX * 100) / SCREEN_WIDTH;
		percentages[i].y = (centerY * 100) / SCREEN_HEIGHT;
	}
	return percentages;
}

void resizeCapsules() {
	for (int i = 0; i < actualCapsules; i++) {
		capsules[i].rect.w = capsuleWidth;
		capsules[i].rect.h = capsuleHeight;
	}
}

void resizeBullets() {
	for (int i = 0; i < actualBullets; i++) {
		bullets[i].w = bulletWidth;
		bullets[i].h = bulletHeight;
	}
}

void activateShoot(int seconds) {
	paddleShoot = true;
	shootTimer += seconds;
}

void takeCapsule(int powerType, SDL_Renderer* renderer) {
	switch (powerType) {
	case 0:
		activateShoot(3000);
		changeTextShootActiveText(shootTimer / 1000, renderer);
		break;
	case 1:
		adNewBall();
		break;
	}
}

void updateCapsules(SDL_Renderer* renderer) {
	for (int i = actualCapsules - 1; i >= 0; i--) {
		//move
		capsules[i].rect.y += capsuleSpeed;
		
		//check collision with paddle
		if (capsules[i].rect.y + capsules[i].rect.h >= paddle.y && SDL_HasIntersection(&capsules[i].rect, &paddle)) {
			//has intersection with paddle
			takeCapsule(capsules[i].type, renderer);
			deleteElementOfCapsuleArray(capsules, i, actualCapsules);
			actualCapsules--;
			continue;
		}

		//delete
		if (capsules[i].rect.y > SCREEN_HEIGHT) {
			deleteElementOfCapsuleArray(capsules, i, actualCapsules);
			actualCapsules--;
		}
	}
}

void showCapsules(SDL_Renderer* renderer) {
	for (int i = 0; i < actualCapsules; i++) {
		switch (capsules[i].type) {
		case 0:
			SDL_SetRenderDrawColor(renderer, 36, 194, 48, 0);
			break;
		case 1:
			SDL_SetRenderDrawColor(renderer, 3, 90, 176, 0);
			break;
		}
		SDL_RenderFillRect(renderer, &capsules[i].rect);
	}
}

void restartCapsules() {
	actualCapsules = 0;
}

void restartBullets() {
	actualBullets = 0;
	shootTimer = 0;
	timerNextBullet = 0;
	paddleShoot = false;
}

void closeCapsule() {
	delete[] brickCapsuleIndex;
	delete[] powerUpType;
	delete[] capsules;
	delete[] bullets;
	SDL_DestroyTexture(textShootTimer);
}

void updateBullets(SDL_Renderer* renderer, int time) {
	for (int i = actualBullets - 1; i >= 0; i--) {
		bullets[i].y -= bulletSpeed;

		//check collision with bricks
		if (checkRectCollisionBricks(bullets[i], renderer, false, -1)) {
			if (actualBullets <= 0)
				return;
			bullets = deleteElementOfRectArray(bullets, i, actualBullets);
			actualBullets--;
			continue;
		}

		//delete
		if (bullets[i].y + bullets[i].h < 0) {
			bullets = deleteElementOfRectArray(bullets, i, actualBullets);
			actualBullets--;
		}
	}
	if (paddleShoot) {
		if (shootTimer < 0) {
			paddleShoot = false;
			timerNextBullet = 0;
		}
		else {
			shootTimer -= time;
			changeTextShootActiveText(shootTimer / 1000, renderer);
		}
		if (timerNextBullet > 0)
			timerNextBullet -= time;
	}
}

void showBullets(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 48, 3, 176, 0);
	for (int i = 0; i < actualBullets; i++) {
		SDL_RenderFillRect(renderer, &bullets[i]);
	}
}

void showTextScore(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, textShootTimer, NULL, &textShootTimerRect);
}

void shoot() {
	if (paddleShoot && timerNextBullet <= 0 && actualBullets < maxBullets - 1) {
		
		timerNextBullet = 300;

		//add 2 bullets on the paddle
		bullets[actualBullets] = { 
			paddle.x + paddle.w / 3 - bulletWidth / 2,
			paddle.y - bulletHeight,
			bulletWidth,
			bulletHeight
		};
		actualBullets++;
		bullets[actualBullets] = {
			paddle.x + paddle.w / 3 + paddle.w / 3 - bulletWidth / 2,
			paddle.y - bulletHeight,
			bulletWidth,
			bulletHeight
		};
		actualBullets++;
	}
}

void changeTextShootActiveText(int seconds, SDL_Renderer* renderer) {
	TTF_Font* font = TTF_OpenFont("fonts/Oswald-BoldItalic.ttf", SCREEN_HEIGHT / 30);
	SDL_Surface* textSurface;
	SDL_Color color = { 255,255,255 };
	std::string a = "Shoot: " + std::to_string(seconds) + " ";
	textSurface = TTF_RenderText_Solid(font,a.c_str(), color);
	textShootTimer = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
}