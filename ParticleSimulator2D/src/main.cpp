#include "engine.h"
#include "Common/constants.h"

#include <iostream>

int main()
{
	int majorVerHint = OPENGL_MAJOR_VERSION;
	int minorVerHint = OPENGL_MINOR_VERSION;

	Engine engine;
	engine.init(TITLE, WIDTH, HEIGHT, majorVerHint, minorVerHint);
	engine.enableBlendFunc();
	engine.startLoop();
	return 0;
}