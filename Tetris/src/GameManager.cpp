#include "GameManager.h"

const int nsTetris::TetrisBlock::_s_size = nsTetris::_kDEFAULT_SIZE;
const int nsTetris::TetrisBlock::_s_thickness = nsTetris::_kDEFAULT_THICKNESS;

namespace nsTetris
{
GameManager::GameManager(int numOfHorizontalBlock, int numOfVerticalBlock, const char* name)
    :m_window(sf::VideoMode((numOfHorizontalBlock + 2) * nsTetris::TetrisBlock::getSize(), (numOfVerticalBlock + 2) * nsTetris::TetrisBlock::getSize()),
                name, sf::Style::Titlebar)
    ,m_isPaused(false)
{
    m_game.initialize(m_window, numOfHorizontalBlock, numOfVerticalBlock);
}

GameManager::~GameManager()
{
    closeGame();
}

void GameManager::resetClock()
{
    m_clock.restart();
}

void GameManager::startGame()
{
    m_isPaused = false;
    resetClock();
    while (m_window.isOpen())
    {
        handleInput();
        update();
        renderAndDisplay();
    }
}

void GameManager::update()
{
    sf::Time time = m_clock.getElapsedTime();
    resetClock();
    if (!m_isPaused)
    {
        // @TODO : Show pause game banner
        m_game.update(time.asSeconds());
    }
}

void GameManager::renderAndDisplay()
{
    m_window.clear();
    m_game.render(m_window);
    m_window.display();
}

void GameManager::handleInput()
{
    sf::Event event;
    if (m_window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            closeGame();
        }
        else if (event.type == sf::Event::LostFocus)
        {
            m_isPaused = true;
        }
        else if (event.type == sf::Event::GainedFocus)
        {
            m_isPaused = false;
        }
        else if (event.key.code == sf::Keyboard::Escape)
        {
            m_isPaused = !m_isPaused;
        }
        else if (!m_isPaused && event.type == sf::Event::KeyPressed)
        {
            m_game.handleInput(event);
        }
    }
}

void GameManager::closeGame()
{
    m_window.close();
}

}