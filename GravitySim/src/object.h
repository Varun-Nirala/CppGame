#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/Graphics.hpp>
#include <vector>

#include "constant.h"

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

	void setVelocity(sf::Vector2f vel) { m_velocity = vel; }
	void setVelocity(float velX, float velY) { m_velocity.x = velX; m_velocity.y = velY; }
	const sf::Vector2f& getVelocity() const { return m_velocity; }
	float getVelocityX() const { return m_velocity.x; }
	float getVelocitY() const { return m_velocity.y; }

	void addVelocity(sf::Vector2f vel) { m_velocity += vel; }

	void setPosition(sf::Vector2f position) { m_circle.setPosition(position); }
	void setPosition(float posX, float posY) { m_circle.setPosition(posX, posY); }
	const sf::Vector2f& getPosition() const { return m_circle.getPosition(); }
	float getPositionX() const { return m_circle.getPosition().x; }
	float getPositionY() const { return m_circle.getPosition().y; }

	void setRadius(float radius) { m_circle.setRadius(radius); }
	const float getRadius() const { return m_circle.getRadius(); }

	void setFillColor(sf::Color color) { m_circle.setFillColor(color); }
	const sf::Color& getColor() const { return m_circle.getFillColor(); }

	void print() const;

private:
	sf::CircleShape							m_circle;
	sf::Vector2f							m_velocity{};
	float									m_mass{ 1.0f };
};

#endif //!__TETROMINO_H__