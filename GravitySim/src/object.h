#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/Graphics.hpp>
#include <vector>

#include "constant.h"

// Mass in Kilograms.
// Radius in Meters.
// Velocity in Meter per second.
class Object
{
public:
	Object(float radius, sf::Color color, sf::Vector2f position, float mass);

	Object(const Object& other) = delete;
	Object(Object&& other) = delete;

	Object& operator=(const Object& other) = delete;
	Object& operator=(Object&& other) = delete;

	void update(const sf::Time& elapsedTime);
	void draw(sf::RenderWindow& window);

	void setMass(float mass) { m_mass = mass; }
	float getMass() const { return m_mass; }

	void addForce(const sf::Vector2f& force) { m_force += force; }
	const sf::Vector2f& getForce() const { return m_force; }

	void setVelocity(sf::Vector2f vel) { m_velocity = vel; }
	const sf::Vector2f& getVelocity() const { return m_velocity; }

	void addVelocity(sf::Vector2f vel) { m_velocity += vel; }

	void setPosition(sf::Vector2f position) { m_circle.setPosition(position); }
	const sf::Vector2f& getPosition() const { return m_circle.getPosition(); }

	void setRadius(float radius) { m_circle.setRadius(radius); }
	const float getRadius() const { return m_circle.getRadius(); }

	void setFillColor(sf::Color color) { m_circle.setFillColor(color); }
	const sf::Color& getColor() const { return m_circle.getFillColor(); }

	void print() const;

private:
	sf::CircleShape							m_circle;
	sf::Vector2f							m_force{};			// In Newton
	sf::Vector2f							m_velocity{};		// In meter per second
	float									m_mass{ 1.0f };		// In kg
};

#endif //!__TETROMINO_H__