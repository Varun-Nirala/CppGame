#include "engine.h"

#include "Display/displayWindow.h"
#include "Graphics/drawable.h"

#include "Common/constants.h"

#include "Common/logger.h"

Engine::Engine()
    : m_camera(glm::vec3{ 0.0f, 0.0f, 3.0f })
{
    if (kbOrthographicView)
    {
        m_camera.setNear(kORTHOGRAPHIC_NEAR);
        m_camera.setFar(kORTHOGRAPHIC_FAR);
    }
    else
    {
        m_camera.setNear(kPERSPECTIVE_NEAR);
        m_camera.setFar(kPERSPECTIVE_FAR);
    }
}

Engine::~Engine() = default;

bool Engine::init(const char* title, int width, int height, int& hintOpenGlMajorVersion, int& hintOpenGlMinorVersion)
{
    m_enabledBits = GL_COLOR_BUFFER_BIT;
    m_pWindow = std::make_unique<DisplayWindow>(title, width, height, hintOpenGlMajorVersion, hintOpenGlMinorVersion);

    for (size_t i = 0, size = m_drawables.size(); i < size; ++i)
    {
        m_drawables[i]->init();
    }

    if (m_pWindow->inputManager().keyboardInitialized())
    {
        m_pWindow->inputManager().keyboard()->registerOnKeyInputCB(std::bind(&Engine::onKeyInput, this, std::placeholders::_1));
    }

    if (m_pWindow->inputManager().mouseInitialized())
    {
        m_pWindow->inputManager().mouse()->registerOnMouseMoveCB(std::bind(&Engine::onMouseMove, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));
        m_pWindow->inputManager().mouse()->registerOnMouseButtonCB(std::bind(&Engine::onMouseButton, this, std::placeholders::_1));
        m_pWindow->inputManager().mouse()->registerOnWheelScrollCB(std::bind(&Engine::onMouseScroll, this, std::placeholders::_1, std::placeholders::_2));
    }

    return m_pWindow != nullptr;
}

void Engine::addDrawable(Drawable* pdrawable)
{
    m_drawables.push_back(pdrawable);
}

void Engine::startLoop()
{
    gameLoop();
}

void Engine::onKeyInput(const KeyButton& keybutton)
{
    m_camera.onKeyInput(keybutton);
    if (keybutton.action.down && keybutton.keycode == KEY_ESCAPE)
    {
        m_pWindow->onClose();
        return;
    }
    else if (keybutton.action.down && keybutton.keycode == KEY_C)
    {
        if (kbOrthographicView)
        {
            ns_Util::Logger::LOG_INFO("Changing view from Orthographic to Perspective.\n");
        }
        else
        {
            ns_Util::Logger::LOG_INFO("Changing view from Perspective to Orthographic.\n");
        }
        kbOrthographicView = !kbOrthographicView;
    }
}

void Engine::onMouseMove(GLdouble posX, GLdouble posY, GLdouble offsetX, GLdouble offsetY)
{
    m_camera.onCursorMove(posX, posY, offsetX, offsetY);
}

void Engine::onMouseScroll(GLdouble offsetX, GLdouble offsetY)
{
    m_camera.onScroll(offsetX, offsetY);
}

void Engine::onMouseButton(const MouseButton& mousebutton)
{
    m_camera.onMouseButton(mousebutton);
    if (mousebutton.button.left)
    {
        if (mousebutton.action.down)
        {
            ;
        }
        else
        {
            ;
        }
    }
    else if (mousebutton.button.right)
    {
        if (mousebutton.action.down)
        {
            ;
        }
        else
        {
            ;
        }
    }
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
        currTime = m_pWindow->getCurrentTimeInMilliSec();
        update(currTime - lastTime);
        
        preRender();
        
        render();

        postRender();
    }
}

void Engine::update(float elapsedDeltaTimeInMs)
{
    m_camera.update(elapsedDeltaTimeInMs);
    for (size_t i = 0, size = m_drawables.size(); i < size; ++i)
    {
        m_drawables[i]->update(elapsedDeltaTimeInMs);
    }
}

void Engine::preRender()
{
    glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
    glClear(m_enabledBits);
    m_pWindow->preRender();
}

void Engine::render()
{
    for (size_t i = 0, size = m_drawables.size(); i < size; ++i)
    {
        m_drawables[i]->render(m_fovy, m_pWindow->aspectRatio(), m_camera);
    }
}

void Engine::postRender()
{
    m_pWindow->postRender();
}