#ifndef __TETROMINO_H__
#define __TETROMINO_H__

#include <SFML/Graphics.hpp>
#include <vector>

#include "constant.h"

// Should call API in below order
// 1. clearOldCells
// 2. apply the moves
// 3. updateNewCells
// 4. draw

class Tetromino
{
public:
	explicit Tetromino(ShapeID id);

	void reset(ShapeID id);

	void clearOldCells(std::vector<std::vector<char>>& matrix);

	bool canMoveLeft(std::vector<std::vector<char>>& matrix);
	bool canMoveRight(std::vector<std::vector<char>>& matrix);
	bool canMoveDown(std::vector<std::vector<char>>& matrix);
	bool canRotateCW(std::vector<std::vector<char>>& matrix);

	bool moveLeft(std::vector<std::vector<char>>& matrix);
	bool moveRight(std::vector<std::vector<char>>& matrix);
	bool moveDown(std::vector<std::vector<char>>& matrix);
	bool rotateCW(std::vector<std::vector<char>>& matrix);

	void updateNewCells(std::vector<std::vector<char>>& matrix);

	void draw(sf::RenderWindow& window);

	char getShape() const { return m_shapes[m_id]; }

	const sf::Color& getColor() const { return m_colors[m_id]; }

	static int getNumberOfShapes() { return (int)m_shapes.size(); }
	static const sf::Color& getColor(int index) { return m_colors[index]; }
	static const char getShape(int index) { return m_shapes[index]; }
private:
	void rotateMatrix(std::vector<std::vector<bool>> &mat);
	void create_minos(char shape);

private:
	sf::Vector2i							m_position;
	std::vector<std::vector<bool>>			m_boundingBox;
	ShapeID									m_id{};
	int										m_rotationAngle{};

	static const std::vector<char>			m_shapes;
	static const std::vector<sf::Color>		m_colors;
};

#endif //!__TETROMINO_H__