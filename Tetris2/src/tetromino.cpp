#include "tetromino.h"
#include "constant.h"

#include "logger.h"

#include <cassert>

const std::vector<char> Tetromino::m_shapes{ SHAPE_I, SHAPE_J, SHAPE_L, SHAPE_O, SHAPE_S, SHAPE_T, SHAPE_Z };
const std::vector<sf::Color> Tetromino::m_colors{ COLOR_I, COLOR_J, COLOR_L, COLOR_O, COLOR_S, COLOR_T, COLOR_Z };

Tetromino::Tetromino(ShapeID id)
	: m_id(id)
{
	m_minos = create_minos(m_shapes[m_id]);
}

void Tetromino::reset(ShapeID id)
{
	if (m_id == id) return;

	m_id = id;
	m_minos = create_minos(m_shapes[id]);
}

void Tetromino::clearOldCells(std::vector<std::vector<char>>& matrix)
{
	for (sf::Vector2i& pos : m_minos)
	{
		matrix[pos.x][pos.y] = 0;
	}
}

bool Tetromino::canMoveLeft(std::vector<std::vector<char>>& matrix)
{
	for (const sf::Vector2i& pos : m_minos)
	{
		if (pos.x <= 0)
		{
			return false;
		}

		if (matrix[pos.x - 1][pos.y])
		{
			return false;
		}
	}
	return true;
}

bool Tetromino::canMoveRight(std::vector<std::vector<char>>& matrix)
{
	for (const sf::Vector2i& pos : m_minos)
	{
		if (COLUMNS <= 1 + pos.x)
		{
			return false;
		}

		if (matrix[pos.x + 1][pos.y])
		{
			return false;
		}
	}
	return true;
}

bool Tetromino::canMoveDown(std::vector<std::vector<char>>& matrix)
{
	for (const sf::Vector2i& pos : m_minos)
	{
		if (ROWS <= 1 + pos.y)
		{
			return false;
		}

		if (matrix[pos.x][pos.y + 1])
		{
			return false;
		}
	}
	return true;
}

bool Tetromino::canRotateCW(std::vector<std::vector<char>>& matrix)
{
	// TODO
	if (m_id == ID_O) { return true; }

	for (const sf::Vector2i& pos : m_minos)
	{
		if (ROWS <= 1 + pos.y)
		{
			return false;
		}

		if (matrix[pos.x][pos.y + 1])
		{
			return false;
		}
	}
	return true;
}

bool Tetromino::moveLeft(std::vector<std::vector<char>>& matrix)
{
	if (!canMoveLeft(matrix)) return false;

	for (sf::Vector2i& pos : m_minos)
	{
		--pos.x;
	}

	return true;
}

bool Tetromino::moveRight(std::vector<std::vector<char>>& matrix)
{
	if (!canMoveRight(matrix)) return false;

	for (sf::Vector2i& pos : m_minos)
	{
		++pos.x;
	}

	return true;
}

bool Tetromino::moveDown(std::vector<std::vector<char>>& matrix)
{
	if (!canMoveDown(matrix)) return false;

	for (sf::Vector2i& pos : m_minos)
	{
		++pos.y;
	}

	return true;
}

bool Tetromino::rotateCW(std::vector<std::vector<char>>& matrix)
{
	if (!canRotateCW(matrix)) return false;

	if (m_id == ID_O) { return true; }

	


	return true;
}

void Tetromino::updateNewCells(std::vector<std::vector<char>>& matrix)
{
	for (sf::Vector2i& pos : m_minos)
	{
		matrix[pos.x][pos.y] = (char)m_id;
	}
}

void Tetromino::draw(sf::RenderWindow& window)
{
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

	for (const sf::Vector2i& pos : m_minos)
	{
		cell.setPosition((float)CELL_SIZE * pos.x, (float)CELL_SIZE * pos.y);
		cell.setFillColor(m_colors[m_id]);
		window.draw(cell);
	}
}

