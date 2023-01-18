#ifndef __GAME_H__
#define __GAME_H__

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "constant.h"
#include "tetromino.h"

#include "helper.h"

class Game
{
public:
	Game();
	~Game();

	void setup();
	void teardown();

	void run();

private:
	void processEvents();
	void update();
	void render();

	void incrementScore();
	std::vector<int> checkWinLines() const;

private:
	sf::Clock							m_clock{};
	sf::Time							m_timeSinceLastUpdate{};
	const sf::Time						m_timePerFrame{ sf::seconds(1.0f / 60.0f) };
	sf::Time							m_gameSpeed{ sf::seconds(1.0f) / 6.0f };

	sf::RenderWindow					m_window;

	std::vector<bool>					m_actions;

	Tetromino							m_tetromino{ ID_I };
	
	std::vector<std::vector<char>>		m_matrix;
	bool								m_bGamePaused{ false };

	int									m_score{};
};

#endif //!__GAME_H__