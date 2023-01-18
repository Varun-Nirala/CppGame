#include "game.h"

int main()
{
	Game game;

	game.setup();

	game.run();

	game.teardown();

	return 0;
}