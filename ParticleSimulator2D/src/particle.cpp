#include "particle.h"

Transformations::Transformations(glm::vec2 inSize, glm::vec2 inPos, glm::vec2 inScale, float inAngleInDeg, glm::vec3 inRotationVector)
	: size(inSize)
	, position(inPos)
	, scale(inScale)
	, rotationInDeg(inAngleInDeg)
	, rotationVec(inRotationVector)
{
}

Particle::Particle(glm::vec2 pos, glm::vec2 size, PARTICLE_TYPE type)
	: m_type(type)
{
	m_transformations.position = pos;
	m_transformations.size = size;
}

void Particle::update(float elapsedDeltaTimeInSec)
{
	(void)elapsedDeltaTimeInSec;
}

void Particle::render()
{
}
