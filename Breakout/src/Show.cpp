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
	SDL_SetRenderDrawColor(renderer, 168, 2, 47, 0);
	if (menuIndex == 0) {
		showBackgroundImage(renderer);
		SDL_RenderFillRect(renderer, &paddle);
		SDL_RenderDrawLine(renderer, boardWidth, 0, boardWidth, SCREEN_HEIGHT);
		showGameMenu(renderer);
		if (serve) {
			SDL_RenderCopy(renderer, textStart, NULL, &startRect);
		}
		else {
			showBalls(renderer);
			showBricks(renderer);
			showCapsules(renderer);
			showBullets(renderer);
		}
	}
	else {
		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		showPauseMenu(renderer);
	}
	if (commandLine) {
		SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
		SDL_RenderFillRect(renderer, &commandLineRect);
		showCommandLineText(renderer);
		if(allCommands)
			showAllCommands(renderer);
	}
	if (fpsActive) {
		showFPSText(renderer);
	}
	SDL_RenderPresent(renderer);
}