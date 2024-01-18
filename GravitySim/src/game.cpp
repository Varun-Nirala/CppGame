#include "game.h"
#include "gravity.h"
#include "helper.h"

Game::Game(std::string gameTitle, int width, int height)
	: m_window{ sf::RenderWindow(sf::VideoMode(width, height), gameTitle, sf::Style::Close) }
{
	m_window.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(width), static_cast<float>(height))));
}

void Game::setUpObjects(size_t count, const std::bitset<FLAG_SIZE>& flags)
{
	// Clear the old objects.
	std::for_each(m_objects.begin(), m_objects.end(), [&](Object* object) { delete object; });
	m_objects.clear();

	m_objects.reserve(count);

	// We will create only one object with all random values.
	m_objects.push_back(createRandomObject());

	for (int i = 1; i < count; ++i)
	{
		m_objects.push_back(createObject(flags));
		m_objects.back()->setRadius(m_objects.front()->getRadius());
	}
}

void Game::run()
{
	while (m_window.isOpen())
	{
		processEvents();

		m_timeSinceLastUpdate += m_clock.restart();

		while (!m_bGamePaused && m_timeSinceLastUpdate > m_timePerFrame)
		{
			m_timeSinceLastUpdate -= m_timePerFrame;
			processEvents();
			update(m_timeSinceLastUpdate);
		}

		if (!m_bGamePaused)
		{
			render();
		}
	}
}

void Game::processEvents()
{
	sf::Event event;
	if (m_window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				m_window.close();
				break;

			case sf::Event::LostFocus:
				m_bGamePaused = true;
				break;

			case sf::Event::GainedFocus:
				m_bGamePaused = false;
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						m_bGamePaused = !m_bGamePaused;
						break;

					case sf::Keyboard::S:
						// Create new set of objects having same radius.
						setUpObjects(m_objects.size(), true);
						break;

					case sf::Keyboard::R:
						// Create new set of objects having random radius.
						setUpObjects(m_objects.size(), false);
						break;
				}
				break;
		}
	}
}

void Game::update(const sf::Time &elapsedTime)
{
	// Apply gravity to all the objects, from all other objects.
	for (size_t i = 0; i < m_objects.size(); ++i)
	{
		Gravity::applyGravity(m_objects, i);
	}

	// Update the position of the objects
	std::for_each(m_objects.begin(), m_objects.end(), [&](Object* object) { object->update(elapsedTime); });
}

void Game::render()
{
	m_window.clear();

	std::for_each(m_objects.begin(), m_objects.end(), [&](Object* object) { object->draw(m_window); });

	m_window.display();
}

Object* Game::createRandomObject()
{
	int radius = Helper::getRandomNumber(m_objectSizeRange.first, m_objectSizeRange.second);
	float mass = Helper::getRandomNumber(m_objectMassRange.first, m_objectMassRange.second);

	sf::Color color = m_objectColorRange[Helper::getRandomNumber(0, (int)m_objectColorRange.size() - 1)];
	float posX = static_cast<float>(Helper::getRandomNumber(0, m_window.getSize().x - radius));
	float posY = static_cast<float>(Helper::getRandomNumber(0, m_window.getSize().y - radius));
	// Code to create random objects
	return new Object(static_cast<float>(radius), color, sf::Vector2f(posX, posY), mass);
}

Object* Game::createObject(const std::bitset<FLAG_SIZE>& flags)
{
	int radius = flags.test(SAME_RADIUS) ? 0 : Helper::getRandomNumber(m_objectSizeRange.first, m_objectSizeRange.second);
	float mass = flags.test(SAME_MASS) ? 0 : Helper::getRandomNumber(m_objectMassRange.first, m_objectMassRange.second);

	sf::Color color = m_objectColorRange[Helper::getRandomNumber(0, (int)m_objectColorRange.size() - 1)];
	float posX = static_cast<float>(Helper::getRandomNumber(0, m_window.getSize().x - radius));
	float posY = static_cast<float>(Helper::getRandomNumber(0, m_window.getSize().y - radius));
	// Code to create random objects
	return new Object(static_cast<float>(radius), color, sf::Vector2f(posX, posY), mass);
}