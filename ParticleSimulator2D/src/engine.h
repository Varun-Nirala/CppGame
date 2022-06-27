#pragma once

#include <memory>

class DisplayWindow;

class Engine
{
public:
	bool initDisplayWindow(const char* title, int width, int height, int& hintOpenGlMajorVersion, int& hintOpenGlMinorVersion);
	void startLoop();

private:
	void gameLoop();
	void update();
	void render();

private:
	std::unique_ptr<DisplayWindow>			m_pWindow;
};