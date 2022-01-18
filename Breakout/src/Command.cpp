// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SDL.h>
#include <string>
#include <SDL_ttf.h>
#include "Menu.h"
#include "Paddle.h"
#include "Ball.h"
#include "Update.h"
#include "Brick.h"
#include "Render.h"

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
	commandLineRect.y = (int)(getScreenHeight() * 0.95);
	commandLineRect.w = getScreenWidth();
	commandLineRect.h = (int)(getScreenHeight() * 0.05);

	commandTextRect.x = commandLineRect.x;
	commandTextRect.y = commandLineRect.y;
	commandTextRect.h = commandLineRect.h;

	fpsTextRect.x = commandLineRect.x;
	fpsTextRect.y = 0;
	fpsTextRect.h = commandLineRect.h;

	commandMenuRect.x = 0;
	commandMenuRect.h = totalCommands * commandLineRect.h;
	commandMenuRect.y = getScreenHeight() - commandMenuRect.h - commandLineRect.h;
	commandMenuRect.w = getScreenWidth();

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
	for (int i = 0; i < totalCommands; i++) {
		generateTextTexture({ 255,255,255,0 }, "fonts/OpenSans-Bold.ttf", commandLineRect.h, commands[i], &commandTextures[i], &commandRects[i], renderer);
	}
}

void writeCommandLineText(SDL_Renderer* renderer, std::string text) {
	commandTextRect.w = 0;
	if (text.size() < 1)
		generateTextTexture({ 255,255,255,0 }, "fonts/OpenSans-Bold.ttf", commandLineRect.h, text, &commandText, renderer);
	else
		generateTextTexture({ 255,255,255,0 }, "fonts/OpenSans-Bold.ttf", commandLineRect.h, text, &commandText, &commandTextRect, renderer);
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
	else if (wordNumber == 44) {
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
				generateTextTexture({ 255,255,255,0 }, "fonts/Oswald-BoldItalic.ttf", getScreenHeight() / 30, std::to_string(score), &textPuntuation, renderer);
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

