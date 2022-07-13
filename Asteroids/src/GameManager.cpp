
#include "GameManager.h"

using namespace AsteroidNS;

GameManager::GameManager(int width, int height, const char* name)
    :m_window(sf::VideoMode(width, height), name)
    ,m_game(m_window)
{
    initialize();
}

void GameManager::startGame()
{
    while (m_window.isOpen())
    {
        m_game.update();
        m_game.render();

        m_window.display();
    }
}


void GameManager::initialize()
{
    // @TODO
}