#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include <SFML/Graphics.hpp>

constexpr int CELL_SIZE{ 8 };
constexpr int COLUMNS{ 10 };
constexpr int ROWS{ 20 };
constexpr int SCREEN_RESIZE{ 4 };

constexpr int SCORE_PER_LINE{ 10 };

enum Action
{
	LEFT,
	RIGHT,
	DOWN,
	SPACE,
	ACTION_MAX
};

enum ShapeID
{
	ID_I,
	ID_J,
	ID_L,
	ID_O,
	ID_S,
	ID_T,
	ID_Z,
	ID_EMPTY,
	ID_GHOST
};

constexpr char EMPTY_CELL{ '#' };

constexpr char SHAPE_I{ 'I' };
constexpr char SHAPE_J{ 'J' };
constexpr char SHAPE_L{ 'L' };
constexpr char SHAPE_O{ 'O' };
constexpr char SHAPE_S{ 'S' };
constexpr char SHAPE_T{ 'T' };
constexpr char SHAPE_Z{ 'Z' };

const sf::Color COLOR_EMPTY_CELL{ 36, 36, 85 };		// BLUEISH
const sf::Color COLOR_GHOST_CELL{ 73, 73, 85 };		// GRAY

const sf::Color COLOR_I{ 0, 219, 255 };				// SKY BLUE
const sf::Color COLOR_J{ 0, 36, 255 };				// BLUE
const sf::Color COLOR_L{ 255, 146, 0 };				// ORANGE
const sf::Color COLOR_O{ 255, 219, 0 };				// YELLOW
const sf::Color COLOR_T{ 146, 0, 255 };				// GREEN
const sf::Color COLOR_S{ 0, 219, 0 };				// PURPLE
const sf::Color COLOR_Z{ 219, 0, 0 };				// RED

#endif //!__CONSTANT_H__