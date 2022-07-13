#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <SFML/Graphics.hpp>
#include "Game.h"


namespace AsteroidNS
{
class GameManager
{
public:
    GameManager(int width = 600, int height = 800, const char* name = "Asteroids");

    void startGame();

private:
    void initialize();

private:
	sf::RenderWindow		m_window;
    Game                    m_game;
};
}
#endif //__GAMEMANAGER_H__