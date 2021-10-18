#include <SDL.h>
#include "Game.h"
#include <SDL_ttf.h>
#include "Sprite.h"
#include "Menu.h"

Menu::Menu(SDL_Renderer* renderer, int totalWidth, int totalHeight) :
	backgroundRect({ 0,0,0,0 }),
	indexMenu(0),
	score(0),
	k(9)
{
	gameRects[0].x = 0;
	gameRects[0].y = 0;
	gameRects[0].w = totalWidth / 4;
	gameRects[0].h = totalHeight / 10;

	gameRects[1].x = gameRects[0].x;
	gameRects[1].y = gameRects[0].h;
	gameRects[1].w = gameRects[0].w / 2;
	gameRects[1].h = gameRects[0].h;

	gameRects[3].x = gameRects[0].w;
	gameRects[3].y = gameRects[0].y;
	gameRects[3].w = gameRects[1].w / 7;
	gameRects[3].h = gameRects[1].h;

	menu0Rects[0].x = totalWidth / 10;
	menu0Rects[0].y = 0;
	menu0Rects[0].w = (int)(totalWidth * 0.8);
	menu0Rects[0].h = totalHeight / 4;

	menu0Rects[1].x = (int)(totalWidth * 0.3);
	menu0Rects[1].y = menu0Rects[0].h;
	menu0Rects[1].w = (int)(totalWidth * 0.4);
	menu0Rects[1].h = totalHeight / 4;

	menu0Rects[2].x = totalWidth / 10;
	menu0Rects[2].y = menu0Rects[1].y + menu0Rects[1].h;
	menu0Rects[2].w = (int)(totalWidth * 0.8);
	menu0Rects[2].h = totalHeight / 4;

	menu0Rects[3].x = (int)(totalWidth * 0.3);
	menu0Rects[3].y = menu0Rects[2].y + menu0Rects[2].h;
	menu0Rects[3].w = (int)(totalWidth * 0.4);
	menu0Rects[3].h = totalHeight / 4;

	gameRects[2].h = gameRects[1].h;
	gameRects[2].w = gameRects[2].h / 2;
	gameRects[2].y = gameRects[1].y;

	instructionRects[0].x = 0;
	instructionRects[0].y = totalHeight / 10;
	instructionRects[0].w = totalWidth;
	instructionRects[0].h = totalHeight / 10;

	instructionRects[1].x = totalWidth / 4;
	instructionRects[1].y = instructionRects[0].y + instructionRects[0].h + totalHeight / 10;
	instructionRects[1].w = totalWidth / 2;
	instructionRects[1].h = totalHeight / 10;

	instructionRects[2].x = totalWidth / 4;
	instructionRects[2].y = instructionRects[1].y + instructionRects[1].h + totalHeight / 10;
	instructionRects[2].w = totalWidth / 2;
	instructionRects[2].h = totalHeight / 10;

	instructionRects[3].x = totalWidth / 8;
	instructionRects[3].y = instructionRects[2].y + instructionRects[2].h + totalHeight / 10;
	instructionRects[3].w = 3 * totalWidth / 4;
	instructionRects[3].h = totalHeight / 10;

	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = totalWidth;
	backgroundRect.h = totalHeight;

	generateMenu(renderer, totalHeight);
}

void Menu::changeTextScore(SDL_Renderer* renderer, std::string newText, int height) {
	TTF_Font* font = TTF_OpenFont("ttf/Oswald-Stencil.ttf", height);
	SDL_Surface* textSurface;
	SDL_Color white = { 255,255,255 };
	textSurface = TTF_RenderText_Solid(font, newText.c_str(), white);
	numberScore = SDL_CreateTextureFromSurface(renderer, textSurface);
	SDL_FreeSurface(textSurface);
}

