#include "tetromino.h"

#include "helper.h"
#include "logger.h"

#include <cassert>

const std::vector<char> Tetromino::m_shapes{ SHAPE_I, SHAPE_J, SHAPE_L, SHAPE_O, SHAPE_S, SHAPE_T, SHAPE_Z };
const std::vector<sf::Color> Tetromino::m_colors{ COLOR_I, COLOR_J, COLOR_L, COLOR_O, COLOR_S, COLOR_T, COLOR_Z };

Tetromino::Tetromino(ShapeID id)
	: m_id(id)
{
	create_minos(m_shapes[m_id]);
	ns_Util::Logger::LOG_MSG("Shape : ", m_shapes[m_id], '\n');
}

void Tetromino::reset(ShapeID id)
{
	m_id = id;
	create_minos(m_shapes[id]);
	ns_Util::Logger::LOG_MSG("Shape : ", m_shapes[m_id], '\n');
}

void Tetromino::clearOldCells(std::vector<std::vector<char>>& matrix)
{
	for (int r = 0, rows = (int)m_boundingBox.size(); r < rows; ++r)
	{
		for (int c = 0, cols = (int)m_boundingBox[r].size(); c < cols; ++c)
		{
			if (m_boundingBox[r][c])
			{
				matrix[m_position.y + r][m_position.x + c] = EMPTY_CELL;
			}
		}
	}
}

