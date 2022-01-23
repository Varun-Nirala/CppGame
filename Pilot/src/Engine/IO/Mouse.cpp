#include "Mouse.h"
#include <iostream>

using namespace nsEngine;
using namespace std;

//static member Start
Mouse* Mouse::m_pInstance = NULL;
void(*Mouse::FP_MousePositionCB)(GLFWwindow *, double, double) = NULL;
void(*Mouse::FP_MouseButtonCB)(GLFWwindow *, int, int, int) = NULL;
double Mouse::m_dPosX = 0;
double Mouse::m_dPosY = 0;
bool Mouse::m_button[MAX_BUTTON] = { false };
bool Mouse::m_buttonUp[MAX_BUTTON] = { false };
bool Mouse::m_buttonDown[MAX_BUTTON] = { false };

Mouse* Mouse::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Mouse();
	}
	return m_pInstance;
}

void Mouse::MousePositionCB(GLFWwindow *pWindow, double x, double y)
{
	if (FP_MousePositionCB)
	{
		FP_MousePositionCB(pWindow, x, y);
	}
	else
	{
		// Default implementation
		int w, h;
		glfwGetFramebufferSize(pWindow, &w, &h);
		// We need height cause Mouse position we get in x and y is from top left,
		// but OpenGl view port start from 0,0 as botton left

		m_dPosX = x;
		m_dPosY = w - y;
	}
}

void Mouse::MouseButtonCB(GLFWwindow *pWindow, int button, int action, int mods)
{
	if (FP_MouseButtonCB)
	{
		FP_MouseButtonCB(pWindow, button, action, mods);
	}
	else
	{
		if (button < 0)
		{
			cout << __LINE__ << " ::Error: Not a valid button" << endl;
			return;
		}
		// Default implementation, handling only left, right and mid button of mouse
		if (button <= GLFW_MOUSE_BUTTON_MIDDLE)
		{
			if (action != GLFW_RELEASE && m_button[button] == false)
			{
				m_buttonDown[button] = true;
				m_buttonUp[button] = false;
			}
			else if (action == GLFW_RELEASE && m_button[button] == false)
			{
				m_buttonDown[button] = false;
				m_buttonUp[button] = true;
			}

			m_button[button] = action != GLFW_RELEASE;
		}
		else
		{
			cout << __LINE__ << " ::Error: No handling for this key" << endl;
		}
	}
}
//static Members End

double Mouse::GetPosX()
{
	return m_dPosX;
}

double Mouse::GetPosY()
{
	return m_dPosY;
}

bool Mouse::ButtonDown(int button)
{
	bool state = m_buttonDown[button];	// maintain state
	m_buttonDown[button] = false;		// clear it
	return state;
}

bool Mouse::ButtonUp(int button)
{
	bool state = m_buttonUp[button];	// maintain state
	m_buttonUp[button] = false;			// clear it
	return state;
}

bool Mouse::Button(int button)
{
	return m_button[button];
}

bool Mouse::SetCustomMousePositionCB(void *funPtr)
{
	FP_MousePositionCB = static_cast<decltype(FP_MousePositionCB)>(funPtr);

	if (!FP_MousePositionCB)
	{
		cout << __LINE__ << " ::Error: Function callback doesn't match the required format: void(*)(GLFWwindow *, double, double)" << endl;
		return false;
	}
	return true;
}

bool Mouse::SetCustomMouseButtonCB(void *funPtr)
{
	FP_MouseButtonCB = static_cast<decltype(FP_MouseButtonCB)>(funPtr);

	if (!FP_MouseButtonCB)
	{
		cout << __LINE__ << " ::Error: Function callback doesn't match the required format: void(*)(GLFWwindow *, int, int, int)" << endl;
		return false;
	}
	return true;
}