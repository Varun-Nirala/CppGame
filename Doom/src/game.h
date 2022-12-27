#ifndef __GAME_H__
#define __GAME_H__

#include <SDL.h>
#undef main
#include <SDL_image.h>
#include <SDL_timer.h>
#include <SDL_ttf.h>

#include <vector>

#include "common/constants.h"
#include "map.h"
#include "player.h"
#include "raycasting.h"
#include "objectRenderer.h"

class Game
{
public:
	Game();
	~Game() { quit(); }

	bool init();

	void update(float dt);
	void preDraw();
	void draw();
	void postDraw();

	void run(bool bRunOnMaxFPS = true);

	void quit();

	void checkEvents();

	SDL_Window* window() const { return m_pWindow; }
	SDL_Renderer* renderer() const { return m_pRenderer; }
	SDL_Surface* screenSurface() const { return m_pScreenSurface; }
	const std::vector<SDL_Event>& keyboardEvents() const { return m_keyboardEvents; }
	const std::vector<SDL_Event>& mouseEvents() const { return m_mouseEvents; }
	const Map& map() const { return m_map; }
	Map& map() { return m_map; }

	const Raycasting& raycasting() const { return m_raycasting; }
	Raycasting& raycasting() { return m_raycasting; }

	const ObjectRenderer& objectRenderer() const { return m_objectRenderer; }
	ObjectRenderer& objectRenderer() { return m_objectRenderer; }

	const Player& player() const { return m_player; }
	Player& player() { return m_player; }

private:
	void runControlledFPS();
	void runMaxFPS();

private:
	SDL_Window				*m_pWindow{};
	SDL_Renderer			*m_pRenderer{};
	SDL_Surface				*m_pScreenSurface{};

	SDL_Color				m_clearColor{ convert(kCOLOR_BLACK) };
	std::vector<SDL_Event>	m_keyboardEvents;
	std::vector<SDL_Event>	m_mouseEvents;

	bool					m_bQuitGame{ false };

	const float				m_timePerFrameInMs{ 1000.0f / FPS };

	Map						m_map;

	Player					m_player;
	Raycasting				m_raycasting;
	ObjectRenderer			m_objectRenderer;
};

#endif // !__GAME_H__