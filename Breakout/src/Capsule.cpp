// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Capsule.h"
#include "Brick.h"
#include "Paddle.h"
#include "Update.h"
#include "Delete.h"
#include "Ball.h"
#include <SDL_ttf.h>
#include <string>
#include "Render.h"
#include "Menu.h"
#include "Brick.h"
#include <vector>
int actualShootSecond = 0;

int totalCapsules;//capsules in level
int* brickCapsuleIndex;
int* powerUpType;//0 -> shoot, 1 -> extra ball
int actualCapsules = 0;//capsules actives in game
std::vector<class Capsule*> capsules;
int capsuleWidth;
int capsuleHeight;
float capsuleSpeed;

//shoot
const int maxBullets = 6;
int actualBullets = 0;
std::vector<class Bullet*> bullets;
int bulletWidth;
int bulletHeight;
float bulletSpeed;
float shootTimer = 0;
float timerNextBullet = 0;
bool paddleShoot = false;

SDL_Texture* textShootTimer;
SDL_Rect textShootTimerRect;

void initRandom() {
	srand((int)time(NULL));
}

void initCapsuleVariables(SDL_Renderer* renderer) {
	capsuleWidth = getScreenWidth() / 36;
	capsuleHeight = getScreenHeight() / 144;
	capsuleSpeed = getScreenHeight() / 3.0f;
	bulletWidth = getScreenWidth() / 72;
	bulletHeight = getScreenHeight() / 72;
	bulletSpeed = getScreenHeight() * 60.0f / 72;
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

	brickCapsuleIndex = NULL;
	powerUpType = NULL;

	brickCapsuleIndex = new int[totalCapsules];
	powerUpType = new int[totalCapsules];
	bullets.clear();
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
		Capsule cap;
		cap.setX(bricks.at(element)->getX() + bricks.at(element)->getW() / 2 - capsuleWidth / 2);
		cap.setY(bricks.at(element)->getY() + bricks.at(element)->getH() / 2 - capsuleHeight / 2);
		cap.setWidth(capsuleWidth);
		cap.setHeight(capsuleHeight);
		cap.setType(powerUpType[capsuleIndex]);

		capsules.push_back(new Capsule(cap));

		actualCapsules++;
		brickCapsuleIndex = deleteElementOfIntArray(brickCapsuleIndex, capsuleIndex, totalCapsules);
		powerUpType = deleteElementOfIntArray(powerUpType, capsuleIndex, totalCapsules);
	}
}

SDL_Point* getActualCapsulePercentages(SDL_Point* percentages) {
	for (int i = 0; i < actualCapsules; i++) {
		int centerX = (int)(capsules.at(i)->getX() + capsules.at(i)->getWidth() / 2);
		int centerY = (int)(capsules.at(i)->getY() + capsules.at(i)->getHeight() / 2);
		percentages[i].x = (centerX * 100) / getScreenWidth();
		percentages[i].y = (centerY * 100) / getScreenHeight();
	}
	return percentages;
}

SDL_Point* getActualBulletPercentages(SDL_Point* percentages) {
	for (int i = 0; i < actualBullets; i++) {
		int centerX = (int)(bullets.at(i)->getX() + bullets.at(i)->getW() / 2);
		int centerY = (int)(bullets.at(i)->getY() + bullets.at(i)->getH() / 2);
		percentages[i].x = (centerX * 100) / getScreenWidth();
		percentages[i].y = (centerY * 100) / getScreenHeight();
	}
	return percentages;
}

void resizeCapsules() {
	for (int i = 0; i < actualCapsules; i++) {
		capsules.at(i)->setWidth(capsuleWidth);
		capsules.at(i)->setHeight(capsuleHeight);
	}
}

void resizeBullets() {
	for (int i = 0; i < actualBullets; i++) {
		bullets.at(i)->setW(bulletWidth);
		bullets.at(i)->setH(bulletHeight);
	}
}

void activateShoot(float seconds) {
	paddleShoot = true;
	shootTimer += seconds;
}

void takeCapsule(int powerType, SDL_Renderer* renderer, float deltaTime) {
	switch (powerType) {
	case 0:
		activateShoot(3.0f);
		break;
	case 1:
		addNewBall();
		break;
	}
}

void updateCapsules(SDL_Renderer* renderer, float deltaTime) {
	for (int i = actualCapsules - 1; i >= 0; i--) {
		//move
		capsules.at(i)->setY(capsules.at(i)->getY() + capsuleSpeed * deltaTime);

		//check collision with paddle
		SDL_Rect rect;
		rect.x = (int)capsules.at(i)->getX();
		rect.y = (int)capsules.at(i)->getY();
		rect.w = capsules.at(i)->getWidth();
		rect.h = capsules.at(i)->getHeight();
		if (capsules.at(i)->getY() + capsules.at(i)->getHeight() >= paddle.y && SDL_HasIntersection(&rect, &paddle)) {
			//has intersection with paddle
			takeCapsule(capsules.at(i)->getType(), renderer, deltaTime);
			deleteCapsuleElement(&capsules, capsules.at(i));
			actualCapsules--;
			continue;
		}

		//delete
		if (capsules.at(i)->getY() > getScreenHeight()) {
			deleteCapsuleElement(&capsules, capsules.at(i));
			actualCapsules--;
		}
	}
}

