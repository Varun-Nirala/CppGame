#include "displayWindow.h"
#include "Common/constants.h"

int main()
{
	int majorVerHint = OPENGL_MAJOR_VERSION;
	int minorVerHint = OPENGL_MINOR_VERSION;

	DisplayWindow pWindow(TITLE, WIDTH, HEIGHT, majorVerHint, minorVerHint);

	while (pWindow.isOpen())
	{
		;
	}
	return 0;
}