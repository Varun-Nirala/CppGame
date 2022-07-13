#ifndef __BULLET_H__
#define __BULLET_H__

#include <SFML/Graphics.hpp>
#include <cassert>

namespace AsteroidNS
{
class Bullet
{
public:
	Bullet(float size = 5.0f, float speed = 0.05f);

	void setPosition(const sf::Vector2f& pos);

	void setDirection(const sf::Vector2f& dir);

	void update(float secElapsed);

	void render(sf::RenderWindow& w) const;

private:
	sf::CircleShape		m_shape{};
	sf::Vector2f		m_direction{};
	float				m_speed{};

};
}
#endif //__BULLET_H__
