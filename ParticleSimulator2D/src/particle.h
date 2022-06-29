#pragma once

#include <glm/glm.hpp>

enum class PARTICLE_TYPE
{
	SAND,
	WATER,
	FIRE
};

struct Transformations
{
	glm::vec2		size{};
	glm::vec2		position{};
	glm::vec2		scale{ 1.0f };
	glm::vec3		rotationVec{ 0.0f, 0.0f, 1.0f };
	float			rotationInDeg{};

	Transformations(
		glm::vec2 inSize = glm::vec2{2.0f}, 
		glm::vec2 inPos = glm::vec2{0.0f}, 
		glm::vec2 inScale = glm::vec2{1.0f}, 
		float inAngleInDeg = 0.0f, 
		glm::vec3 inRotationVector = glm::vec3{0.0f, 0.0f, 1.0f});
};

class Particle
{
public:
	Particle(glm::vec2 pos = glm::vec2{}, glm::vec2 size = glm::vec2{ 1.0f, 1.0f }, PARTICLE_TYPE type = PARTICLE_TYPE::SAND);

	void update(float elapsedDeltaTimeInSec);
	void render();

	const Transformations& transformations() const { return m_transformations; }
	Transformations& transformations() { return m_transformations; }

private:
	bool				m_bisActive{ true };
	bool				m_bIsStatic{ false };
	PARTICLE_TYPE		m_type{};
	Transformations		m_transformations{};
};