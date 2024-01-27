#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/Graphics.hpp>
#include <vector>
#include <glm/vec2.hpp>

#include "constant.h"

// Mass in Kilograms.
// Radius in Meters.
// Velocity in Meter per second.
class Object
{
public:
	Object(float radius, sf::Color color, glm::dvec2 position, double mass);

	Object(const Object& other) = delete;
	Object(Object&& other) = delete;

	Object& operator=(const Object& other) = delete;
	Object& operator=(Object&& other) = delete;

	void update(const sf::Time& elapsedTime);
	void draw(sf::RenderWindow& window);

	void setMass(const double mass) { m_mass = mass * MASS_SCALER; }
	double getMass() const { return m_mass; }

	void addForce(const glm::dvec2& force) { m_force += force; }
	void addForce(const double xForce, const double yForce) { m_force.x += xForce; m_force.y += yForce; }
	const glm::dvec2& getForce() const { return m_force; }

	void setVelocity(const glm::dvec2 &vel) { m_velocity = vel; }
	void setVelocity(const double xVel, const double yVel) { m_velocity.x = xVel; m_velocity.y = yVel; }
	const glm::dvec2& getVelocity() const { return m_velocity; }

	void addVelocity(const glm::dvec2&vel) { m_velocity += vel; }
	void addVelocity(const double xVel, const double yVel) { m_velocity.x += xVel; m_velocity.y += yVel; }

	void setPosition(const glm::dvec2& position) { setPosition(position.x, position.y); }
	void setPosition(const double xPos, const double yPos) { m_position.x = xPos; m_position.y = yPos; m_circle.setPosition((float)m_position.x, (float)m_position.y); }
	const glm::dvec2& getPosition() const { return m_position; }

	void setRadius(const float radius) { m_circle.setRadius(radius); }
	const float getRadius() const { return m_circle.getRadius(); }

	void setFillColor(const sf::Color &color) { m_circle.setFillColor(color); }
	const sf::Color& getColor() const { return m_circle.getFillColor(); }

	void print() const;

private:
	sf::CircleShape							m_circle;
	glm::dvec2								m_position{};
	glm::dvec2								m_force{};			// In Newton
	glm::dvec2								m_velocity{};		// In meter per second
	double									m_mass{ 1.0f * MASS_SCALER };		// In kg
};

#endif //!__TETROMINO_H__