#include "particle.h"

Transformations::Transformations(glm::vec2 inSize, glm::vec2 inScale, glm::vec2 inPos, float inAngleInDeg, glm::vec3 inRotationVector)
	: size(inSize)
	, scale(inScale)
	, position(inPos)
	, rotationInDeg(inAngleInDeg)
	, rotationVec(inRotationVector)
{
}

Particle::Particle(PARTICLE_TYPE type, glm::vec2 pos, glm::vec2 size)
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

Particle* Particle::clone() const
{
	return new Particle(*this);
}
