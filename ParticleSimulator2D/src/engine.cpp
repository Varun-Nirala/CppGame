#include "engine.h"
#include "displayWindow.h"

bool Engine::initDisplayWindow(const char* title, int width, int height, int& hintOpenGlMajorVersion, int& hintOpenGlMinorVersion)
{
    m_pWindow = std::make_unique<DisplayWindow>(title, width, height, hintOpenGlMajorVersion, hintOpenGlMinorVersion);
    return m_pWindow != nullptr;
}

void Engine::startLoop()
{
    gameLoop();
}

void Engine::gameLoop()
{
    while (m_pWindow->isOpen())
    {
        update();
        render();
    }
}

void Engine::update()
{
}

void Engine::render()
{
}
