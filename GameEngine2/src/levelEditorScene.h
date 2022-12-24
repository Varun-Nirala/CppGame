#pragma once

#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <cassert>

#include "Renderer/shaderProgram.h"
#include "Input/inputManager.h"

#include "Renderer/texture.h"

#include "scene.h"


class LevelEditorScene : public Scene
{
public:

	void init() override;
	void update(GLfloat dt) override;
};