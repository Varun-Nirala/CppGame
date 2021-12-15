#include "Game.h"
#include "Common.h"
#include <vector>

namespace nsTetris
{
Game::~Game()
{
	closeGame();
}

void Game::initialize(const sf::RenderWindow& window, int numOfHorizontalBlock, int numOfVerticalBlock)
{
	m_nBlockHorizontally = numOfHorizontalBlock;
	m_nBlockVertically = numOfVerticalBlock;
	createBoundary(window, nsTetris::TetrisBlock::getSize(), nsTetris::TetrisBlock::getSize(), _kDEFAULT_THICKNESS);
	setUpKeyboardHandle();
}

void Game::createBoundary(const sf::RenderWindow& window, int topBottomSpacing, int leftRightSpacing, int thickNess)
{
	int width = window.getSize().x;
	int height = window.getSize().y;

	topBottomSpacing -= thickNess;
	leftRightSpacing -= thickNess;

	m_topLeft.x = (float)leftRightSpacing;
	m_topLeft.y = (float)topBottomSpacing;

	m_bottomRight.x = m_topLeft.x + width - 2 * leftRightSpacing;
	m_bottomRight.y = m_topLeft.y + height - 2 * topBottomSpacing;

	sf::Vector2f horizontal( m_bottomRight.x - m_topLeft.x, (float)thickNess );
	sf::Vector2f vertical( (float)thickNess, m_bottomRight.y - m_topLeft.y );

	m_border[0].setSize(vertical);
	m_border[1].setSize(vertical);

	m_border[2].setSize(horizontal);
	m_border[3].setSize(horizontal);

	m_border[0].setPosition(m_topLeft);
	m_border[1].setPosition(m_bottomRight.x, m_topLeft.y);

	m_border[2].setPosition(m_topLeft);
	m_border[3].setPosition(m_topLeft.x, m_bottomRight.y);

	m_shapeStartPos.x = m_topLeft.x + thickNess;
	m_shapeStartPos.y = m_topLeft.y + thickNess;

	m_shapeStartPos.x += nsTetris::TetrisBlock::getSize() * (m_nBlockHorizontally - 1);
	m_shapeStartPos.x /= 2;
}

void Game::update(const float elapsedSec)
{
	if (!m_currShape)
	{
		m_currShape = getRandShape();
	}
	m_currShape->update(elapsedSec);
}

void Game::render(sf::RenderWindow& window) const
{
	renderBoundary(window);
	if (m_currShape)
	{
		m_currShape->render(window);
	}
}

void Game::handleInput(const sf::Event& currEvent)
{
	if (m_currShape && m_commandMap.count(currEvent.key.code))
	{
		m_commandMap[currEvent.key.code]->execute(*m_currShape);
	}
}

void Game::renderBoundary(sf::RenderWindow& w) const
{
	for (auto &b : m_border)
	{
		w.draw(b);
	}
}

TetrisShape* Game::getRandShape() const
{
	int randNum = getRandomNumber(0, kNUM_OF_SHAPES - 1);
	TetrisShape* shape{};
	sf::Vector2f dir(0, 1);
	switch (randNum)
	{
		case 0:
			shape = new Shape_I(m_shapeStartPos, dir);
			break;
		case 1:
			shape = new Shape_O(m_shapeStartPos, dir);
			break;
		case 2:
			shape = new Shape_T(m_shapeStartPos, dir);
			break;
		case 3:
			shape = new Shape_J(m_shapeStartPos, dir);
			break;
		case 4:
			shape = new Shape_L(m_shapeStartPos, dir);
			break;
		case 5:
			shape = new Shape_Z(m_shapeStartPos, dir);
			break;
		case 6:
			shape = new Shape_S(m_shapeStartPos, dir);
			break;
		default:
			break;
	}
	if (shape)
	{
		shape->init();
	}
	else
	{
		assert(shape && "Unknown Rand");
	}
	return shape;
}

void Game::setUpKeyboardHandle()
{
	m_commandMap[sf::Keyboard::Left] = std::make_unique<MoveLeftCmd>(MoveLeftCmd());
	m_commandMap[sf::Keyboard::Right] = std::make_unique<MoveRightCmd>(MoveRightCmd());
	m_commandMap[sf::Keyboard::Down] = std::make_unique<MoveDownCmd>(MoveDownCmd());
	m_commandMap[sf::Keyboard::Up] = std::make_unique<ToggleShapeCmd>(ToggleShapeCmd());
}

void Game::closeGame()
{
	delete m_currShape;
	m_commandMap.clear();
}
}
