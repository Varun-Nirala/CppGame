#include "game.h"

#include "common/constants.h"
#include "common/logger.h"

Game::Game()
	: m_map(this)
	, m_player(this)
	, m_raycasting(this)
	, m_objectRenderer(this)
{
}

bool Game::init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		ns_Util::Logger::LOG_ERROR("Error initializing SDL : ", SDL_GetError(), '\n');
		assert(false);
		return false;
	}

	const int flags = IMG_INIT_JPG | IMG_INIT_PNG;
	const int initedFlags = IMG_Init(flags);

	if ((flags & initedFlags) != flags)
	{
		ns_Util::Logger::LOG_ERROR("Error initializing SDL_Image : ", SDL_GetError(), '\n');
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
		ns_Util::Logger::LOG_ERROR("Error initializingg SDL_ttf : ", TTF_GetError(), '\n');
		assert(false);
		return false;
	}
	
	SDL_ShowCursor(SDL_DISABLE);

	m_objectRenderer.init();

	return true;
}

void Game::update(float dt)
{
	const std::string title = "DOOM   FPS : " + std::to_string(1000.0f / dt);
	SDL_SetWindowTitle(m_pWindow, title.c_str());

	m_player.update(dt);
	m_raycasting.update(dt);
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

	//m_map.draw();
	//m_player.draw();
	m_raycasting.draw();
	m_objectRenderer.draw();

	postDraw();
}

void Game::quit()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);
	
	IMG_Quit();
	TTF_Quit();
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
		if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
		{
			m_bQuitGame = true;
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