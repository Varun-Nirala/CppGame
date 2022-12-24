#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "camera.h"

#include "Renderer/renderer.h"

class GameObject;
class Spritesheet;

class Scene
{
public:
	Scene() = default;

	void start();
	void addGameObjectToScene(GameObject *pGameObject);
	virtual void init() = 0;
	virtual void update(GLfloat dt) = 0;

	const Camera& getCamera() const { return m_camera; }
	Camera& getCamera() { return m_camera; }

protected:
	Camera							m_camera;
	bool							m_bIsRunning{ false };
	std::vector<GameObject*>		m_gameObjects;
	Renderer						m_renderer{};
	Spritesheet						*m_pSpriteSheet{};
};