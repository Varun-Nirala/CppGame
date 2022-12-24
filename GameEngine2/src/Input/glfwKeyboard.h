#pragma once

#include "Ikeyboard.h"
#include "Display/displayWindow.h"

class GLFW_Keyboard : public Ikeyboard
{
public:
	GLFW_Keyboard(DisplayWindow* pWindow);
	virtual void registerCallbacks() override;

private:
	static void keyInput_CB(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
};