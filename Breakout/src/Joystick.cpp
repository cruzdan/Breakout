#include <SDL.h>
#include <iostream>
#include "Paddle.h"
SDL_Joystick* joystick;
int totalJoysticks = 0;

void loadJoystick() {
	joystick = SDL_JoystickOpen(0);
	if (!joystick) {
		std::cout << "there is no joystick 1" << std::endl;
	}
	totalJoysticks = SDL_NumJoysticks();
}

void detectKeyJoystick() {
	if (SDL_JoystickGetAxis(joystick, 0) == SDL_JOYSTICK_AXIS_MAX) {
		movePaddleRight();
	}
	else if (SDL_JoystickGetAxis(joystick, 0) == SDL_JOYSTICK_AXIS_MIN) {
		movePaddleLeft();
	}
}

void closeJoystick() {
	SDL_JoystickClose(joystick);
}