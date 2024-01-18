#ifndef __CONSTANT_H__
#define __CONSTANT_H__

#include <SFML/Graphics.hpp>

constexpr float FPS = 1.0f;

constexpr float MASS_SCALER = 1.0e8f;

constexpr int FLAG_SIZE = 2;
constexpr int SAME_RADIUS = 0;
constexpr int SAME_MASS = 1;


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