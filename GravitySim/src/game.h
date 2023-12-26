#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "constant.h"
#include "object.h"
#include "helper.h"

#include <array>

class Game
{
public:
	Game(std::string gameTitle, int width, int height);

	void setUpObjects(size_t count, bool sameSizeObjects);

	void run();

private:
	void processEvents();
	void update(const sf::Time &elapsedTime);
	void render();

private:
	Object* createRandomObject(bool sameSizeObjects);

private:
	sf::Clock							m_clock{};
	sf::Time							m_timeSinceLastUpdate{};
	const sf::Time						m_timePerFrame{ sf::seconds(1.0f / 60.0f) };
	sf::Time							m_gameSpeed{ sf::seconds(1.0f) / 6.0f };

	sf::RenderWindow					m_window;
	bool								m_bGamePaused{ false };

	std::vector<Object*>				m_objects;


	std::pair<int, int>					m_objectSizeRange{ 1, 5 };
	std::array<sf::Color, 5>			m_objectColorRange{ sf::Color::White, sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Yellow };
};

#endif //!__GAME_H__