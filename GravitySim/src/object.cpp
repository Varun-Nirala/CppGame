#include "object.h"

#include "helper.h"
#include "logger.h"

#include <cassert>

Object::Object(float radius, sf::Color color, sf::Vector2f position, float mass)
{
	setMass(mass);
	m_circle.setFillColor(color);
	m_circle.setPosition(position);
	m_circle.setRadius(radius);
}

void Object::update(const sf::Time& elapsedTime)
{
	// Update the position of the objects
	// Velocity gain by the gravitational force of other objects.
	
	Helper::printSfVector("Before Velocity : ", getVelocity());
	Helper::printSfVector(", Before Position : ", getPosition());
	ns_Util::Logger::LOG_MSG('\n');

	addVelocity(getForce() / getMass() * elapsedTime.asSeconds());
	setPosition(getPosition() + getVelocity());

	Helper::printSfVector("After Velocity : ", getVelocity());
	Helper::printSfVector(", After Position : ", getPosition());
	ns_Util::Logger::LOG_MSG('\n');
}


void Object::draw(sf::RenderWindow& window)
{
	// sf::CircleShape circle(m_radius);
	
	window.draw(m_circle);
}

void Object::print() const
{
	ns_Util::Logger::LOG_MSG("Radius(meter)              : ", getRadius());
	ns_Util::Logger::LOG_MSG("Mass(kilogram)             : ", getMass());
	Helper::printSfVector("Position                   : ", getPosition());
	ns_Util::Logger::LOG_MSG('\n');
	Helper::printSfVector("Velocity(meter per second) : ", getVelocity());
	ns_Util::Logger::LOG_MSG('\n');
}