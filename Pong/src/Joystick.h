#pragma once
#include <SDL.h>

extern SDL_Joystick* joystick1;
extern SDL_Joystick* joystick2;
extern int totalJoysticks;

void initJoystick();
void detectKeyJoystick(SDL_Joystick* joystick, SDL_Rect* paddle);
void closeJoystick();