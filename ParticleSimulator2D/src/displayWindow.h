#pragma once

#include <string>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class DisplayWindow
{
public:
	~DisplayWindow() { release(); }
	DisplayWindow(const char* title, int width, int height, int &hintOpenGlMajorVersion, int &hintOpenGlMinorVersion);

	const GLFWwindow* glfwWindow() const { return m_pWindow; }
	GLFWwindow* glfwWindow() { return m_pWindow; }

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
	static void keyinput_CB(GLFWwindow* pWindow, int key, int scancode, int action, int mods);
	static void mouseMove_CB(GLFWwindow* pWindow, double posX, double posY);
	static void mouseScroll_CB(GLFWwindow* pWindow, double offsetX, double offsetY);
	static void mouseButton_CB(GLFWwindow* pWindow, int button, int action, int mods);

private:
	void registerCallbacks();
	void release();
private:
	GLFWwindow				*m_pWindow{};
	std::string				m_title;
	int						m_width{};
	int						m_height{};
	bool					m_bIsOpen{true};

};