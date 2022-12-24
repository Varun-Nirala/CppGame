#include "inputManager.h"
#include "Common/logger.h"
#include "Common/constants.h"
#include "glfwMouse.h"
#include "glfwKeyboard.h"

InputManager::InputManager(bool bInitKeyboard, bool bInitMouse)
{
	m_bInitKeyboard = bInitKeyboard;
	m_bInitMouse = bInitMouse;
}

bool InputManager::init(DisplayWindow* pWindow)
{
	if (m_bInitKeyboard)
	{
		if ((m_pKeyboard = createKeyboard(pWindow)) == nullptr)
		{
			ns_Util::Logger::LOG_ERROR("Failed to create Keyboard.\n");
			return false;
		}
		m_pKeyboard->registerCallbacks();
	}
	if (m_bInitMouse)
	{
		if ((m_pMouse = createMouse(pWindow)) == nullptr)
		{
			ns_Util::Logger::LOG_ERROR("Failed to create Mouse.\n");
			return false;
		}
		m_pMouse->registerCallbacks();
	}
	return true;
}

void InputManager::endFrame()
{
	if (m_pKeyboard)
	{
		m_pKeyboard->endFrame();
	}
	if (m_pMouse)
	{
		m_pMouse->endFrame();
	}
}

void InputManager::release()
{
	delete m_pKeyboard;
	m_pKeyboard = nullptr;

	delete m_pMouse;
	m_pMouse = nullptr;
	m_bInitKeyboard = m_bInitMouse = false;
}

void InputManager::print(const std::string& prefix) const
{
	ns_Util::Logger::LOG_MSG(prefix, "  Key Initialized   : ", keyboardInitialized() ? "True" : "False", '\n');
	ns_Util::Logger::LOG_MSG(prefix, "  Mouse Initialized : ", mouseInitialized() ? "True" : "False", '\n');
}

Imouse* InputManager::createMouse(DisplayWindow* pWindow)
{
	return new GLFW_Mouse(pWindow);
}

Ikeyboard* InputManager::createKeyboard(DisplayWindow* pWindow)
{
	return new GLFW_Keyboard(pWindow);
}