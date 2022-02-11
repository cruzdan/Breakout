// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Bullet.h"

Bullet::Bullet():
	x(0),
	y(0),
	w(0),
	h(0),
	firstX(0),
	firstY(0),
	endY(0),
	endX(0),
	dead(false),
	damage(0)
{
	
}

void Bullet::update(float deltaTime) {

}

void Bullet::show(SDL_Renderer* renderer) {

}