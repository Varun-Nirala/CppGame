#include "game.h"

#include <vector>

int main()
{
	for (int i = 0; i < 80; ++i)
	{
		std::cout << '\n';
	}
	Game game;

	game.init();

	bool bRunOnMaxFPS{ false };

	game.run(bRunOnMaxFPS);

	return 0;
}