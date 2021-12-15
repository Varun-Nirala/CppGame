#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Command.h"

namespace nsTetris
{
class GameManager
{
	public:
        GameManager(int numOfHorizontalBlock, int numOfVerticalBlock, const char* name);
        ~GameManager();
        void resetClock();
        void startGame();

        void update();
        void renderAndDisplay();
        void handleInput();

    private:
        void closeGame();

	private:
		sf::RenderWindow		                            m_window;
        sf::Clock				                            m_clock;
        Game                                                m_game;
        bool                                                m_isPaused{false};
};
}
#endif //__GAMEMANAGER_H__