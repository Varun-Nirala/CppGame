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
		glm::vec2 inScale = glm::vec2{ 1.0f },
		glm::vec2 inPos = glm::vec2{0.0f}, 
		float inAngleInDeg = 0.0f, 
		glm::vec3 inRotationVector = glm::vec3{0.0f, 0.0f, 1.0f});
};

class Particle
{
public:
	Particle(PARTICLE_TYPE type, glm::vec2 pos = glm::vec2{}, glm::vec2 size = glm::vec2{ 1.0f, 1.0f });

	void update(float elapsedDeltaTimeInSec);
	void render();

	void setCanUpdate(bool val) { m_bCanUpdate = val; }
	void setActive(bool val) { m_bisActive = val; }

	bool canUpdate() const { return m_bCanUpdate; }
	bool isActive() const { return m_bisActive; }

	PARTICLE_TYPE type() const { return m_type; }

	const Transformations& transformations() const { return m_transformations; }
	Transformations& transformations() { return m_transformations; }

	Particle* clone() const;

private:
	bool				m_bisActive{ true };
	bool				m_bCanUpdate{ true };
	PARTICLE_TYPE		m_type{};
	Transformations		m_transformations{};
};