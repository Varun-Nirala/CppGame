#include "game.h"

#include "common/constants.h"
#include "common/logger.h"

#include <SDL_mixer.h>

Game::Game()
	: m_map(this)
	, m_player(this)
	, m_raycasting(this)
	, m_objectRenderer(this)
	, m_objectHandler(this)
	, m_weapon(this)
	, m_pathfinding(this)
{
}

bool Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		ns_Util::Logger::LOG_ERROR("Error initialising SDL : ", SDL_GetError(), '\n');
		assert(false);
		return false;
	}

	const int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	const int initedFlags = IMG_Init(flags);

	if ((flags & initedFlags) != flags)
	{
		ns_Util::Logger::LOG_ERROR("Error initialising SDL_Image : ", SDL_GetError(), '\n');
		assert(false);
		return false;
	}

	m_pWindow = SDL_CreateWindow(
		TITLE,
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		WIDTH, HEIGHT,
		0);

	if (!m_pWindow)
	{
		ns_Util::Logger::LOG_ERROR("Error creating window : ", SDL_GetError(), '\n');
		assert(false);
		return false;
	}

	const Uint32 renderFlags = SDL_RENDERER_ACCELERATED;

	m_pRenderer = SDL_CreateRenderer(m_pWindow, -1, renderFlags);

	if (!m_pRenderer)
	{
		ns_Util::Logger::LOG_ERROR("Error creating renderer : ", SDL_GetError(), '\n');
		assert(false);
		return false;
	}

	if (TTF_Init() < 0)
	{
		ns_Util::Logger::LOG_ERROR("Error initialising SDL_ttf : ", TTF_GetError(), '\n');
		assert(false);
		return false;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) < 0)
	{
		ns_Util::Logger::LOG_ERROR("Error initialising SDL_mixer!\n");
		assert(false);
		return false;
	}
	
	SDL_ShowCursor(SDL_DISABLE);

	m_objectRenderer.init();

	SDL_WarpMouseInWindow(m_pWindow, HALF_WIDTH, HALF_HEIGHT);

	m_objectHandler.init();

	m_weapon.init(R"(.\resources\sprites\weapon\shotgun)", { 11.5f, 3.5f }, 0.4f, 0.16f, 90);

	m_soundEffects.resize(SoundIndex::MAX_SOUNDS);

	m_soundEffects[SoundIndex::SHOTGUN] = new SoundEffect(R"(.\resources\sound\shotgun.wav)");
	
	m_soundEffects[SoundIndex::NPC_PAIN] = new SoundEffect(R"(.\resources\sound\npc_pain.wav)");
	m_soundEffects[SoundIndex::NPC_DEATH] = new SoundEffect(R"(.\resources\sound\npc_death.wav)");
	m_soundEffects[SoundIndex::NPC_SHOT] = new SoundEffect(R"(.\resources\sound\npc_attack.wav)");

	m_soundEffects[SoundIndex::PLAYER_PAIN] = new SoundEffect(R"(.\resources\sound\player_pain.wav)");

	return true;
}

void Game::update(float dt)
{
	const std::string title = "DOOM   FPS : " + std::to_string(1000.0f / dt);
	SDL_SetWindowTitle(m_pWindow, title.c_str());

	if (!m_bPauseGame)
	{
		m_player.update(dt);
		m_raycasting.update(dt);
		m_objectHandler.update(dt);
		m_weapon.update(dt);
	}
}

void Game::run(bool bRunOnMaxFPS)
{
	bRunOnMaxFPS ? runMaxFPS() : runControlledFPS();
}

void Game::preDraw()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	SDL_RenderClear(m_pRenderer);
}

void Game::postDraw()
{
	SDL_RenderPresent(m_pRenderer);
}

void Game::draw()
{
	preDraw();

	m_map.draw();
	m_player.draw();
	m_raycasting.draw();
	m_objectHandler.draw();
	m_objectRenderer.draw();
	m_weapon.draw();

	postDraw();
}

void Game::quit()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	
	IMG_Quit();
	TTF_Quit();
	Mix_CloseAudio();
	SDL_Quit();
	
	m_pWindow = nullptr;
	m_pRenderer = nullptr;
}

void Game::checkEvents()
{
	m_keyboardEvents.clear();
	m_mouseEvents.clear();
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_bQuitGame = true;
			break;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
		{
			m_bPauseGame = !m_bPauseGame;
			break;
		}
		else if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP)
		{
			m_keyboardEvents.push_back(event);
		}
		else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
		{
			m_mouseEvents.push_back(event);
		}
	}
}

void Game::runControlledFPS()
{
	float accumulator{};
	Uint32 lastTicks{};

	while (!m_bQuitGame)
	{
		const Uint32 currTicks = SDL_GetTicks();
		const float elapsedTimeInMs = float(currTicks - lastTicks);

		accumulator += elapsedTimeInMs;

		while (!m_bQuitGame && accumulator >= m_timePerFrameInMs)
		{
			checkEvents();
			update(m_timePerFrameInMs);
			draw();
			accumulator -= m_timePerFrameInMs;
		}

		lastTicks = currTicks;
		//ns_Util::Logger::LOG_INFO("Elapsed time in ms : ", elapsedTimeInMs, ", FPS : ", 1000.0f / elapsedTimeInMs, '\n');
	}
}

void Game::runMaxFPS()
{
	Uint32 lastTicks{};

	while (!m_bQuitGame)
	{
		const Uint32 currTicks = SDL_GetTicks();
		const float elapsedTimeInMs = float(currTicks - lastTicks);

		checkEvents();

		update(elapsedTimeInMs);
		draw();

		lastTicks = currTicks;
		//ns_Util::Logger::LOG_INFO("Elapsed time in ms : ", elapsedTimeInMs, ", FPS : ", 1000.0f / elapsedTimeInMs, '\n');
	}
}