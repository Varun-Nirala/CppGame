#include "Game.h"

using namespace AsteroidNS;

Game::Game(sf::RenderWindow &rw)
	:m_window(rw)
{
	m_clock.restart();
	m_player.setCanFire(true);
}

Game::~Game()
{
	deleteVector(m_bullets);
}

void Game::update()
{
	float inc_x = 5.0f;
	float inc_y = 5.0f;
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			// Left
			m_player.move(sf::Vector2f(-inc_x, 0));
			m_player.setRoll(-inc_x);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			// Right
			m_player.move(sf::Vector2f(inc_x, 0));
			m_player.setRoll(inc_x);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			// Up
			m_player.move(sf::Vector2f(0, -inc_y));
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			// Down
			m_player.move(sf::Vector2f(0, inc_y));
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_player.canFire())
		{
			m_bullets.push_back(m_player.fire());
		}
	}
	
	for (size_t i = 0; i < m_bullets.size(); ++i)
	{
		m_bullets[i]->update(time.asSeconds());
	}
	m_player.update(time.asSeconds());
}

void Game::render() const
{
	m_window.clear(m_clearColor);

	for (size_t i = 0; i < m_bullets.size(); ++i)
	{
		m_bullets[i]->render(m_window);
	}

	m_player.render(m_window);
}