#include "game.h"
#include <bitset>

int main()
{
	int width = 600;
	int height = 600;
	std::string gameTitle = "Gravity Sim";

	std::bitset<FLAG_SIZE> flags;
	flags.set(SAME_RADIUS, false);
	flags.set(SAME_MASS, false);

	Game game(gameTitle, width, height);

	int objectCount = 2;
	game.setUpObjects(objectCount, flags);

	game.run();

	return 0;
}