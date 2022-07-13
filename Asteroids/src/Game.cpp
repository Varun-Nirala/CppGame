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

void Game::render() const
{
	m_window.clear(m_clearColor);

	for (size_t i = 0; i < m_bullets.size(); ++i)
	{
		m_bullets[i]->render(m_window);
	}

	m_player.render(m_window);
}