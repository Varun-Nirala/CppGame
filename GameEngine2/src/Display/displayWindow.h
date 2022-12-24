#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <string>
#include <functional>

#include "Common/constants.h"
#include "Input/inputManager.h"

class Scene;

class DisplayWindow
{
public:
	using KeyinputCallback		= std::function<void(int, int, int, int)>;
	using MousemoveCallback		= std::function<void(double, double)>;
	using MousescrollCallback	= std::function<void(double, double)>;
	using MousebuttonCallback	= std::function<void(int, int, int)>;


public:
	// Singleton
	static DisplayWindow& getInstance();

	const GLFWwindow* glfwWindow() const { return m_pWindow; }
	GLFWwindow* glfwWindow() { return m_pWindow; }

	const InputManager& inputManager() const { return m_inputManager; }
	InputManager& inputManager() { return m_inputManager; }

	int getOpenGLMajorVersion() const;
	int getOpenGLMinorVersion() const;

	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	const std::string& getTitle() const { return m_title; }

	const Scene* getScene() const { return m_pCurrScene; }
	Scene* getScene() { return m_pCurrScene; }

	glm::vec4 getClearColor() const { return m_clearColor; }
	void setClearColor(glm::vec4 color) { m_clearColor = color; }

	void preRender();
	void postRender();

	void loop();

	void changeScene(int newScene);

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
	~DisplayWindow();
	DisplayWindow(const char* title, int width, int height, int hintOpenGlMajorVersion, int hintOpenGlMinorVersion);

private:
	void registerCallbacks();
	void release();
private:
	GLFWwindow							*m_pWindow{};
	std::string							m_title;
	int									m_width{};
	int									m_height{};

	glm::vec4							m_clearColor{0.0f, 0.0f, 0.0f, 1.0f};

	bool								m_bIsOpen{true};

	InputManager						m_inputManager;

	std::vector<KeyinputCallback>		m_keyinputCallbacks;
	std::vector<MousemoveCallback>		m_mousemoveCallback;
	std::vector<MousescrollCallback>	m_mousescrollCallback;
	std::vector<MousebuttonCallback>	m_mousebuttonCallback;

	Scene								*m_pCurrScene{};
};