bool Tetromino::canMoveLeft(std::vector<std::vector<char>>& matrix) const
{
	for (int r = 0, rows = (int)m_boundingBox.size(); r < rows; ++r)
	{
		const int currY = m_position.y + r;
		for (int c = 0, cols = (int)m_boundingBox[r].size(); c < cols; ++c)
		{
			if (m_boundingBox[r][c])
			{
				const int currX = m_position.x + c;

				if (currX - 1 < 0 || matrix[currY][currX - 1] != EMPTY_CELL)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool Tetromino::canMoveRight(std::vector<std::vector<char>>& matrix) const
{
	for (int r = 0, rows = (int)m_boundingBox.size(); r < rows; ++r)
	{
		const int currY = m_position.y + r;
		for (int c = 0, cols = (int)m_boundingBox[r].size(); c < cols; ++c)
		{
			if (m_boundingBox[r][c])
			{
				const int currX = m_position.x + c;

				if (currX + 1 >= COLUMNS || matrix[currY][currX + 1] != EMPTY_CELL)
				{
					return false;
				}
			}
		}
	}

	return true;
}

bool Tetromino::canMoveDown(std::vector<std::vector<char>>& matrix) const
{
	for (int r = 0, rows = (int)m_boundingBox.size(); r < rows; ++r)
	{
		const int currY = m_position.y + r;
		for (int c = 0, cols = (int)m_boundingBox[r].size(); c < cols; ++c)
		{
			if (m_boundingBox[r][c])
			{
				const int currX = m_position.x + c;
				if (currY + 1 >= ROWS || matrix[currY + 1][currX] != EMPTY_CELL)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Tetromino::canRotateCW(std::vector<std::vector<char>>& matrix) const
{
	// TODO
	if (m_id == ID_O) { return true; }

	std::vector<std::vector<bool>> temp = m_boundingBox;

	rotateMatrix(temp);

	for (int r = 0, rows = (int)m_boundingBox.size(); r < rows; ++r)
	{
		const int currY = m_position.y + r;
		for (int c = 0, cols = (int)m_boundingBox[r].size(); c < cols; ++c)
		{
			if (m_boundingBox[r][c])
			{
				const int currX = m_position.x + c;
				if (currY + 1 >= ROWS || matrix[currY][currX] != EMPTY_CELL
					|| currX < 0 || currX >= COLUMNS)
				{
					return false;
				}
			}
		}
	}
	return true;
}

bool Tetromino::moveLeft(std::vector<std::vector<char>>& matrix)
{
	if (!canMoveLeft(matrix)) return false;

	--m_position.x;

	return true;
}

bool Tetromino::moveRight(std::vector<std::vector<char>>& matrix)
{
	if (!canMoveRight(matrix)) return false;

	++m_position.x;

	return true;
}

bool Tetromino::moveDown(std::vector<std::vector<char>>& matrix)
{
	if (!canMoveDown(matrix)) return false;

	++m_position.y;

	return true;
}

bool Tetromino::rotateCW(std::vector<std::vector<char>>& matrix)
{
	if (m_id == ID_O) { return true; }

	if (!canRotateCW(matrix)) return false;

	printVectorOfVector<bool>(m_boundingBox);
	rotateMatrix(m_boundingBox);
	printVectorOfVector<bool>(m_boundingBox);

	return true;
}

void Tetromino::updateNewCells(std::vector<std::vector<char>>& matrix)
{
	for (int r = 0, rows = (int)m_boundingBox.size(); r < rows; ++r)
	{
		const int currY = m_position.y + r;
		for (int c = 0, cols = (int)m_boundingBox[r].size(); c < cols; ++c)
		{
			if (m_boundingBox[r][c])
			{
				const int currX = m_position.x + c;
				matrix[currY][currX] = (char)m_id;
			}
		}
	}
}

void Tetromino::render(sf::RenderWindow& window) const
{
	sf::RectangleShape cell(sf::Vector2f(CELL_SIZE - 1, CELL_SIZE - 1));

	for (int r = 0, rows = (int)m_boundingBox.size(); r < rows; ++r)
	{
		for (int c = 0, cols = (int)m_boundingBox[r].size(); c < cols; ++c)
		{
			if (m_boundingBox[r][c])
			{
				cell.setPosition((float)CELL_SIZE * (m_position.x + c), (float)CELL_SIZE * (m_position.y + r));
				cell.setFillColor(m_colors[m_id]);
				window.draw(cell);
			}
		}
	}
}

void Tetromino::rotateMatrix(std::vector<std::vector<bool>>& mat) const
{
	const int size = (int)mat.size();
	// Rotate matrix right
	// 1. take transponse
	for (int i = 0; i < size; ++i)
	{
		for (int j = i; j < size; ++j)
		{
			if (i != j)
			{
				// can't use swap as vector<bool> behave differently, just a simple swap
				const bool temp = mat[i][j];
				mat[i][j] = mat[j][i];
				mat[j][i] = temp;
			}
		}
	}

	// 2. flip horizontally
	for (int i = 0, j = size - 1; i < j; ++i, --j)
	{
		for (int k = 0; k < size; ++k)
		{
			// can't use swap as vector<bool> behave differently, just a simple swap
			const bool temp = mat[k][i];
			mat[k][i] = mat[k][j];
			mat[k][j] = temp;
		}
	}
}

void Tetromino::create_minos(char shape)
{
	m_position = { COLUMNS / 2 - 2, 0 };
	switch (shape)
	{
		case SHAPE_I:
			m_boundingBox = {
				{ false, false, false, false },
				{ true, true, true, true },
				{ false, false, false, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_J:
			m_boundingBox = {
				{ true, false, false, false },
				{ true, true, true, false },
				{ false, false, false, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_L:
			m_boundingBox = {
				{ false, false, true, false },
				{ true, true, true, false },
				{ false, false, false, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_O:
			m_boundingBox = {
				{ false, false, false, false },
				{ false, true, true, false },
				{ false, true, true, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_S:
			m_boundingBox = {
				{ false, true, true, false },
				{ true, true, false, false },
				{ false, false, false, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_T:
			m_boundingBox = {
				{ false, true, false, false },
				{ true, true, true, false },
				{ false, false, false, false },
				{ false, false, false, false }
			};
			break;

		case SHAPE_Z:
			m_boundingBox = {
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
}