void Tetromino::rotateMatrix(std::vector<std::vector<bool>>& mat)
{
	int size = (int)mat.size();
	// Rotate matrix right
	// 1. take transponse
	for (int i = 0; i < size; ++i)
	{
		for (int j = i; j < size; ++j)
		{
			if (i != j)
			{
				std::swap(mat[i][j], mat[j][i]);
			}
		}
	}

	// 2. flip horizontally
	for (int i = 0, j = size - 1; i < j; ++i, --j)
	{
		for (int k = 0; k < size; ++k)
		{
			std::swap(mat[k][i], mat[k][j]);
		}
	}
}

std::vector<sf::Vector2i> Tetromino::create_minos(char shape)
{
	std::vector<sf::Vector2i> minos(4);
	switch (shape)
	{
		case SHAPE_I:
			minos[0].x = COLUMNS / 2 - 2;
			minos[0].y = 0;
			minos[1].x = COLUMNS / 2 - 1;
			minos[1].y = 0;
			minos[2].x = COLUMNS / 2;
			minos[2].y = 0;
			minos[3].x = COLUMNS / 2 + 1;
			minos[3].y = 0;

			m_vecForRotation = {
				{ false, false, false, false },
				{ true, true, true, true },
				{ false, false, false, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_J:
			minos[0].x = COLUMNS / 2 - 1;
			minos[0].y = 0;
			minos[1].x = COLUMNS / 2 - 1;
			minos[1].y = 1;
			minos[2].x = COLUMNS / 2;
			minos[2].y = 1;
			minos[3].x = COLUMNS / 2 + 1;
			minos[3].y = 1;

			m_vecForRotation = {
				{ true, false, false, false },
				{ true, true, true, false },
				{ false, false, false, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_L:
			minos[0].x = COLUMNS / 2 - 1;
			minos[0].y = 1;
			minos[1].x = COLUMNS / 2;
			minos[1].y = 1;
			minos[2].x = COLUMNS / 2 + 1;
			minos[2].y = 1;
			minos[3].x = COLUMNS / 2 + 1;
			minos[3].y = 0;

			m_vecForRotation = {
				{ false, false, true, false },
				{ true, true, true, false },
				{ false, false, false, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_O:
			minos[0].x = COLUMNS / 2 - 1;
			minos[0].y = 0;
			minos[1].x = COLUMNS / 2;
			minos[1].y = 0;
			minos[2].x = COLUMNS / 2;
			minos[2].y = 1;
			minos[3].x = COLUMNS / 2 - 1;
			minos[3].y = 1;

			m_vecForRotation = {
				{ false, false, false, true },
				{ false, true, true, false },
				{ false, true, true, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_S:
			minos[0].x = COLUMNS / 2 + 1;
			minos[0].y = 0;
			minos[1].x = COLUMNS / 2;
			minos[1].y = 0;
			minos[2].x = COLUMNS / 2;
			minos[2].y = 1;
			minos[3].x = COLUMNS / 2 - 1;
			minos[3].y = 1;

			m_vecForRotation = {
				{ false, true, true, false },
				{ true, true, false, false },
				{ false, false, false, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_T:
			minos[0].x = COLUMNS / 2 - 1;
			minos[0].y = 0;
			minos[1].x = COLUMNS / 2;
			minos[1].y = 0;
			minos[2].x = COLUMNS / 2 + 1;
			minos[2].y = 0;
			minos[3].x = COLUMNS / 2;
			minos[3].y = 1;

			m_vecForRotation = {
				{ false, true, false, true },
				{ true, true, true, false },
				{ false, false, false, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_Z:
			minos[0].x = COLUMNS / 2 - 1;
			minos[0].y = 0;
			minos[1].x = COLUMNS / 2;
			minos[1].y = 0;
			minos[2].x = COLUMNS / 2;
			minos[2].y = 1;
			minos[3].x = COLUMNS / 2 + 1;
			minos[3].y = 1;

			m_vecForRotation = {
				{ true, true, false, false },
				{ false, true, true, false },
				{ false, false, false, false },
				{ false, false, false, false }
			};
			break;

		default:
			ns_Util::Logger::LOG_ERROR("Unkown tetromino shape : ", (char)shape, '\n');
			assert(false);
			break;
	}
	return minos;
}