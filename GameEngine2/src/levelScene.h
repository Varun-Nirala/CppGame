#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "scene.h"

class LevelScene : public Scene
{
public:
	LevelScene() = default;

	void init() override
	{

	}

	void update(GLfloat dt) override
	{
		(void)dt;
		DisplayWindow::getInstance().setClearColor(glm::vec4{ 0.0f, 1.0f, 0.0f, 1.0f });
	}
};