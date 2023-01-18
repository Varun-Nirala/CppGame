#include "game.h"

Game::Game()
	: m_window{ sf::RenderWindow(sf::VideoMode(CELL_SIZE * COLUMNS * SCREEN_RESIZE, CELL_SIZE * ROWS * SCREEN_RESIZE), "Tetris", sf::Style::Close) }
	, m_matrix{ std::vector<std::vector<char>>(ROWS, std::vector<char>(COLUMNS, EMPTY_CELL)) }
	, m_actions(ACTION_MAX, false)
{
}

Game::~Game()
{
	teardown();
}

void Game::setup()
{
	m_window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * COLUMNS, CELL_SIZE * ROWS)));
}

void Game::teardown()
{
}

void Game::run()
{
	m_tetromino.reset(static_cast<ShapeID>(getRandomNumber(0, Tetromino::getNumberOfShapes() - 1)));

	while (m_window.isOpen())
	{
		processEvents();

		m_timeSinceLastUpdate += m_clock.restart();

		while (!m_bGamePaused && m_timeSinceLastUpdate > m_gameSpeed)
		{
			m_timeSinceLastUpdate -= m_gameSpeed;
			processEvents();
			update();
		}

		if (m_bGamePaused)
		{
			m_timeSinceLastUpdate = sf::Time::Zero;
		}

		render();
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

					case sf::Keyboard::A:
					case sf::Keyboard::Left:
						m_actions[LEFT] = true;
						break;
							
					case sf::Keyboard::D:
					case sf::Keyboard::Right:
						m_actions[RIGHT] = true;
						break;

					case sf::Keyboard::S:
					case sf::Keyboard::Down:
						m_actions[DOWN] = true;
						break;

					case sf::Keyboard::Space:
						m_actions[SPACE] = true;
						break;
				}
				break;
		}
	}
}

void Game::update()
{
	if (m_actions[LEFT])
	{
		m_tetromino.clearOldCells(m_matrix);
		m_tetromino.moveLeft(m_matrix);
		m_tetromino.updateNewCells(m_matrix);

		m_actions[LEFT] = false;
	}

	if (m_actions[RIGHT])
	{
		m_tetromino.clearOldCells(m_matrix);
		m_tetromino.moveRight(m_matrix);
		m_tetromino.updateNewCells(m_matrix);

		m_actions[RIGHT] = false;
	}

	if (m_actions[DOWN])
	{
		m_tetromino.clearOldCells(m_matrix);
		m_tetromino.moveDown(m_matrix);
		m_tetromino.updateNewCells(m_matrix);

		m_actions[DOWN] = false;
	}

	if (m_actions[SPACE])
	{
		m_tetromino.clearOldCells(m_matrix);
		m_tetromino.rotateCW(m_matrix);
		m_tetromino.updateNewCells(m_matrix);

		m_actions[SPACE] = false;
	}

	m_tetromino.clearOldCells(m_matrix);
	if (!m_tetromino.moveDown(m_matrix))
	{
		m_tetromino.updateNewCells(m_matrix);

		std::vector<int> filledRows = checkWinLines();

		for (int r : filledRows)
		{
			for (int i = r - 1; i >= 0; --i)
			{
				m_matrix[i + 1] = m_matrix[i];
			}
			incrementScore();
		}

		const int id = getRandomNumber(0, Tetromino::getNumberOfShapes() - 1);
		m_tetromino.reset(static_cast<ShapeID>(id));
	}
	m_tetromino.updateNewCells(m_matrix);
}

void Game::render()
{
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

	m_window.clear();

	for (char y = 0; y < ROWS; ++y)
	{
		for (char x = 0; x < COLUMNS; ++x)
		{
			cell.setPosition((float)CELL_SIZE * x, (float)CELL_SIZE * y);

			if (m_matrix[y][x] == EMPTY_CELL)
			{
				cell.setFillColor(COLOR_EMPTY_CELL);
			}
			else
			{
				cell.setFillColor(Tetromino::getColor(m_matrix[y][x]));
			}
			m_window.draw(cell);
		}
	}
	m_tetromino.render(m_window);
	m_window.display();
}

void Game::incrementScore()
{
	m_score += SCORE_PER_LINE;
}

std::vector<int> Game::checkWinLines() const
{
	std::vector<int> res;

	for (char y = ROWS - 1; y >= 0; --y)
	{
		bool bAllFilled{ true };
		for (char x = 0; x < COLUMNS; ++x)
		{
			if (m_matrix[y][x] == EMPTY_CELL)
			{
				bAllFilled = false;
				break;
			}
		}
		if (bAllFilled)
		{
			res.push_back(y);
		}
	}
	return res;
}