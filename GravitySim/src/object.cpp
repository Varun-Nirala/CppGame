#include "object.h"

#include "helper.h"
#include "logger.h"

#include <cassert>

Object::Object(float radius, sf::Color color, sf::Vector2f position)
{
	m_circle.setFillColor(color);
	m_circle.setPosition(position);
	m_circle.setRadius(radius);
}

void Object::update(const sf::Time& elapsedTime)
{
	// Update the position of the objects
	(void)elapsedTime;
}


void Object::draw(sf::RenderWindow& window)
{
	// sf::CircleShape circle(m_radius);
	
	window.draw(m_circle);
}

void Object::print() const
{
	std::cout << getRadius() << ", (" << getPosX() << ", " << getPosY() << ")\n";
}