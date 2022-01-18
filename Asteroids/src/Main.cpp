// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "Game.h"

int main(int argc, char* args[]) {
	Game game;
	if (game.init()) {
		game.loop();
	}
	game.closeGame();
	return 0;
}