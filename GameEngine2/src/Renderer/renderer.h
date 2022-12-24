#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

class GameObject;
class RenderBatch;
class SpriteRenderer;

class Renderer
{
public:
	void add(GameObject* pGameObject);

	void render();
private:
	void add(SpriteRenderer* pSpriteRenderer);

private:
	GLint							m_MAX_BATCH_SIZE{ 1000 };
	std::vector<RenderBatch *>		m_batches;
};