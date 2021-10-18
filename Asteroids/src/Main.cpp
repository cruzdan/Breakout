#include "Game.h"

int main(int argc, char* args[]) {
	Game game;
	if (game.init()) {
		game.loop();
	}
	game.closeGame();
	return 0;
}