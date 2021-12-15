#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <SFML/Graphics.hpp>
#include "Game.h"


namespace AsteroidNS
{
class GameManager
{
	public:
        GameManager(int width = 512, int height = 256, const char* name = "Asteroids")
            :m_window(sf::VideoMode(width, height), name)
            ,m_game(m_window)
        {
            initialize();
        }

		void startGame()
		{
            while (m_window.isOpen())
            {
                m_game.update();
                m_game.render();

                m_window.display();
            }
		}

    private:
        void initialize()
        {
            // @TODO
        }

	private:
		sf::RenderWindow		m_window;
        Game                    m_game;
};
}
#endif //__GAMEMANAGER_H__