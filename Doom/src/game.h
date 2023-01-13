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

#include "spriteObject.h"
#include "animatedSpriteObject.h"

#include "objectHandler.h"

#include "weapon.h"

#include "pathfinding.h"

#include "sound.h"

enum SoundIndex
{
	SHOTGUN,
	
	NPC_PAIN,
	NPC_DEATH,
	NPC_SHOT,

	PLAYER_PAIN,

	MAX_SOUNDS
};

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

	void setGameOver() { m_bGameOver = true; }
	void setGameWon() { setGameOver(); m_bVictory = true; }

	void startNewGame();

	SDL_Window* window() const { return m_pWindow; }
	SDL_Renderer* renderer() const { return m_pRenderer; }
	const std::vector<SDL_Event>& keyboardEvents() const { return m_keyboardEvents; }
	const std::vector<SDL_Event>& mouseEvents() const { return m_mouseEvents; }
	const Map& map() const { return m_map; }
	Map& map() { return m_map; }

	const Raycasting& raycasting() const { return m_raycasting; }
	Raycasting& raycasting() { return m_raycasting; }

	const ObjectRenderer& objectRenderer() const { return m_objectRenderer; }
	ObjectRenderer& objectRenderer() { return m_objectRenderer; }

	const ObjectHandler& objectHandler() const { return m_objectHandler; }
	ObjectHandler& objectHandler() { return m_objectHandler; }

	const Player& player() const { return m_player; }
	Player& player() { return m_player; }

	const Weapon& weapon() const { return m_weapon; }
	Weapon& weapon() { return m_weapon; }

	const Sound* getSound(SoundIndex id) const { return m_soundEffects[id]; }
	Sound* getSound(SoundIndex id) { return m_soundEffects[id]; }

	const Pathfinding& pathfinding() const { return m_pathfinding; }
	Pathfinding& pathfinding() { return m_pathfinding; }
private:
	void runControlledFPS();
	void runMaxFPS();

private:
	SDL_Window					*m_pWindow{};
	SDL_Renderer				*m_pRenderer{};

	SDL_Color					m_clearColor{ convert(kCOLOR_BLACK) };
	std::vector<SDL_Event>		m_keyboardEvents;
	std::vector<SDL_Event>		m_mouseEvents;

	bool						m_bQuitGame{ false };
	bool						m_bPauseGame{ false };

	const float					m_timePerFrameInMs{ 1000.0f / FPS };

	Map							m_map;

	Player						m_player;
	Raycasting					m_raycasting;

	ObjectRenderer				m_objectRenderer;

	ObjectHandler				m_objectHandler;
	
	Weapon						m_weapon;
	std::vector<SoundEffect*>	m_soundEffects;

	Pathfinding					m_pathfinding;

	bool						m_bGameOver{ false };
	bool						m_bVictory{ false };
};

#endif // !__GAME_H__