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
	// Velocity gain by the gravitational force of other objects.
	m_velocity += (m_force / m_mass * elapsedTime.asSeconds());
	setPosition(getPosition() + m_velocity);
}


void Object::draw(sf::RenderWindow& window)
{
	// sf::CircleShape circle(m_radius);
	
	window.draw(m_circle);
}

void Object::print() const
{
	std::printf("Radius(meter)              : %f\n", getRadius());
	std::printf("Mass(kilogram)             : %f\n", getMass());
	std::printf("Position                   : %f, %f\n", getPosition().x, getPosition().y);
	std::printf("Velocity(meter per second) : %f, %f\n", getVelocity().x, getVelocity().y);
}