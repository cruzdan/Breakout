// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Menu.h"
#include "Textures.h"
#include "Render.h"

Menu::Menu():
	gameOver(false),
	index(0),
	players(1),
	phase(0),
	x(0),
	backgroundSpeed(0),
	width(0),
	height(0),
	pauseTextures(),
	pauseRects()
{

}

void Menu::showCP(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	SDL_Rect imageMenuRect = { (int)x,0,width,height };
	SDL_RenderCopy(renderer, imageMenuTexture, NULL, &imageMenuRect);
	if (phase == 1) {
		//the menu is still
		SDL_Rect shipRect;
		shipRect.w = width / 9;
		shipRect.h = height / 12;
		shipRect.x = width / 4 + width / 32;
		if(players == 1)
			shipRect.y = (int)(height * 0.58 - shipRect.h / 2);
		else
			shipRect.y = (int)(height * 0.64 - shipRect.h / 2);
		SDL_Rect rect = { 0,0,32,20 };
		SDL_RenderCopy(renderer, shipTexture, &rect, &shipRect);
	}
	SDL_RenderPresent(renderer);
}

void Menu::updateCP(float deltaTIme) {
	if (phase == 0) {
		x += backgroundSpeed * deltaTIme;
		if (x >= 0) {
			phase = 1;
		}
	}
}

void Menu::keyIG(float deltaTime, const Uint8* keys) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		int typeEvent = event.type;
		if (typeEvent == SDL_QUIT) {
			gameOver = true;
		}
		if (keys[SDL_SCANCODE_ESCAPE])
			index = 2;
	}
}

void Menu::showShipData(SDL_Renderer* renderer, Ship* ship) {

	Vec4 a = ship->getMenuRect(6);

	SDL_Rect rect = { a.x,a.y,a.w,a.h };
	SDL_RenderCopy(renderer, ship->getMenuTexture(0), NULL, &rect);

	a = ship->getMenuRect(7);
	rect = { a.x,a.y,a.w,a.h };
	SDL_RenderCopy(renderer, ship->getMenuTexture(1), NULL, &rect);
}

void Menu::showShipUpgradeImages(SDL_Renderer* renderer, Ship* ship) {

	Vec4 p = ship->getMenuRect(0);
	Vec4 l = ship->getSpriteRect(0);

	SDL_Rect rect = { p.x,p.y,p.w,p.h };
	SDL_Rect spriteRect = { l.x, l.y,l.w,l.h };
	SDL_RenderCopy(renderer, menuTexture, &spriteRect, &rect);

	rect.x = ship->getMenuRect(1).x;
	spriteRect.x = ship->getSpriteRect(1).x;
	spriteRect.y = ship->getSpriteRect(1).y;
	SDL_RenderCopy(renderer, menuTexture, &spriteRect, &rect);

	rect.x = ship->getMenuRect(2).x;
	spriteRect.x = ship->getSpriteRect(2).x;
	spriteRect.y = ship->getSpriteRect(2).y;
	SDL_RenderCopy(renderer, menuTexture, &spriteRect, &rect);

	rect.x = ship->getMenuRect(3).x;
	spriteRect.x = ship->getSpriteRect(3).x;
	spriteRect.y = ship->getSpriteRect(3).y;
	SDL_RenderCopy(renderer, menuTexture, &spriteRect, &rect);

	rect.x = ship->getMenuRect(4).x;
	spriteRect.x = ship->getSpriteRect(4).x;
	spriteRect.y = ship->getSpriteRect(4).y;
	SDL_RenderCopy(renderer, menuTexture, &spriteRect, &rect);

	rect.x = ship->getMenuRect(5).x;
	spriteRect.x = ship->getSpriteRect(5).x; 
	spriteRect.y = ship->getSpriteRect(5).y;
	SDL_RenderCopy(renderer, menuTexture, &spriteRect, &rect);
}

