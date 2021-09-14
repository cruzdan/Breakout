#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include "GlobalVariables.h"
#include "FPS.h"
#include "Menu.h"
#include "Paddle.h"
#include "Ball.h"
#include "Update.h"
#include "Brick.h"

//command line
bool commandLine = false;
SDL_Rect commandLineRect;
std::string command = "";
SDL_Texture* commandText;
SDL_Rect commandTextRect;


//fps
bool fpsActive = false;
SDL_Texture* fpsText;
SDL_Rect fpsTextRect;

const int totalCommands = 11;
bool allCommands = false;

//all commands
SDL_Rect commandMenuRect;
SDL_Texture* commandTextures[totalCommands];
SDL_Rect commandRects[totalCommands];
std::string commands[totalCommands] = {
	"fps count on",
	"fps count off",
	"music on",
	"music off",
	"sound on",
	"sound off",
	"paddle speed up",
	"paddle speed down",
	"ball speed up",
	"ball speed down",
	"next level"
};

void initCommandLine() {
	commandLineRect.x = 0;
	commandLineRect.y = (int)(SCREEN_HEIGHT * 0.95);
	commandLineRect.w = SCREEN_WIDTH;
	commandLineRect.h = (int)(SCREEN_HEIGHT * 0.05);

	commandTextRect.x = commandLineRect.x;
	commandTextRect.y = commandLineRect.y;
	commandTextRect.h = commandLineRect.h;

	fpsTextRect.x = commandLineRect.x;
	fpsTextRect.y = 0;
	fpsTextRect.h = commandLineRect.h;

	commandMenuRect.x = 0;
	commandMenuRect.h = totalCommands * commandLineRect.h;
	commandMenuRect.y = SCREEN_HEIGHT - commandMenuRect.h - commandLineRect.h;
	commandMenuRect.w = SCREEN_WIDTH;

	for (int i = 0; i < totalCommands; i++) {
		commandRects[i].x = 0;
		commandRects[i].y = commandMenuRect.y + i * commandLineRect.h;
		commandRects[i].h = commandLineRect.h;
	}
	
}

void showAllCommands(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 105, 105, 105, 0);
	SDL_RenderFillRect(renderer, &commandMenuRect);
	for (int i = 0; i < totalCommands; i++) {
		SDL_RenderCopy(renderer, commandTextures[i], NULL, &commandRects[i]);
	}
}

void writeAllCommands(SDL_Renderer* renderer) {
	SDL_Color color = { 255,255,255 };
	TTF_Font* font = TTF_OpenFont("fonts/OpenSans-Bold.ttf", commandLineRect.h);
	SDL_Surface* textSurface;

	for (int i = 0; i < totalCommands; i++) {
		textSurface = TTF_RenderText_Solid(font, commands[i].c_str(), color);
		commandTextures[i] = SDL_CreateTextureFromSurface(renderer, textSurface);
		commandRects[i].w = textSurface->w;
	}
	

	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
}

void writeCommandLineText(SDL_Renderer* renderer, std::string text) {
	SDL_Color color = { 255,255,255 };
	TTF_Font* font = TTF_OpenFont("fonts/OpenSans-Bold.ttf", commandLineRect.h);
	SDL_Surface* textSurface;

	textSurface = TTF_RenderText_Solid(font, text.c_str(), color);
	commandText = SDL_CreateTextureFromSurface(renderer, textSurface);
	if(text.size() < 1)
		commandTextRect.w = 0;
	else
		commandTextRect.w = textSurface->w;

	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
}

void writeFPSText(SDL_Renderer* renderer) {
	SDL_Color color = { 36,144,98 };
	TTF_Font* font = TTF_OpenFont("fonts/OpenSans-Bold.ttf", fpsTextRect.h);
	SDL_Surface* textSurface;
	char c[4];
	SDL_itoa(fps, c, 10);
	textSurface = TTF_RenderText_Solid(font, c, color);
	fpsText = SDL_CreateTextureFromSurface(renderer, textSurface);
	fpsTextRect.w = textSurface->w;
	SDL_FreeSurface(textSurface);
	textSurface = nullptr;
	TTF_CloseFont(font);
}

//add the word specified by event.key.keysym.scancode number in the string command
void addWordToCommand(SDL_Renderer* renderer, int wordNumber) {
	/*
	wordNumber 4 - 29 = letter
	wordNumber 30 - 39 = number
	*/
	if (wordNumber > 3 && wordNumber < 30) {
		//letter in ASCII
		command += (char)(wordNumber + 93);
	}
	else if (wordNumber > 29 && wordNumber < 39) {
		//number in ASCII 1-9
		command += (char)(wordNumber + 19);
	}
	else if (wordNumber == 39) {
		//number in ASCII 0
		command += '0';
	}
	else if(wordNumber == 44){
		//space
		command += ' ';
	}
	else if (wordNumber == 42 && command.size() > 0) {
		//delete
		command.pop_back();
	}
	writeCommandLineText(renderer, command);
}


void checkCommandMatch(SDL_Renderer* renderer) {
	for (int i = 0; i < 12; i++) {
		if (command.compare(commands[i]) == 0) {
			switch (i) {
			case 0:
				fpsActive = true;
				break;
			case 1:
				fpsActive = false;
				break;
			case 2:
				turnOnMusic(renderer);
				break;
			case 3:
				turnOffMusic(renderer);
				break;
			case 4:
				turnOnSound(renderer);
				break;
			case 5:
				turnOffSound(renderer);
				break;
			case 6:
				incrementPaddleSpeed();
				break;
			case 7:
				decrementPaddleSpeed();
				break;
			case 8:
				incrementBallSpeed();
				break;
			case 9:
				decrementBallSpeed();
				break;
			case 10:
				score += actualBricks;
				writeScore(renderer);
				nextLevel(renderer);
				break;
			}
			break;
		}
	}
}

void showCommandLineText(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, commandText, NULL, &commandTextRect);
}

void showFPSText(SDL_Renderer* renderer) {
	SDL_RenderCopy(renderer, fpsText, NULL, &fpsTextRect);
}

void closeCommand() {
	SDL_DestroyTexture(commandText);
}

void closeFPS() {
	SDL_DestroyTexture(fpsText);
}

void closeAllCommands() {
	for (int i = 0; i < totalCommands; i++) {
		SDL_DestroyTexture(commandTextures[i]);
	}
}

