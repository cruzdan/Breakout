#include <SDL.h>
#include <iostream>
#include "Command.h"

int frameCount = 0, timerFPS = 0, lastFrame = 0, fps = 0, lastTime = 0;

void beforeFPS() {
	lastFrame = SDL_GetTicks();
	if (lastFrame >= (lastTime + 1000)) {
		lastTime = lastFrame;
		fps = frameCount;
		frameCount = 0;
	}
}

void afterFPS(SDL_Renderer* renderer) {
	const int frameDelay = 1000 / 60;
	frameCount++;
	timerFPS = SDL_GetTicks() - lastFrame;
	if (timerFPS < frameDelay) {
		SDL_Delay(frameDelay - timerFPS);
	}
	if (fpsActive)
		writeFPSText(renderer);
}