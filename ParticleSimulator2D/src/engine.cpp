#include "engine.h"

#include "particleManager.h"
#include "displayWindow.h"

Engine::Engine() = default;
Engine::~Engine() = default;

bool Engine::init(const char* title, int width, int height, int& hintOpenGlMajorVersion, int& hintOpenGlMinorVersion)
{
    m_enabledBits = GL_COLOR_BUFFER_BIT;
    m_pWindow = std::make_unique<DisplayWindow>(title, width, height, hintOpenGlMajorVersion, hintOpenGlMinorVersion);
    m_particleManager = std::make_unique<ParticleManager>(PARTICLE_TYPE::WATER, width, height, glm::vec2{ 0.0f, 0.0f });
    return m_pWindow != nullptr;
}

void Engine::startLoop()
{
    m_pWindow->registerKeyinputCallback(std::bind(&Engine::onKeyInput, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
    m_pWindow->registerMousemoveCallback(std::bind(&Engine::onMouseMove, this, std::placeholders::_1, std::placeholders::_2));
    m_pWindow->registerMousescrollCallback(std::bind(&Engine::onMouseScroll, this, std::placeholders::_1, std::placeholders::_2));
    m_pWindow->registerMousebuttonCallback(std::bind(&Engine::onMouseButton, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
    gameLoop();
}

void Engine::onKeyInput(int key, int scancode, int action, int mods)
{
    (void)key;
    (void)scancode;
    (void)action;
    (void)mods;
}

void Engine::onMouseMove(double posX, double posY)
{
    (void)posX;
    (void)posY;
}

void Engine::onMouseScroll(double offsetX, double offsetY)
{
    (void)offsetX;
    (void)offsetY;
}

void Engine::onMouseButton(int button, int action, int mods)
{
    (void)button;
    (void)action;
    (void)mods;
}

void Engine::enableDepthTest()
{
    glEnable(GL_DEPTH_TEST);
    m_enabledBits |= GL_DEPTH_BUFFER_BIT;
}

void Engine::enableStencilTest()
{
    glEnable(GL_STENCIL_TEST);
    m_enabledBits |= GL_STENCIL_BUFFER_BIT;
}

void Engine::enableBlendFunc()
{
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    //m_enabledBits |= GL_BLEND;			// not required
}

bool Engine::isDepthTestEnable() const
{
    return glIsEnabled(GL_DEPTH_TEST) == GL_TRUE;
}

bool Engine::isStencilTestEnable() const
{
    return glIsEnabled(GL_STENCIL_TEST) == GL_TRUE;
}

bool Engine::isBlendFuncEnable() const
{
    return glIsEnabled(GL_BLEND) == GL_TRUE;
}

void Engine::gameLoop()
{
    GLfloat lastTime = m_pWindow->getCurrentTimeInSec();
    GLfloat currTime{};
    while (m_pWindow->isOpen())
    {
        currTime = m_pWindow->getCurrentTimeInSec();
        update(currTime - lastTime);
        
        preRender();
        
        render();

        postRender();
    }
}

void Engine::update(float elapsedDeltaTimeInSec)
{
    m_particleManager->update(elapsedDeltaTimeInSec);
}

void Engine::preRender()
{
    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    glClear(m_enabledBits);
    m_pWindow->preRender();
}

void Engine::render()
{
    m_particleManager->render();
}

void Engine::postRender()
{
    m_pWindow->postRender();
}