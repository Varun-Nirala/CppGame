#ifndef __OBJECT_H__
#define __OBJECT_H__

#include <SFML/Graphics.hpp>
#include <vector>

#include "constant.h"

class Object
{
public:
	Object(float radius, sf::Color color, sf::Vector2f position);

	Object(const Object& other) = delete;
	Object(Object&& other) = delete;

	Object& operator=(const Object& other) = delete;
	Object& operator=(Object&& other) = delete;

	void update(const sf::Time& elapsedTime);
	void draw(sf::RenderWindow& window);

	void setPosition(sf::Vector2f position) { m_circle.setPosition(position); }
	void setPosition(float posX, float posY) { m_circle.setPosition(posX, posY); }
	sf::Vector2f getPosition() const { return m_circle.getPosition(); }
	float getPosX() const { return m_circle.getPosition().x; }
	float getPosY() const { return m_circle.getPosition().y; }

	void setRadius(float radius) { m_circle.setRadius(radius); }
	const float getRadius() const { return m_circle.getRadius(); }

	void setFillColor(sf::Color color) { m_circle.setFillColor(color); }
	const sf::Color& getColor() const { return m_circle.getFillColor(); }


	void print() const;

private:
	sf::CircleShape							m_circle;
};

#endif //!__TETROMINO_H__