#pragma once
#include <SDL.h>
#include <string>
extern bool commandLine;
extern SDL_Rect commandLineRect;
extern std::string command;
extern bool fpsActive;
extern bool allCommands;

void initCommandLine();
void writeCommandLineText(SDL_Renderer* renderer, std::string text);
void writeFPSText(SDL_Renderer* renderer, int fps);
void addWordToCommand(SDL_Renderer* renderer, int wordNumber);
void showCommandLineText(SDL_Renderer* renderer);
void closeCommand();
void checkCommandMatch(SDL_Renderer* renderer);
void showFPSText(SDL_Renderer* renderer);
void closeFPS();
void showAllCommands(SDL_Renderer* renderer);
void closeAllCommands();
void writeAllCommands(SDL_Renderer* renderer);