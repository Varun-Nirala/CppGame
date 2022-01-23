#include "Engine.h"
#include "IO\Mouse.h"
#include "IO\Keyboard.h"
#include <iostream>

using namespace std;
using namespace nsEngine;

Engine::Engine()
	: m_pWindow(NULL)
	, m_iWidth(0)
	, m_iHeight(0)
{}

Engine::Engine(int w, int h)
	: m_iWidth(w)
	, m_iHeight(h)
	, m_pWindow(NULL)
{}

Engine::~Engine()
{
	glfwTerminate();
}

bool Engine::Initialize(char *windowTitle)
{
	if (!glfwInit())
	{
		cout << __LINE__ << " ::Error: Initializing glfw." << endl;
		return false;
	}

	if (m_iHeight == 0 && m_iWidth == 0)
	{
		const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

		m_iWidth = mode->width - 100;
		m_iHeight = mode->height - 100;
	}

	m_pWindow = glfwCreateWindow(m_iWidth, m_iHeight, windowTitle, NULL, NULL);
	if (!m_pWindow)
	{
		cout << __LINE__ << " ::Error: creating window." << endl;
		glfwTerminate();
		return false;
	}

	// GLFW initial Setup Start
	glfwMakeContextCurrent(m_pWindow);

	int width, height;
	glfwGetFramebufferSize(m_pWindow, &width, &height);
	glfwSwapInterval(1);

	const GLFWvidmode *pVidMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	int xPos, yPos;
	xPos = (pVidMode->width - m_iWidth) / 2;
	yPos = (pVidMode->height - m_iHeight) / 2;
	glfwSetWindowPos(m_pWindow, xPos, yPos);
	// GLFW initial Setup END

	// Mouse CallBack register
	glfwSetCursorPosCallback(m_pWindow, Mouse::MousePositionCB);
	glfwSetMouseButtonCallback(m_pWindow, Mouse::MouseButtonCB);

	// Keyboard Callback register
	glfwSetKeyCallback(m_pWindow, Keyboard::KeyboardCB);

	// OpenGL Setup Start
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -10, 10);
	glDepthRange(-10, 10);
	glMatrixMode(GL_MODELVIEW);

	glEnable(GL_ALPHA_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// OpenGL Setup End

	return true;
}

bool Engine::SetMousePositionCB(void *funPtr)
{
	return Mouse::getInstance()->SetCustomMousePositionCB(funPtr);
}

bool Engine::SetMouseButtonCB(void *funPtr)
{
	return Mouse::getInstance()->SetCustomMouseButtonCB(funPtr);
}

void Engine::Update()
{
	glfwPollEvents();
}

void Engine::BeginRender()
{
	glClearColor(0, 1, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Engine::EndRender()
{
	glfwSwapBuffers(m_pWindow);
}

bool Engine::IsWindowClosed()
{
	return glfwWindowShouldClose(m_pWindow);
}

int Engine::GetWidth() const
{
	return m_iWidth;
}

int Engine::GetHeight() const
{
	return m_iHeight;
}