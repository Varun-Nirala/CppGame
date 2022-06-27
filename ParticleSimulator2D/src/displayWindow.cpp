#include <glad/glad.h>
#include "displayWindow.h"
#include "Common/logger.h"

DisplayWindow::DisplayWindow(const char* title, int width, int height, int &hintOpenGlMajorVersion, int &hintOpenGlMinorVersion)
    : m_width(width)
    , m_height(height)
    , m_title(title)
{
    using ns_Util::Logger;

    if (glfwInit() == GLFW_FALSE)
    {
        Logger::LOG_ERROR("Failed to init GLFW.\n");
        return;
    }

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, hintOpenGlMajorVersion);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, hintOpenGlMinorVersion);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	hintOpenGlMajorVersion = 0;
	hintOpenGlMinorVersion = 0;

#ifdef DEBUG_OPENGL
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, true);
#endif

	m_pWindow = glfwCreateWindow(m_width, m_height, m_title.c_str(), NULL, NULL);

	if (!m_pWindow)
	{
		Logger::LOG_ERROR("Failed to create GLFW window.\n");
		return;
	}
	Logger::LOG_MSG("GLFW window created successfully.\n");
	glfwMakeContextCurrent(m_pWindow);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		Logger::LOG_ERROR("Failed to init GLAD.\n");
	}
	Logger::LOG_MSG("GLAD initialized successfully.\n");

#ifdef DEBUG_OPENGL
	DebugOpenGL::init();
#endif

	glGetIntegerv(GL_MAJOR_VERSION, &hintOpenGlMajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &hintOpenGlMinorVersion);
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

	glViewport(0, 0, m_width, m_height);
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
}
