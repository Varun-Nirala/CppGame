#include "glfwMouse.h"

GLFW_Mouse::GLFW_Mouse(DisplayWindow* pWindow)
	: Imouse(pWindow)
{}

void GLFW_Mouse::registerCallbacks()
{
	GLFWwindow* ptrGlfwWindow = static_cast<GLFWwindow*>(m_pWindow->glfwWindow());

	glfwSetCursorPosCallback(ptrGlfwWindow, cursorMove_CB);
	glfwSetScrollCallback(ptrGlfwWindow, scroll_CB);
	glfwSetMouseButtonCallback(ptrGlfwWindow, mouseButton_CB);
}

void GLFW_Mouse::cursorMove_CB(GLFWwindow* pWindow, GLdouble posX, GLdouble posY)
{
	DisplayWindow* ptrWindow = DisplayWindow::getDisplayWindow(pWindow);

	if (ptrWindow->inputManager().mouseInitialized())
	{
		ptrWindow->inputManager().mouse()->newMoveEvent(posX, posY);
	}
}

void GLFW_Mouse::scroll_CB(GLFWwindow* pWindow, GLdouble offsetX, GLdouble offsetY)
{
	DisplayWindow* ptrWindow = DisplayWindow::getDisplayWindow(pWindow);

	if (ptrWindow->inputManager().mouseInitialized())
	{
		ptrWindow->inputManager().mouse()->newScrollEvent(offsetX, offsetY);
	}
}

void GLFW_Mouse::mouseButton_CB(GLFWwindow* pWindow, int button, int action, int mods)
{
	DisplayWindow* ptrWindow = DisplayWindow::getDisplayWindow(pWindow);

	MouseButton mousebutton;

	glfwGetCursorPos(ptrWindow->glfwWindow(), &mousebutton.x, &mousebutton.y);

	mousebutton.action.down = action == GLFW_PRESS;
	mousebutton.action.up = action == GLFW_RELEASE;

	mousebutton.button.left = button == GLFW_MOUSE_BUTTON_LEFT;
	mousebutton.button.right = button == GLFW_MOUSE_BUTTON_RIGHT;
	mousebutton.button.middle = button == GLFW_MOUSE_BUTTON_MIDDLE;

	mousebutton.button.id = button;

	mousebutton.mods = mods;

	if (ptrWindow->inputManager().mouseInitialized())
	{
		ptrWindow->inputManager().mouse()->newButtonEvent(mousebutton);
	}

	// pWindow	-	The window that received the event.
	// button	-	The mouse button. GLFW_MOUSE_BUTTON_1 to GLFW_MOUSE_BUTTON_8,
	//				GLFW_MOUSE_BUTTON_8 = GLFW_MOUSE_BUTTON_LAST,
	//				GLFW_MOUSE_BUTTON_1 = GLFW_MOUSE_BUTTON_LEFT,
	//				GLFW_MOUSE_BUTTON_2 = GLFW_MOUSE_BUTTON_RIGHT,
	//				GLFW_MOUSE_BUTTON_3 = GLFW_MOUSE_BUTTON_MIDDLE,
	// action	-	GLFW_PRESS, GLFW_RELEASE or GLFW_REPEAT.Future releases may add more actions.
	// mods		-	Bit field describing which modifier keys were held down.
}