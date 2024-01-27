#include "object.h"

#include "helper.h"
#include "logger.h"

#include <SFML/Graphics.hpp>
#include <cassert>

Object::Object(float radius, sf::Color color, glm::dvec2 position, double mass)
{
	setMass(mass);
	setPosition(position);

	m_circle.setFillColor(color);
	m_circle.setRadius(radius);
	
	// Set origin to mid of circle, by default it is set as local (0, 0).
	m_circle.setOrigin(radius, radius);
}

void Object::update(const sf::Time& elapsedTime)
{
	// Update the position of the objects
	// Velocity gain by the gravitational force of other objects.
	
	ns_Util::Logger::LOG_MSG("Before: ");

	Helper::printVector("\n\tVelocity : ", getVelocity());
	Helper::printVector("\n\tPosition : ", getPosition());
	Helper::printVector("\n\tForce : ", getForce());

	ns_Util::Logger::LOG_MSG("\n\tMass: ", getMass(), ", Elapsed Time: ", elapsedTime.asSeconds(), "s\n");
			
	addVelocity(getForce() / getMass());
	setPosition(getPosition() + getVelocity());

	ns_Util::Logger::LOG_MSG("\nAfter: ");
	
	Helper::printVector("\n\tVelocity : ", getVelocity());
	Helper::printVector("\n\tPosition : ", getPosition());
	Helper::printVector("\n\tForce : ", getForce());
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
	Helper::printVector("Position                   : ", getPosition());
	ns_Util::Logger::LOG_MSG('\n');
	Helper::printVector("Velocity(meter per second) : ", getVelocity());
	ns_Util::Logger::LOG_MSG('\n');
}