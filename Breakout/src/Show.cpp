#include <SDL.h>
#include "Paddle.h"
#include "Menu.h"
#include "GlobalVariables.h"
#include "Ball.h"
#include "Brick.h"
#include "Command.h"
#include "Capsule.h"

void show(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
	if (menuIndex == 0) {
		SDL_RenderFillRect(renderer, &paddle);
		SDL_RenderDrawLine(renderer, boardWidth, 0, boardWidth, SCREEN_HEIGHT);
		showGameMenu(renderer);
		if (serve) {
			SDL_RenderCopy(renderer, textStart, NULL, &startRect);
		}
		else {
			SDL_RenderCopy(renderer, ballTexture, NULL, &ballRect);
			showBricks();
			
			showCapsules(renderer);
			showBullets(renderer);
		}
	}
	else {
		showPauseMenu(renderer);
	}
	if (commandLine) {
		SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
		SDL_RenderFillRect(renderer, &commandLineRect);
		showCommandLineText(renderer);
	}
	if (fpsActive) {
		showFPSText(renderer);
	}
	SDL_RenderPresent(renderer);
}