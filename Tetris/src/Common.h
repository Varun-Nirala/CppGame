#ifndef __COMMON_H__
#define __COMMON_H__

#include <SFML/Graphics.hpp>
#include <vector>

namespace nsTetris
{
sf::Vector2f operator*(const sf::Vector2f& lhs, const sf::Vector2f& rhs);

sf::Vector2f& operator+=(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
sf::Vector2f& operator-=(const sf::Vector2f& lhs, const sf::Vector2f& rhs);
sf::Vector2f& operator*=(const sf::Vector2f& lhs, const sf::Vector2f& rhs);

template<typename T>
inline void deleteVector(std::vector<T>& v)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		delete v[i];
	}
	v.clear();
}

int getRandomNumber(int min, int max);
}
#endif //__COMMON_H__