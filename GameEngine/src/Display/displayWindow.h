#pragma once

#include <string>
#include <functional>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "Input/inputManager.h"

class DisplayWindow
{
public:
	using KeyinputCallback		= std::function<void(int, int, int, int)>;
	using MousemoveCallback		= std::function<void(double, double)>;
	using MousescrollCallback	= std::function<void(double, double)>;
	using MousebuttonCallback	= std::function<void(int, int, int)>;
public:
	~DisplayWindow();
	DisplayWindow(const char* title, int width, int height, int& hintOpenGlMajorVersion, int& hintOpenGlMinorVersion);

	const GLFWwindow* glfwWindow() const { return m_pWindow; }
	GLFWwindow* glfwWindow() { return m_pWindow; }

	const InputManager& inputManager() const { return m_inputManager; }
	InputManager& inputManager() { return m_inputManager; }

	void preRender();
	void postRender();

	bool isOpen() const { return m_bIsOpen; }

	float aspectRatio() const;

	void onClose();
	void onRefresh();
	void onResize(int newWidth, int newHeight);
	void onKeyInput(int key, int scancode, int action, int mods);
	void onMouseMove(double posX, double posY);
	void onMouseScroll(double offsetX, double offsetY);
	void onMouseButton(int button, int action, int mods);

	float getCurrentTimeInSec() const;
	float getCurrentTimeInMilliSec() const;

	static DisplayWindow* getDisplayWindow(GLFWwindow* pWindow);

	static void windowClose_CB(GLFWwindow* pWindow);
	static void windowRefresh_CB(GLFWwindow* pWindow);
	static void windowReSize_CB(GLFWwindow* pWindow, int width, int height);

private:
	void registerCallbacks();
	void release();
private:
	GLFWwindow							*m_pWindow{};
	std::string							m_title;
	int									m_width{};
	int									m_height{};

	bool								m_bIsOpen{true};

	InputManager						m_inputManager;

	std::vector<KeyinputCallback>		m_keyinputCallbacks;
	std::vector<MousemoveCallback>		m_mousemoveCallback;
	std::vector<MousescrollCallback>	m_mousescrollCallback;
	std::vector<MousebuttonCallback>	m_mousebuttonCallback;
};