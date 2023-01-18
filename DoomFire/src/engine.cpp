#include "engine.h"
#include "common/logger.h"

Engine::Engine()
	: m_fire(m_width, m_height, m_pixelWidth, m_pixelHeight)
{}

bool Engine::setup()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		ns_Util::Logger::LOG_ERROR("Error initialising SDL : ", SDL_GetError(), '\n');
		assert(false);
		return false;
	}

	m_pWindow = SDL_CreateWindow(
		m_title.c_str(),
		SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width * m_pixelWidth, m_height * m_pixelHeight,
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

	return true;
}

void Engine::teardown()
{
	SDL_DestroyRenderer(m_pRenderer);
	SDL_DestroyWindow(m_pWindow);

	SDL_Quit();

	m_pWindow = nullptr;
	m_pRenderer = nullptr;
}

void Engine::run(bool bRunOnMaxFPS)
{
	m_fire.start();
	bRunOnMaxFPS ? runMaxFPS() : runControlledFPS();
}

void Engine::runControlledFPS()
{
	float accumulator{};
	Uint32 lastTicks{};

	while (!m_bQuit)
	{
		const Uint32 currTicks = SDL_GetTicks();
		const float elapsedTimeInMs = float(currTicks - lastTicks);

		accumulator += elapsedTimeInMs;

		while (!m_bQuit && accumulator >= m_timePerFrameInMs)
		{
			checkEvents();
			update(m_timePerFrameInMs);
			render();
			accumulator -= m_timePerFrameInMs;
		}

		lastTicks = currTicks;
		//ns_Util::Logger::LOG_INFO("Elapsed time in ms : ", elapsedTimeInMs, ", FPS : ", 1000.0f / elapsedTimeInMs, '\n');
	}
}

void Engine::runMaxFPS()
{
	Uint32 lastTicks{};

	while (!m_bQuit)
	{
		const Uint32 currTicks = SDL_GetTicks();
		const float elapsedTimeInMs = float(currTicks - lastTicks);

		checkEvents();

		update(elapsedTimeInMs);
		render();

		lastTicks = currTicks;
		//ns_Util::Logger::LOG_INFO("Elapsed time in ms : ", elapsedTimeInMs, ", FPS : ", 1000.0f / elapsedTimeInMs, '\n');
	}
}

void Engine::checkEvents()
{
	SDL_Event event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT || event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			m_bQuit = true;
			break;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
		{
			m_bPause = !m_bPause;
			break;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_a)
		{
			m_fire.stop();
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
		{
			m_fire.start();
		}
	}
}

void Engine::update(float dt)
{
	const std::string title = "DOOM   FPS : " + std::to_string(1000.0f / dt);
	SDL_SetWindowTitle(m_pWindow, title.c_str());

	if (!m_bPause)
	{
		m_fire.update(dt);
	}
}

void Engine::render()
{
	SDL_SetRenderDrawColor(m_pRenderer, m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
	SDL_RenderClear(m_pRenderer);

	m_fire.render(m_pRenderer);

	SDL_RenderPresent(m_pRenderer);
}