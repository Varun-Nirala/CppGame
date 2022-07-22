#pragma once

#include <memory>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>

#include "Input/Ikeyboard.h"
#include "Input/Imouse.h"

#include "Camera/camera.h"

class DisplayWindow;
class Drawable;

class Engine
{
public:
	Engine();
	~Engine();

	bool init(const char* title, int width, int height, int& hintOpenGlMajorVersion, int& hintOpenGlMinorVersion);

	void addDrawable(Drawable* pdrawable);

	void startLoop();

	void onKeyInput(const KeyButton& keybutton);
	void onMouseMove(GLdouble posX, GLdouble posY, GLdouble offsetX, GLdouble offsetY);
	void onMouseScroll(GLdouble offsetX, GLdouble offsetY);
	void onMouseButton(const MouseButton& mousebutton);

	void enableDepthTest();
	void enableStencilTest();
	void enableBlendFunc();

	bool isDepthTestEnable() const;
	bool isStencilTestEnable() const;
	bool isBlendFuncEnable() const;

private:
	void gameLoop();
	void update(float elapsedDeltaTimeInSec);
	
	void render();
	void preRender();
	void postRender();
private:
	std::unique_ptr<DisplayWindow>			m_pWindow;
	glm::vec4								m_clearColor{ 0.2f, 0.3f, 0.3f, 1.0f };
	GLuint									m_enabledBits{};
	std::vector<Drawable*>					m_drawables;
	Camera									m_camera;
};