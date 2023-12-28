#include "game.h"

int main()
{
	int width = 600;
	int height = 600;
	std::string gameTitle = "Gravity Sim";

	Game game(gameTitle, width, height);

	game.setUpObjects(200, true);

	game.run();

	return 0;
}