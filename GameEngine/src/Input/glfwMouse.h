#pragma once

#include "Imouse.h"
#include "Display/displayWindow.h"

class GLFW_Mouse : public Imouse
{
public:
	GLFW_Mouse(DisplayWindow* pWindow);
	virtual void registerCallbacks() override;

private:
	static void cursorMove_CB(GLFWwindow* pWindow, GLdouble posX, GLdouble posY);
	static void scroll_CB(GLFWwindow* pWindow, GLdouble offsetX, GLdouble offsetY);
	static void mouseButton_CB(GLFWwindow* pWindow, int button, int action, int mods);
};