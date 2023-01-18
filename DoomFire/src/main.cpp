#include "engine.h"

int main()
{
	Engine fireEngine;

	fireEngine.setup();

	bool bRunOnMaxFPS = true;
	fireEngine.run(bRunOnMaxFPS);

	fireEngine.teardown();

	return 0;
}