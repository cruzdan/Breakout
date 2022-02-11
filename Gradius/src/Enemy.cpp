// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Enemy.h"

Enemy::Enemy():
	x(0),
	y(0),
	w(0),
	h(0),
	firstX(0),
	firstY(0),
	endX(0),
	endY(0),
	dead(false),
	score(0),
	lifes(0),
	upgrade(false)
{

}

void Enemy::update(float deltaTime) {

}

void Enemy::show(SDL_Renderer* renderer) {

}