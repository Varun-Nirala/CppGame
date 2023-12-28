#include "object.h"

#include "helper.h"
#include "logger.h"

#include <cassert>

Object::Object(float radius, sf::Color color, sf::Vector2f position, float mass)
	: m_mass(mass)
{
	m_circle.setFillColor(color);
	m_circle.setPosition(position);
	m_circle.setRadius(radius);
}

void Object::update(const sf::Time& elapsedTime)
{
	// Update the position of the objects
	(void)elapsedTime;
	setPosition(getPosition() + m_velocity);
}


void Object::draw(sf::RenderWindow& window)
{
	// sf::CircleShape circle(m_radius);
	
	window.draw(m_circle);
}

void Object::print() const
{
	std::printf("Radius   : %f\n", getRadius());
	std::printf("Mass     : %f\n", getMass());
	std::printf("Position : %f, %f\n", getPositionX(), getPositionY());
	std::printf("Velocity : %f, %f\n", getVelocityX(), getVelocitY());
}