#include <SFML/Graphics.hpp>
#include <cassert>

#include "TetrisBlock.h"

namespace nsTetris
{
const float _kDEFAULT_SPEED = 25.0f;
const int _kDEFAULT_SIZE = 25;
const int _kDEFAULT_THICKNESS = 2;
TetrisBlock::TetrisBlock(const sf::Vector2f &pos, const sf::Color &color, const sf::Vector2f& dir, const float speed)
	:m_speed(speed)
	,m_direction(dir)
{
	m_block.setSize(sf::Vector2f(float(_s_size - _s_thickness), float(_s_size - _s_thickness)));
	init(pos, color);
}

void TetrisBlock::setSpeed(float s)
{
	m_speed = s;
}

float TetrisBlock::getSpeed() const
{
	return m_speed;
}

void TetrisBlock::setPosition(const sf::Vector2f &pos)
{
	m_block.setPosition(pos);
}

sf::Vector2f TetrisBlock::getPosition() const
{
	return m_block.getPosition();
}

void TetrisBlock::setDirection(const sf::Vector2f& dir)
{
	m_direction = dir;
}

sf::Vector2f TetrisBlock::getDirection() const
{
	return m_direction;
}

void TetrisBlock::update(const float elapsedSec)
{
	sf::Vector2f move = m_direction * m_speed * elapsedSec;
	translate(move.x, move.y);
}

void TetrisBlock::render(sf::RenderWindow& w) const
{
	w.draw(m_block);
}

void TetrisBlock::translate(float x, float y)
{
	sf::Vector2f pos = m_block.getPosition();
	pos.x += x;
	pos.y += y;
	pos.x = std::clamp(pos.x, _s_minX, _s_maxX);
	pos.y = std::clamp(pos.y, _s_minY, _s_maxY);
	setPosition(pos);
}

void TetrisBlock::translate(int x, int y)
{
	translate((float)x, (float)y);
}

void TetrisBlock::init(const sf::Vector2f &pos, const sf::Color &color)
{
	setPosition(pos);
	m_block.setFillColor(color);
	m_block.setOutlineThickness((float)_s_thickness);
	m_block.setOutlineColor(sf::Color::Black);
}

float TetrisBlock::_s_minX = 0.0f;
float TetrisBlock::_s_maxX = 0.0f;
float TetrisBlock::_s_minY = 0.0f;
float TetrisBlock::_s_maxY = 0.0f;
}