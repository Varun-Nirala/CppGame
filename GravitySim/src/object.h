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

	void setMassInKg(float mass) { m_mass = mass; }
	float getMassInKg() const { return m_mass; }

	void setVelocityInMPS(sf::Vector2f vel) { m_velocity = vel; }
	void setVelocityInMPS(float velX, float velY) { m_velocity.x = velX; m_velocity.y = velY; }
	const sf::Vector2f& getVelocityInMPS() const { return m_velocity; }
	float getVelocityInMPSX() const { return m_velocity.x; }
	float getVelocityInMPSY() const { return m_velocity.y; }

	void addVelocityInMPS(sf::Vector2f vel) { m_velocity += vel; }

	void setPosition(sf::Vector2f position) { m_circle.setPosition(position); }
	void setPosition(float posX, float posY) { m_circle.setPosition(posX, posY); }
	const sf::Vector2f& getPosition() const { return m_circle.getPosition(); }
	float getPositionX() const { return m_circle.getPosition().x; }
	float getPositionY() const { return m_circle.getPosition().y; }

	void setRadiusInMeter(float radius) { m_circle.setRadius(radius); }
	const float getRadiusInMeter() const { return m_circle.getRadius(); }

	void setFillColor(sf::Color color) { m_circle.setFillColor(color); }
	const sf::Color& getColor() const { return m_circle.getFillColor(); }

	void print() const;

private:
	sf::CircleShape							m_circle;
	sf::Vector2f							m_velocity{};		// In meter per second
	float									m_mass{ 1.0f };		// In kg
};

#endif //!__TETROMINO_H__