#include "keyboard.h"
#include <iostream>

using namespace std;
using namespace nsEngine;

// static member Start
Keyboard* Keyboard::m_pInstance = NULL;
bool Keyboard::m_keysDown[GLFW_KEY_LAST] = { false };
bool Keyboard::m_keysUp[GLFW_KEY_LAST] = { false };
bool Keyboard::m_keys[GLFW_KEY_LAST] = { false };
void(*Keyboard::FP_KeyboardCB)(GLFWwindow *, int, int, int, int) = NULL;

Keyboard* Keyboard::getInstance()
{
	if (!m_pInstance)
	{
		m_pInstance = new Keyboard();
	}
	return m_pInstance;
}

void Keyboard::KeyboardCB(GLFWwindow *pWindow, int key, int scanCode, int action, int mods)
{
	if (FP_KeyboardCB)
	{
		FP_KeyboardCB(pWindow, key, scanCode, action, mods);
	}
	else
	{
		if (key < 0)
		{
			cout << __LINE__ << " ::Error: Not a valid key" << endl;
			return;
		}
		// Default implementation, Any key handling
		if (action != GLFW_RELEASE && m_keys[key] == false)
		{
			m_keysDown[key] = true;
			m_keysUp[key] = false;
		}
		else if (action == GLFW_RELEASE && m_keys[key] == false)
		{
			m_keysDown[key] = false;
			m_keysUp[key] = true;
		}

		m_keys[key] = GLFW_RELEASE != action;
	}
}
// static member End

bool Keyboard::SetCustomKeyboardCB(void *funPtr)
{
	FP_KeyboardCB = static_cast<decltype(FP_KeyboardCB)>(funPtr);

	if (!FP_KeyboardCB)
	{
		cout << __LINE__ << " ::Error: Function callback doesn't match the required format: void(*)(GLFWwindow *, int, int, int, int)" << endl;
		return false;
	}
	return true;
}

bool Keyboard::KeyDown(int key)
{
	bool state = m_keysDown[key];
	m_keysDown[key] = false;
	return state;
}

bool Keyboard::KeyUp(int key)
{
	bool state = m_keysUp[key];
	m_keysUp[key] = false;
	return state;
}

bool Keyboard::Key(int key)
{
	return m_keys[key];
}