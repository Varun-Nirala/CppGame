#pragma once

#include <glm/glm.hpp>

enum class PARTICLE_TYPE
{
	SAND,
	WATER,
	FIRE
};

class Particle
{
public:
	Particle(glm::vec2 pos, PARTICLE_TYPE type = PARTICLE_TYPE::SAND);

	void update();
	void render();

private:
	bool			m_bisActive{ true };
	bool			m_bIsStatic{ false };
	glm::vec2		m_position{};
	glm::vec2		m_size{ 2.0f, 2.0f };
	PARTICLE_TYPE	m_type{};
};