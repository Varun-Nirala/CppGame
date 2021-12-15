#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <algorithm>
#include "BattleShip.h"
#include "Bullet.h"

namespace AsteroidNS
{
template<typename T>
inline void deleteVector(std::vector<T>& v)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		delete v[i];
	}
	v.clear();
}

class Game
{
	public:
		Game(sf::RenderWindow &rw)
			:m_window(rw)
		{
			m_clock.restart();
		}

		~Game()
		{
			deleteVector(m_bullets);
		}

		void update()
		{
			// handle events
			sf::Time time = m_clock.getElapsedTime();
			m_clock.restart();
			sf::Event event;
			if (m_window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					m_window.close();
				}

				sf::Vector2f mouse = (sf::Vector2f)sf::Mouse::getPosition(m_window);
				m_player.setOrigin(mouse);
				m_player.update(time.asSeconds());

				if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_player.canFire())
				{
					m_bullets.push_back(m_player.fire());
				}
			}

			for (size_t i = 0; i < m_bullets.size(); ++i)
			{
				m_bullets[i]->update(time.asSeconds());
			}
		}

		void render() const
		{
			m_window.clear();

			m_player.render(m_window);
			
			for (size_t i = 0; i < m_bullets.size(); ++i)
			{
				m_bullets[i]->render(m_window);
			}
		}

	private:
		sf::RenderWindow				&m_window;
		BattleShip						m_player{};
		std::vector<Bullet*>			m_bullets{};
		sf::Clock						m_clock{};
};
}
#endif //__GAME_H__
