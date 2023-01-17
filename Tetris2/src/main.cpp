#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

#include "constant.h"
#include "tetromino.h"

#include "helper.h"

void processEvents(sf::RenderWindow& window, bool &bGamePaused, std::vector<bool> &action);
void update(sf::Time deltaTime, std::vector<bool>& action, Tetromino &tetromino, std::vector<std::vector<char>> &matrix);
void render(sf::RenderWindow &window, Tetromino& tetromino, std::vector<std::vector<char>> &matrix);

int main()
{
	std::vector<std::vector<char>> matrix(ROWS, std::vector<char>(COLUMNS, 0));

	sf::RenderWindow window(sf::VideoMode(CELL_SIZE * COLUMNS * SCREEN_RESIZE, CELL_SIZE * ROWS * SCREEN_RESIZE), "Tetris", sf::Style::Close);
	window.setView(sf::View(sf::FloatRect(0, 0, CELL_SIZE * COLUMNS, CELL_SIZE * ROWS)));

	Tetromino tetromino(ID_L);
	tetromino.reset(static_cast<ShapeID>(getRandomNumber(0, Tetromino::getNumberOfShapes() - 1)));

	std::vector<bool> action(ACTION_MAX, false);
	
	sf::Clock clock;

	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time TimePerFrame{ sf::seconds(1.0f / 60.0f) };

	sf::Time gameSpeed{ sf::seconds(1.0f / 6.0f) };
	
	bool bGamePaused{ false };

	while (window.isOpen())
	{
		processEvents(window, bGamePaused, action);

		timeSinceLastUpdate += clock.restart();

		while (!bGamePaused && timeSinceLastUpdate > gameSpeed)
		{
			timeSinceLastUpdate -= gameSpeed;
			processEvents(window, bGamePaused, action);
			update(gameSpeed, action, tetromino, matrix);
		}

		if (bGamePaused)
		{
			timeSinceLastUpdate = sf::Time::Zero;
		}

		render(window, tetromino, matrix);
	}

	return 0;
}

void processEvents(sf::RenderWindow& window, bool &bGamePaused, std::vector<bool>& action)
{
	sf::Event event;
	if (window.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				window.close();
				break;

			case sf::Event::LostFocus:
				bGamePaused = true;
				break;

			case sf::Event::GainedFocus:
				bGamePaused = false;
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						bGamePaused = !bGamePaused;
						break;

					case sf::Keyboard::A:
					case sf::Keyboard::Left:
						action[LEFT] = true;
						break;

					case sf::Keyboard::D:
					case sf::Keyboard::Right:
						action[RIGHT] = true;
						break;

					case sf::Keyboard::S:
					case sf::Keyboard::Down:
						action[DOWN] = true;
						break;

					case sf::Keyboard::Space:
						action[SPACE] = true;
						break;

					default:
						break;
				}
			default:
				break;
		}
	}
}

void update(sf::Time deltaTime, std::vector<bool> &action, Tetromino &tetromino, std::vector<std::vector<char>> &matrix)
{
	(void)deltaTime;

	if (action[LEFT])
	{
		tetromino.clearOldCells(matrix);
		tetromino.moveLeft(matrix);
		tetromino.updateNewCells(matrix);

		action[LEFT] = false;
	}
	
	if (action[RIGHT])
	{
		tetromino.clearOldCells(matrix);
		tetromino.moveRight(matrix);
		tetromino.updateNewCells(matrix);
		
		action[RIGHT] = false;
	}
	
	if (action[DOWN])
	{
		tetromino.clearOldCells(matrix);
		tetromino.moveDown(matrix);
		tetromino.updateNewCells(matrix);
		
		action[DOWN] = false;
	}
	
	if (action[SPACE])
	{
		tetromino.clearOldCells(matrix);
		tetromino.rotateCW(matrix);
		tetromino.updateNewCells(matrix);
	}

	tetromino.clearOldCells(matrix);
	if (!tetromino.moveDown(matrix))
	{
		tetromino.updateNewCells(matrix);
		const int id = getRandomNumber(0, Tetromino::getNumberOfShapes() - 1);
		tetromino.reset(static_cast<ShapeID>(id));
	}
	tetromino.updateNewCells(matrix);
}

void render(sf::RenderWindow& window, Tetromino& tetromino, std::vector<std::vector<char>> &matrix)
{
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

	window.clear();

	for (char y = 0; y < ROWS; ++y)
	{
		for (char x = 0; x < COLUMNS; ++x)
		{
			cell.setPosition((float)CELL_SIZE * x, (float)CELL_SIZE * y);

			if (matrix[y][x])
			{
				cell.setFillColor(Tetromino::getColor(matrix[y][x]));
			}
			else
			{
				cell.setFillColor(COLOR_EMPTY_CELL);
			}
			window.draw(cell);
		}
	}
	tetromino.draw(window);
	window.display();
}