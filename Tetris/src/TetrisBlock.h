#ifndef __TETRIS_BLOCK_H__
#define __TETRIS_BLOCK_H__

#include <SFML/Graphics.hpp>
#include <cassert>

#include "Common.h"

namespace nsTetris
{
// will be drawn and moved wrt to top left position
extern const float _kDEFAULT_SPEED;
extern const int _kDEFAULT_SIZE;
extern const int _kDEFAULT_THICKNESS;
class TetrisBlock
{
public:
	TetrisBlock(const sf::Vector2f& pos, const sf::Color& color, const sf::Vector2f &dir, const float speed = _kDEFAULT_SPEED);

	void setSpeed(float s);
	float getSpeed() const;

	void setPosition(const sf::Vector2f& pos);
	sf::Vector2f getPosition() const;		// returns the top left x, y of the block

	void setDirection(const sf::Vector2f& dir);
	sf::Vector2f getDirection() const;

	void update(const float elapsedSec);
	void render(sf::RenderWindow& w) const;

	void translate(float x, float y);
	void translate(int x, int y);

	sf::RectangleShape& getShape() {
		return m_block;
	};

	static int getSize() { return _s_size; };
	static int getThickness() { return _s_thickness; };

	static void setMinMaxX(float minX, float maxX) { _s_minX = minX; _s_maxX = maxX; }
	static void setMinMaxY(float minY, float maxY) { _s_minY = minY; _s_maxY = maxY; }

private:
	void init(const sf::Vector2f& pos, const sf::Color& color);

private:
	sf::RectangleShape		m_block;
	sf::Vector2f			m_direction{};
	float					m_speed{};
	static const int		_s_size;
	static const int		_s_thickness;
	static float			_s_minX;
	static float			_s_minY;
	static float			_s_maxX;
	static float			_s_maxY;
};
}
#endif //__TETRIS_BLOCK_H__