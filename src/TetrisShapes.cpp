#include "TetrisShapes.h"

namespace nsTetris
{
namespace nsColors
{
	extern const sf::Color RED{ sf::Color::Color(255, 0, 0) };
	extern const sf::Color GREEN{ sf::Color::Color(0, 255, 0) };
	extern const sf::Color BLUE{ sf::Color::Color(0, 0, 255) };
	extern const sf::Color YELLOW{ sf::Color::Color(255, 255, 0) };
	extern const sf::Color ORANGE{ sf::Color::Color(255, 168, 18) };
	extern const sf::Color PINK{ sf::Color::Color(255, 20, 147) };
	extern const sf::Color LIGHT_BLUE{ sf::Color::Color(30, 144, 255) };
}
extern const int kNUM_OF_SHAPES = 7;
TetrisShape::TetrisShape(const sf::Vector2f& pos, const sf::Color& color, const sf::Vector2f& dir, float speed)
	:m_position(pos)
	,m_color(color)
	,m_direction(dir)
	,m_speed(speed)
{}

void TetrisShape::init()
{
	if (m_shape.empty())
	{
		setUpShape();
	}
	m_blocks.clear();

	float x = m_position.x;
	float y = m_position.y;
	for (int i = 0; i < m_shape.size(); ++i)
	{
		for (int j = 0; j < m_shape[0].size(); ++j)
		{
			if (m_shape[i][j])
			{
				m_blocks.emplace_back(TetrisBlock(sf::Vector2f(x, y), m_color, m_direction, m_speed));
			}
			x += TetrisBlock::getSize();
		}
		x = m_position.x;
		y += TetrisBlock::getSize();
	}
}

void TetrisShape::setShape(const Grid& shape)
{
	m_shape = shape;
}

TetrisShape::Grid TetrisShape::getShape()
{
	return m_shape;
}

const TetrisShape::Grid& TetrisShape::getShape() const
{
	return m_shape;
}

void TetrisShape::setSpeed(float s)
{
	m_speed = s;
}

float TetrisShape::getSpeed() const
{
	return m_speed;
}

void TetrisShape::setPosition(const sf::Vector2f& pos)
{
	m_position = pos;
}

sf::Vector2f TetrisShape::getPosition() const
{
	return m_position;
}

void TetrisShape::setDirection(const sf::Vector2f& dir)
{
	m_direction = dir;
}

sf::Vector2f TetrisShape::getDirection() const
{
	return m_direction;
}

size_t TetrisShape::numOfBlocks() const
{
	return m_blocks.size();
}

void TetrisShape::moveLeft()
{
	for (auto& block : m_blocks)
	{
		block.translate(-TetrisBlock::getSize(), 0);
	}
}

void TetrisShape::moveRight()
{
	for (auto& block : m_blocks)
	{
		block.translate(TetrisBlock::getSize(), 0);
	}
}

void TetrisShape::moveUp()
{
	assert(!"Should not be called!");
	return;
}

void TetrisShape::moveDown()
{
	for (auto& block : m_blocks)
	{
		block.translate(0, TetrisBlock::getSize());
	}
}

void TetrisShape::rotateCCW()
{
	//reverseTheOrderOfRows(Transpose(originalMatrix))
	Grid newShape;
	std::vector<bool> vec;
	for (int i = 0; i < m_shape[0].size(); ++i)
	{
		for (int j = 0; j < m_shape.size(); ++j)
		{
			vec.push_back(m_shape[j][i]);
		}
		newShape.push_back(vec);
		vec.clear();
	}
	m_shape = newShape;
	for (size_t i = 0, j = m_shape.size() - 1; i < j; ++i, --j)
	{
		swap(m_shape[i], m_shape[j]);
	}
	init();
	return;
}

void TetrisShape::rotateCW()
{
	//reverseTheOrderOfColumns(Transpose(originalMatrix))
	assert(!"Should not be called!");
	return;
}

void TetrisShape::update(const float elapsedSec)
{
	for (size_t i = 0; i < m_blocks.size(); ++i)
	{
		m_blocks[i].update(elapsedSec);
	}

	size_t minId = 0;
	for (size_t i = 1; i < m_blocks.size(); ++i)
	{
		if (m_blocks[i].getPosition().x < m_blocks[minId].getPosition().x)
		{
			minId = i;
		}
	}
	m_position = m_blocks[minId].getPosition();
}

void TetrisShape::render(sf::RenderWindow& w) const
{
	for (auto& block : m_blocks)
	{
		block.render(w);
	}
}



// I = [][][][]		// Light Blue
Shape_I::Shape_I(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color, float speed)
	:Base(pos, color, dir, speed)
{}

void Shape_I::setUpShape()
{
	m_shape.emplace_back(std::vector<bool>(4, true));
}




// O =	[][]		// Yellow
//		[][]
Shape_O::Shape_O(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color, float speed)
	:Base(pos, color, dir, speed)
{}

void Shape_O::setUpShape()
{
	m_shape.emplace_back(std::vector<bool>(2, true));
	m_shape.emplace_back(std::vector<bool>(2, true));
}




// T = [][][]		// Pink
//		 []
Shape_T::Shape_T(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color, float speed)
	:Base(pos, color, dir, speed)
{}

void Shape_T::setUpShape()
{
	m_shape.emplace_back(std::vector<bool>(3, true));
	m_shape.emplace_back(std::vector<bool>(3, true));
	m_shape[1][0] = m_shape[1][2] = false;
}



//		[]			// Blue
// J =  []
//	  [][]
Shape_J::Shape_J(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color, float speed)
	:Base(pos, color, dir, speed)
{}

void Shape_J::setUpShape()
{
	m_shape.emplace_back(std::vector<bool>(2, true));
	m_shape.emplace_back(std::vector<bool>(2, true));
	m_shape.emplace_back(std::vector<bool>(2, true));
	m_shape[0][0] = m_shape[1][0] = false;
}



// L =  []			// Orange
//		[]
//		[][]
Shape_L::Shape_L(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color, float speed)
	:Base(pos, color, dir, speed)
{}

void Shape_L::setUpShape()
{
	m_shape.emplace_back(std::vector<bool>(2, true));
	m_shape.emplace_back(std::vector<bool>(2, true));
	m_shape.emplace_back(std::vector<bool>(2, true));
	m_shape[0][1] = m_shape[1][1] = false;
}



// Z = [][]			// Green
//		 [][]
Shape_Z::Shape_Z(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color, float speed)
	:Base(pos, color, dir, speed)
{}

void Shape_Z::setUpShape()
{
	m_shape.emplace_back(std::vector<bool>(3, true));
	m_shape.emplace_back(std::vector<bool>(3, true));
	m_shape[0][2] = m_shape[1][0] = false;
}



// S =  [][]		// Red
//    [][]
Shape_S::Shape_S(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color, float speed)
	:Base(pos, color, dir, speed)
{}

void Shape_S::setUpShape()
{
	m_shape.emplace_back(std::vector<bool>(3, true));
	m_shape.emplace_back(std::vector<bool>(3, true));
	m_shape[0][0] = m_shape[1][2] = false;
}
}
