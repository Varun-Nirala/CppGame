#ifndef __TETRIS_SHAPES_H__
#define __TETRIS_SHAPES_H__

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Color.hpp>

#include "TetrisBlock.h"

namespace nsTetris
{
	namespace nsColors
	{
		extern const sf::Color RED;
		extern const sf::Color GREEN;
		extern const sf::Color BLUE;
		extern const sf::Color YELLOW;
		extern const sf::Color ORANGE;
		extern const sf::Color PINK;
		extern const sf::Color LIGHT_BLUE;
	}
extern const int kNUM_OF_SHAPES;

class TetrisShape
{
public:
	using Base = TetrisShape;
	using Grid = std::vector<std::vector<bool>>;

	TetrisShape() = default;
	virtual ~TetrisShape() = default;

	TetrisShape(const TetrisShape&) = default;
	TetrisShape(TetrisShape&&) = default;

	TetrisShape& operator=(const TetrisShape&) = default;
	TetrisShape& operator=(TetrisShape&&) = default;

	TetrisShape(const sf::Vector2f& pos, const sf::Color& color, const sf::Vector2f& dir, float speed = _kDEFAULT_SPEED);

	virtual void setUpShape() = 0;
	virtual void init();

	void setShape(const Grid& grid);
	Grid getShape();
	const Grid& getShape() const;

	void setSpeed(float s);
	float getSpeed() const;

	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition() const;

	void setDirection(const sf::Vector2f& dir);
	sf::Vector2f getDirection() const;

	size_t numOfBlocks() const;

	void moveLeft();
	void moveRight();
	void moveUp();
	void moveDown();

	void rotateCCW();
	void rotateCW();

	void update(const float elapsedSec);
	void render(sf::RenderWindow& w) const;

protected:
	Grid						m_shape;
	sf::Color					m_color;
	sf::Vector2f				m_position;
	std::vector<TetrisBlock>	m_blocks;
	sf::Vector2f				m_direction;
	float						m_speed{};
};

class Shape_I : public TetrisShape
{
public:
	using TetrisShape::Grid;
	Shape_I(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color = nsColors::RED, float speed = _kDEFAULT_SPEED);

	virtual void setUpShape() override;
};

class Shape_O : public TetrisShape
{
public:
	using TetrisShape::Grid;
	Shape_O(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color = nsColors::YELLOW, float speed = _kDEFAULT_SPEED);
	
	virtual void setUpShape() override;
};

class Shape_T : public TetrisShape
{
public:
	using TetrisShape::Grid;
	Shape_T(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color = nsColors::PINK, float speed = _kDEFAULT_SPEED);
	
	virtual void setUpShape() override;
};

class Shape_J : public TetrisShape
{
public:
	using TetrisShape::Grid;
	Shape_J(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color = nsColors::BLUE, float speed = _kDEFAULT_SPEED);
	
	virtual void setUpShape() override;
};

class Shape_L : public TetrisShape
{
public:
	using TetrisShape::Grid;
	Shape_L(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color = nsColors::ORANGE, float speed = _kDEFAULT_SPEED);
	
	virtual void setUpShape() override;
};

class Shape_Z : public TetrisShape
{
public:
	using TetrisShape::Grid;
	Shape_Z(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color = nsColors::GREEN, float speed = _kDEFAULT_SPEED);
	
	virtual void setUpShape() override;
};

class Shape_S : public TetrisShape
{
public:
	using TetrisShape::Grid;
	Shape_S(const sf::Vector2f& pos, const sf::Vector2f& dir, const sf::Color& color = nsColors::RED, float speed = _kDEFAULT_SPEED);
	
	virtual void setUpShape() override;
};
}
#endif // #define __TETRIS_SHAPES_H__