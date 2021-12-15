#include "Common.h"
#include <random>

namespace nsTetris
{
sf::Vector2f operator*(const sf::Vector2f& lhs, const sf::Vector2f& rhs)
{
	return sf::Vector2f(lhs.x * rhs.x, lhs.y * rhs.y);
}

sf::Vector2f& operator+=(sf::Vector2f& lhs, const sf::Vector2f& rhs)
{
	lhs.x += rhs.x;
	lhs.y += rhs.y;
	return lhs;
}

sf::Vector2f& operator-=(sf::Vector2f& lhs, const sf::Vector2f& rhs)
{
	lhs.x -= rhs.x;
	lhs.y -= rhs.y;
	return lhs;
}

sf::Vector2f& operator*=(sf::Vector2f& lhs, const sf::Vector2f& rhs)
{
	lhs.x *= rhs.x;
	lhs.y *= rhs.y;
	return lhs;
}

int getRandomNumber(int min, int max)
{
	static std::random_device rd;
	static std::mt19937 gen(rd());

	std::uniform_int_distribution<> distrib(min, max);

	return distrib(gen);
}
}