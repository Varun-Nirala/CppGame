#include "Bullet.h"

using namespace AsteroidNS;

Bullet::Bullet(float size, float speed)
	:m_shape(size)
	,m_speed(speed)
{
	assert(speed > 0.0f);
	m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
}

void Bullet::setPosition(const sf::Vector2f &pos)
{
	m_shape.setPosition(pos);
}

void Bullet::setDirection(const sf::Vector2f& dir)
{
	m_direction = dir;
}

void Bullet::update(float secElapsed)
{
	(void)secElapsed;
	m_shape.move(m_direction * m_speed);
}

void Bullet::render(sf::RenderWindow& w) const
{
	w.draw(m_shape);
}