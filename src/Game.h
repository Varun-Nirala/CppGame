#ifndef __GAME_H__
#define __GAME_H__

#include <vector>
#include <array>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <SFML/Graphics/RectangleShape.hpp>
#include "TetrisShapes.h"
#include "Command.h"

namespace nsTetris
{
class Game
{
	public:
		~Game();
		void initialize(const sf::RenderWindow& window, int numOfHorizontalBlock, int numOfVerticalBlock);
		void createBoundary(const sf::RenderWindow& window, int topBottomSpacing, int leftRightSpacing, int thickNess);
		void update(const float elapsedSec);
		void render(sf::RenderWindow& window) const;

		void handleInput(const sf::Event &currEvent);

	protected:
		void closeGame();
		void renderBoundary(sf::RenderWindow& window) const;
		TetrisShape* getRandShape() const;
		void setUpKeyboardHandle();

	private:
		sf::Vector2f														m_topLeft{};
		sf::Vector2f														m_bottomRight{};
		sf::Vector2f														m_shapeStartPos{};
		int																	m_nBlockHorizontally{};
		int																	m_nBlockVertically{};
		TetrisShape*														m_currShape{};
		std::vector<std::vector<TetrisBlock>>								m_tetrisGrid;
		std::array<sf::RectangleShape, 4>									m_border;
		std::unordered_map<sf::Keyboard::Key,std::unique_ptr<Command>>		m_commandMap;

};
}
#endif //__GAME_H__
