#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <algorithm>
#include "BattleShip.h"
#include "Bullet.h"

namespace AsteroidNS
{
template<typename T>
inline void deleteVector(std::vector<T>& v)
{
	for (size_t i = 0; i < v.size(); ++i)
	{
		delete v[i];
	}
	v.clear();
}

class Game
{
public:
	Game(sf::RenderWindow& rw);

	~Game();

	void update();

	void render() const;
private:
	sf::RenderWindow				&m_window;
	BattleShip						m_player{};
	std::vector<Bullet*>			m_bullets{};
	sf::Clock						m_clock{};
	sf::Color						m_clearColor{ sf::Color::Blue };
};
}
#endif //__GAME_H__
