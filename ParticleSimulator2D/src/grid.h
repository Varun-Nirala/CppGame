#pragma once

#include "particle.h"
#include <vector>

struct Block
{
	Particle			*particle{};
	glm::vec2			position{};
};

enum class Direction
{
	BELOW,
	BELOW_LEFT,
	BELOW_RIGHT,
	LEFT,
	RIGHT
};

class Grid
{
public:
	Grid(glm::vec2 particleSize, glm::vec2 particleScale, glm::vec2 startPos, int windowWidth, int windowHeight);

	size_t rows() const { return m_grid.size(); }
	size_t cols() const { return m_grid[0].size(); }

	void move(size_t srcR, size_t srcC, Direction dir);

	const std::vector<Block>& operator[](size_t index) const;
	std::vector<Block>& operator[](size_t index);

	bool isEmpty(size_t r, size_t c) const { return m_grid[r][c].particle == nullptr; }

	bool isEmpty(size_t r, size_t c, Direction dir) const;

private:
	std::vector<std::vector<Block>>			m_grid;
};