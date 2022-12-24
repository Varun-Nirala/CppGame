#include <glad/glad.h>
#include "displayWindow.h"
#include "Common/logger.h"
#include "Common/debugOpenGL.h"
#include "Common/constants.h"

#include "levelScene.h"
#include "levelEditorScene.h"

#define DEBUG_OPENGL

DisplayWindow& DisplayWindow::getInstance()
{
	int major = OPENGL_MAJOR_VERSION;
	int minor = OPENGL_MINOR_VERSION;
	static DisplayWindow displayWindow(TITLE, WIDTH, HEIGHT, major, minor);
	return displayWindow;
}


DisplayWindow::~DisplayWindow()
{
	release();
}

DisplayWindow::DisplayWindow(const char* title, int width, int height, int hintOpenGlMajorVersion, int hintOpenGlMinorVersion)
	: m_width(width)
	, m_height(height)
	, m_title(title)
	, m_inputManager(true, true)
{
	using ns_Util::Logger;

	if (glfwInit() == GLFW_FALSE)
	{
		Logger::LOG_ERROR("Failed to init GLFW.\n");
		assert(false);
		return;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, hintOpenGlMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, hintOpenGlMinorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef DEBUG_OPENGL
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

	if (!m_pWindow)
	{
		Logger::LOG_ERROR("Failed to create GLFW window.\n");
		assert(false);
		return;
	}
	Logger::LOG_MSG("GLFW window created successfully.\n");
	glfwMakeContextCurrent(m_pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::LOG_ERROR("Failed to init GLAD.\n");
		assert(false);
		return;
	}
	Logger::LOG_MSG("GLAD initialized successfully.\n");

#ifdef DEBUG_OPENGL
	DebugOpenGL::init();
#endif

	if (!m_inputManager.init(this))
	{
		Logger::LOG_ERROR("Failed to init input manager.\n");
		assert(false);
		return;
	}

	registerCallbacks();

	glfwGetFramebufferSize(m_pWindow, &m_width, &m_height);
	glViewport(0, 0, m_width, m_height);
	
	WIDTH = m_width;
	HEIGHT = m_height;
	
	glfwSetCursorPos(m_pWindow, m_width / 2.0f, m_height / 2.0f);
}

int DisplayWindow::getOpenGLMajorVersion() const
{
	int version{};
	glGetIntegerv(GL_MAJOR_VERSION, &version);
	return version;
}

int DisplayWindow::getOpenGLMinorVersion() const
{
	int version{};
	glGetIntegerv(GL_MINOR_VERSION, &version);
	return version;
}

void DisplayWindow::preRender()
{
	glfwPollEvents();
}

void DisplayWindow::postRender()
{
	glfwSwapBuffers(m_pWindow);
}

void DisplayWindow::loop()
{
	GLfloat beginTime = getCurrentTimeInSec();
	GLfloat endTime{};
	GLfloat dt{};

	changeScene(0);

	while (!glfwWindowShouldClose(m_pWindow))
	{
		preRender();

		glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);

		glClear(GL_COLOR_BUFFER_BIT);

		m_pCurrScene->update(dt);

		postRender();

		endTime = getCurrentTimeInSec();
		dt = endTime - beginTime;
		beginTime = endTime;
	}
}

void DisplayWindow::changeScene(int newScene)
{
	switch (newScene)
	{
		case 0:
			m_pCurrScene = new LevelEditorScene();
			m_pCurrScene->init();
			m_pCurrScene->start();
			break;

		case 1:
			m_pCurrScene = new LevelScene();
			m_pCurrScene->init();
			m_pCurrScene->start();
			break;

		default:
			ns_Util::Logger::LOG_ERROR("Unkown Scene : ", newScene, '\n');
			assert(false);
	}
}

float DisplayWindow::aspectRatio() const
{
    return m_width / (float)m_height;
}

void DisplayWindow::onClose()
{
	glfwSetWindowShouldClose(m_pWindow, true);
	m_bIsOpen = false;
}

void DisplayWindow::onRefresh()
{
}

void DisplayWindow::onResize(int newWidth, int newHeight)
{
	m_width = newWidth;
	m_height = newHeight;

	WIDTH = m_width;
	HEIGHT = m_height;

	glViewport(0, 0, m_width, m_height);
}

void DisplayWindow::onKeyInput(int key, int scancode, int action, int mods)
{
	for (auto& cb : m_keyinputCallbacks)
	{
		cb(key, scancode, action, mods);
	}
	if (key == GLFW_KEY_ESCAPE)
	{
		onClose();
	}
}

void DisplayWindow::onMouseMove(double posX, double posY)
{
	for (auto& cb : m_mousemoveCallback)
	{
		cb(posX, posY);
	}
}

void DisplayWindow::onMouseScroll(double offsetX, double offsetY)
{
	for (auto& cb : m_mousescrollCallback)
	{
		cb(offsetX, offsetY);
	}
}

void DisplayWindow::onMouseButton(int button, int action, int mods)
{
	for (auto& cb : m_mousebuttonCallback)
	{
		cb(button, action, mods);
	}
}

float DisplayWindow::getCurrentTimeInSec() const
{
	return (float)glfwGetTime();
}

float DisplayWindow::getCurrentTimeInMilliSec() const
{
	return getCurrentTimeInSec() * 1000.0f;
}

DisplayWindow* DisplayWindow::getDisplayWindow(GLFWwindow* pWindow)
{
	return static_cast<DisplayWindow*>(glfwGetWindowUserPointer(pWindow));
}

void DisplayWindow::windowClose_CB(GLFWwindow* pWindow)
{
	DisplayWindow* pDisplayWindow = getDisplayWindow(pWindow);
	if (pDisplayWindow)
	{
		pDisplayWindow->onClose();
	}
}

void DisplayWindow::windowRefresh_CB(GLFWwindow* pWindow)
{
	DisplayWindow* pDisplayWindow = getDisplayWindow(pWindow);
	if (pDisplayWindow)
	{
		pDisplayWindow->onRefresh();
	}
}

void DisplayWindow::windowReSize_CB(GLFWwindow* pWindow, int width, int height)
{
	DisplayWindow* pDisplayWindow = getDisplayWindow(pWindow);
	if (pDisplayWindow)
	{
		pDisplayWindow->onResize(width, height);
	}
}

void DisplayWindow::registerCallbacks()
{
	// Register this pointer so that we can retrieve it in our static methods
	glfwSetWindowUserPointer(m_pWindow, this);

	glfwSetFramebufferSizeCallback(m_pWindow, windowReSize_CB);
	glfwSetWindowRefreshCallback(m_pWindow, windowRefresh_CB);
	glfwSetWindowCloseCallback(m_pWindow, windowClose_CB);
}

void DisplayWindow::release()
{
	glfwDestroyWindow(m_pWindow);
	glfwTerminate();
	m_inputManager.release();
}