void Menu::showIG(SDL_Renderer* renderer, std::vector<class Ship*> ships) {
	SDL_Rect showRect;
	showRect = { (int)(width * 0.253), (int)(height * 0.93), (int)(width * 0.053), (int)(height * 0.04) };
	SDL_RenderCopy(renderer, menuTextTexture[0], NULL, &showRect);

	showRect.x = (int)(width * 0.625);
	showRect.w = (int)(width * 0.053);
	SDL_RenderCopy(renderer, menuTextTexture[1], NULL, &showRect);

	for (auto ship : ships) {
		showShipUpgradeImages(renderer, ship);
		showShipData(renderer, ship);
	}
}

void Menu::keyPause(const Uint8* keys) {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		int typeEvent = event.type;
		if (typeEvent == SDL_QUIT) {
			gameOver = true;
		}
		else if (typeEvent == SDL_KEYDOWN) {
			if (keys[SDL_SCANCODE_ESCAPE])
				index = 1;
		}
		if (typeEvent == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
			int mouseX;
			int mouseY;
			SDL_GetMouseState(&mouseX, &mouseY);
			SDL_Rect mouseRect;
			mouseRect.x = mouseX;
			mouseRect.y = mouseY;
			mouseRect.w = 1;
			mouseRect.h = 1;
			SDL_Rect exitRect = { pauseRects[10].x,pauseRects[10].y,pauseRects[10].w,pauseRects[10].h };
			if (SDL_HasIntersection(&mouseRect, &exitRect)) {
				gameOver = true;
			}
		}
	}
}

void Menu::showPause(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);
	for (int i = 0; i < 11; i++) {
		SDL_Rect showRect = { pauseRects[i].x,pauseRects[i].y,pauseRects[i].w,pauseRects[i].h };
		SDL_RenderCopy(renderer, pauseTextures[i], NULL, &showRect);
	}
	SDL_RenderPresent(renderer);
}

void Menu::initPauseTextures(SDL_Renderer* renderer) {
	SDL_Color white = { 255,255,255 };
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(height * 0.2), "PAUSE", &pauseTextures[0], renderer);
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(height * 0.08), "ship 1:", &pauseTextures[1], renderer);
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(height * 0.08), "move with w,a,s,d", &pauseTextures[2], renderer);
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(height * 0.08), "shoot with f", &pauseTextures[3], renderer);
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(height * 0.08), "select upgrade with g", &pauseTextures[4], renderer);
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(height * 0.08), "ship 2:", &pauseTextures[5], renderer);
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(height * 0.08), "move with rows up,down,right,left", &pauseTextures[6], renderer);
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(height * 0.08), "shoot with k", &pauseTextures[7], renderer);
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(height * 0.08), "select upgrade with L", &pauseTextures[8], renderer);
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(height * 0.08), "Press esc to continue", &pauseTextures[9], renderer);
	generateTextTexture(white, "ttf/Oswald-BoldItalic.ttf", (int)(height * 0.08), "Click here to exit", &pauseTextures[10], renderer);
}

void Menu::initPauseRects() {
	pauseRects[0] = { width / 4,0,width / 3,height / 5 };
	for (int i = 1; i < 11; i++) {
		pauseRects[i].x = 0;
		pauseRects[i].y = pauseRects[i - 1].y + pauseRects[i - 1].h;
		pauseRects[i].h = (int)(height * 0.08);
	}
	pauseRects[1].w = (int)(7.0f * 0.0303f * width);
	pauseRects[2].w = (int)(17.0f * 0.0303f * width);
	pauseRects[3].w = (int)(14.0f * 0.0303f * width);
	pauseRects[4].w = (int)(21.0f * 0.0303f * width);
	pauseRects[5].w = (int)(7.0f * 0.0303f * width);
	pauseRects[6].w = (int)(23.0f * 0.0303f * width);
	pauseRects[7].w = (int)(12.0f * 0.0303f * width);
	pauseRects[8].w = (int)(21.0f * 0.0303f * width);
	pauseRects[9].w = (int)(21.0f * 0.0303f * width);
	pauseRects[10].w = (int)(18.0f * 0.0303f * width);
}