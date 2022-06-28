#include "particle.h"

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
