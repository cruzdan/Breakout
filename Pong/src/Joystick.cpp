#include <SDL.h>
#include <iostream>
#include "Joystick.h"
#include "Paddle.h"

SDL_Joystick* joystick1;
SDL_Joystick* joystick2;
int totalJoysticks = 0;

void initJoystick() {
	joystick1 = SDL_JoystickOpen(0);
	if (!joystick1) {
		std::cout << "there is no joystick 1" << std::endl;
	}
	joystick2 = SDL_JoystickOpen(1);
	if (!joystick2) {
		std::cout << "there is no joystick 2" << std::endl;
	}
	totalJoysticks = SDL_NumJoysticks();
}

void detectKeyJoystick(SDL_Joystick* joystick, SDL_Rect* paddle) {
	if (SDL_JoystickGetAxis(joystick, 1) == SDL_JOYSTICK_AXIS_MAX) {
		movePaddleDown(paddle);
	}
	else if (SDL_JoystickGetAxis(joystick, 1) == SDL_JOYSTICK_AXIS_MIN) {
		movePaddleUp(paddle);
	}
}

void closeJoystick() {
	SDL_JoystickClose(joystick1);
	SDL_JoystickClose(joystick2);
}