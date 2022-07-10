#include "glfwKeyboard.h"

GLFW_Keyboard::GLFW_Keyboard(DisplayWindow* pWindow)
	: Ikeyboard(pWindow)
{}

void GLFW_Keyboard::registerCallbacks()
{
	GLFWwindow* ptrGlfwWindow = static_cast<GLFWwindow*>(m_pWindow->glfwWindow());

	glfwSetKeyCallback(ptrGlfwWindow, keyInput_CB);
}

void GLFW_Keyboard::keyInput_CB(GLFWwindow* pWindow, int key, int scancode, int action, int mods)
{
	DisplayWindow* ptrWindow = DisplayWindow::getDisplayWindow(pWindow);

	KeyButton keybutton;
	keybutton.action.down = action == GLFW_PRESS;
	keybutton.action.up = action == GLFW_RELEASE;

	keybutton.mods = mods;

	keybutton.keycode = key;
	keybutton.scancode = scancode;

	if (ptrWindow->inputManager().keyboardInitialized())
	{
		ptrWindow->inputManager().keyboard()->newKeyEvent(keybutton);
	}

	// pWindow	-	The window that received the event.
	// key		-	The keyboard key that was pressed or released.
	// scancode	-	The system - specific scancode of the key.
	// action	-	GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.Future releases may add more actions.
	// mods		-	Bit field describing which modifier keys were held down.
}

