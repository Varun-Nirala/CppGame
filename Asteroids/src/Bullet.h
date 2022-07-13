#ifndef __BULLET_H__
#define __BULLET_H__

#include <SFML/Graphics.hpp>
#include <cassert>

namespace AsteroidNS
{
class Bullet
{
	public:
		Bullet(float size = 5.0f, float speed = 0.05f)
			:m_shape(size)
			,m_speed(speed)
		{
			assert(speed > 0.0f);
			m_shape.setOrigin(m_shape.getRadius(), m_shape.getRadius());
		}

		void setPosition(const sf::Vector2f &pos)
		{
			m_shape.setPosition(pos);
		}

		void setDirection(const sf::Vector2f& dir)
		{
			m_direction = dir;
		}

		void update(float secElapsed)
		{
			(void)secElapsed;
			m_shape.move(m_direction * m_speed);
		}

		void render(sf::RenderWindow& w) const
		{
			w.draw(m_shape);
		}

	private:
		sf::CircleShape		m_shape{};
		sf::Vector2f		m_direction{};
		float				m_speed{};

};
}
#endif //__BULLET_H__
