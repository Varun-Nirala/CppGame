#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <SDL.h>
#undef main
#include <string>
#include <vector>

#include "fire.h"

class Engine
{
public:
	Engine();
	~Engine() { teardown(); }

	bool setup();
	void teardown();

	void run(bool bRunOnMaxFPS);

private:
	void checkEvents();
	void update(float elapsedTime);
	void render();

	void runControlledFPS();
	void runMaxFPS();

private:
	SDL_Window						*m_pWindow{};
	SDL_Renderer					*m_pRenderer{};
	SDL_Color						m_clearColor{ 50, 20, 20, 255 };

	std::string						m_title;
	const int						m_width{ 360 };
	const int						m_height{ 168 };

	const int						m_pixelWidth{ 6 };
	const int						m_pixelHeight{ 6 };

	const int						m_goalFPS{ 60 };

	const float						m_timePerFrameInMs{ 1000.0f / m_goalFPS };

	bool							m_bQuit{ false };
	bool							m_bPause{ false };

	Fire							m_fire;
};

#endif //!__ENGINE_H__