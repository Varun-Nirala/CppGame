#include "game.h"

#include <vector>

int main()
{
	Game game;

	game.init();

	bool bRunOnMaxFPS{ false };

	game.run(bRunOnMaxFPS);

	return 0;
}