void Menu::generateMenu(SDL_Renderer* renderer, int totalHeight) {
	SDL_Color white = { 255,255,255 };
	SDL_Surface* textSurface;
	TTF_Font* font = TTF_OpenFont("ttf/Oswald-BoldItalic.ttf", totalHeight / 4);
	//menu 0
	textSurface = TTF_RenderText_Solid(font, "ASTEROIDS", white);
	titleTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Play", white);
	playTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Controls", white);
	controlsTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Exit", white);
	exitTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	//menu 1
	font = TTF_OpenFont("ttf/Oswald-Stencil.ttf", totalHeight / 10);
	textSurface = TTF_RenderText_Solid(font, "Score: ", white);
	scoreTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "0", white);
	numberScore = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Lifes:", white);
	lifeTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
	//menu 2
	font = TTF_OpenFont("ttf/Oswald-BoldItalic.ttf", totalHeight / 10);
	textSurface = TTF_RenderText_Solid(font, "Press w,a,s,d to move the ship", white);
	instruction1Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Press space to shoot", white);
	instruction2Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Press R to restart", white);
	instruction3Texture = SDL_CreateTextureFromSurface(renderer, textSurface);
	textSurface = TTF_RenderText_Solid(font, "Press esc to go to main menu", white);
	instruction4Texture = SDL_CreateTextureFromSurface(renderer, textSurface);

	TTF_CloseFont(font);
}

void Menu::showBackground(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, backgroundTexture, NULL, &backgroundRect);
}

void Menu::showMenu0(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, titleTexture, NULL, &menu0Rects[0]);
	SDL_RenderCopy(renderer, playTexture, NULL, &menu0Rects[1]);
	SDL_RenderCopy(renderer, controlsTexture, NULL, &menu0Rects[2]);
	SDL_RenderCopy(renderer, exitTexture, NULL, &menu0Rects[3]);
}

void Menu::showMenu1(SDL_Renderer* renderer, int lifes) {
	SDL_RenderCopy(renderer, scoreTexture, NULL, &gameRects[0]);
	SDL_RenderCopy(renderer, numberScore, NULL, &gameRects[3]);
	SDL_RenderCopy(renderer, lifeTexture, NULL, &gameRects[1]);
	for (int i = 0; i < lifes; i++) {
		gameRects[2].x = gameRects[1].w + gameRects[2].w * i;
		SDL_RenderCopy(renderer, shipTexture, NULL, &gameRects[2]);
	}
}

void Menu::showMenu2(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, instruction1Texture, NULL, &instructionRects[0]);
	SDL_RenderCopy(renderer, instruction2Texture, NULL, &instructionRects[1]);
	SDL_RenderCopy(renderer, instruction3Texture, NULL, &instructionRects[2]);
	SDL_RenderCopy(renderer, instruction4Texture, NULL, &instructionRects[3]);
}

//restart when all lifes are lost
void Menu::completeRestartMenu(SDL_Renderer* renderer, int height) {
	score = 0;
	changeTextScore(renderer, std::to_string(score), height);
	k = 9;
	gameRects[3].w = gameRects[1].w / 7;
}

void Menu::incrementScore(SDL_Renderer* renderer, int height) {
	if (score == k) {
		k += 9 * (k + 1);
		gameRects[3].w += gameRects[1].w / 7;
	}
	score++;
	changeTextScore(renderer, std::to_string(score), height);
}

void Menu::detectMenuKeys(const Uint8* keys, bool* gameOver) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		int typeEvent = event.type;
		if (typeEvent == SDL_QUIT) {
			*gameOver = true;
		}
		else if (typeEvent == SDL_MOUSEBUTTONDOWN && indexMenu == 0 && event.button.button == SDL_BUTTON_LEFT) {
			int mouseX;
			int mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			SDL_Rect mouseRect;
			mouseRect.x = mouseX;
			mouseRect.y = mouseY;
			mouseRect.w = 1;
			mouseRect.h = 1;
			if (SDL_HasIntersection(&mouseRect, &menu0Rects[1])) {
				indexMenu = 1;
			}
			else if (SDL_HasIntersection(&mouseRect, &menu0Rects[2])) {
				indexMenu = 2;
			}
			else if (SDL_HasIntersection(&mouseRect, &menu0Rects[3])) {
				*gameOver = true;
			}
		}
		else if (typeEvent == SDL_KEYDOWN) {
			if (keys[SDL_SCANCODE_ESCAPE]) {
				switch (indexMenu) {
				case 0:
					*gameOver = true;
					break;
				case 1:
				case 2:
					indexMenu = 0;
					break;
				}
			}
		}
	}
}