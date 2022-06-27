#pragma once

#include "particle.h"
#include "grid.h"

class ParticleManager
{
public:
	~ParticleManager() { release(); }
	ParticleManager(int windowWidth, int windowHeight, glm::vec2 startPos = { 0.0f, 0.0f });

	void update();
	void render();

private:
	void release();

private:
	Grid			m_grid;
};