void showCapsules(SDL_Renderer* renderer) {
	for (int i = 0; i < actualCapsules; i++) {
		switch (capsules.at(i)->getType()) {
		case 0:
			SDL_SetRenderDrawColor(renderer, 36, 194, 48, 0);
			break;
		case 1:
			SDL_SetRenderDrawColor(renderer, 3, 90, 176, 0);
			break;
		}
		SDL_Rect rect;
		rect.x = (int)capsules.at(i)->getX();
		rect.y = (int)capsules.at(i)->getY();
		rect.w = capsules.at(i)->getWidth();
		rect.h = capsules.at(i)->getHeight();
		SDL_RenderFillRect(renderer, &rect);
	}
}

void restartCapsules() {
	capsules.clear();
	actualCapsules = 0;
}

void restartBullets() {
	bullets.clear();
	actualBullets = 0;
	shootTimer = 0;
	timerNextBullet = 0;
	paddleShoot = false;
}

void closeCapsule() {
	delete[] brickCapsuleIndex;
	delete[] powerUpType;
	SDL_DestroyTexture(textShootTimer);
}

void updateBullets(SDL_Renderer* renderer, float time) {
	for (int i = actualBullets - 1; i >= 0; i--) {
		bullets.at(i)->setY(bullets.at(i)->getY() - (bulletSpeed * time));

		//check collision with bricks
		SDL_Rect rect;
		rect.x = (int)bullets.at(i)->getX();
		rect.y = (int)bullets.at(i)->getY();
		rect.w = bullets.at(i)->getW();
		rect.h = bullets.at(i)->getH();
		if (checkRectCollisionBricks(rect, renderer, false, -1, time)) {
			if (actualBullets <= 0)
				return;
			deleteBulletElement(&bullets, bullets.at(i));
			actualBullets--;
			continue;
		}
		//delete
		if (bullets.at(i)->getY() + bullets.at(i)->getH() < 0) {
			deleteBulletElement(&bullets, bullets.at(i));
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
			if (actualShootSecond != (int)shootTimer) {
				actualShootSecond = (int)shootTimer;
				changeTextShootActiveText(actualShootSecond, renderer);
			}
		}
		if (timerNextBullet > 0)
			timerNextBullet -= time;
	}
}

void showBullets(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 48, 3, 176, 0);
	for (int i = 0; i < actualBullets; i++) {
		SDL_Rect rect;
		rect.x = (int)bullets.at(i)->getX();
		rect.y = (int)bullets.at(i)->getY();
		rect.w = bullets.at(i)->getW();
		rect.h = bullets.at(i)->getH();
		SDL_RenderFillRect(renderer, &rect);
	}
}

void showTextScore(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, textShootTimer, NULL, &textShootTimerRect);
}

void shoot() {
	if (paddleShoot && timerNextBullet <= 0 && actualBullets < maxBullets - 1) {
		timerNextBullet = 0.3f;
		//add 2 bullets on the paddle
		Bullet bullet;
		bullet.setX((float)(paddle.x + paddle.w / 3 - bulletWidth / 2));
		bullet.setY((float)(paddle.y - bulletHeight));
		bullet.setW(bulletWidth);
		bullet.setH(bulletHeight);
		bullets.push_back(new Bullet(bullet));
		actualBullets++;
		bullet.setX((float)(paddle.x + paddle.w / 3 + paddle.w / 3 - bulletWidth / 2));
		bullet.setY((float)(paddle.y - bulletHeight));
		bullets.push_back(new Bullet(bullet));
		actualBullets++;
	}
}

void changeTextShootActiveText(int seconds, SDL_Renderer* renderer) {
	std::string a = "Shoot: " + std::to_string(seconds) + " ";
	generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", getScreenHeight() / 30, a, &textShootTimer, renderer);
}

void deleteCapsuleElement(std::vector<class Capsule*>* caps, class Capsule* cap) {
	auto index = std::find(caps->begin(), caps->end(), cap);
	if (index != caps->end())
		caps->erase(index);
}

void deleteBulletElement(std::vector<class Bullet*>* bulls, class Bullet* bull) {
	auto index = std::find(bulls->begin(), bulls->end(), bull);
	if (index != bulls->end())
		bulls->erase(index);
}