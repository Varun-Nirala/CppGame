#pragma once

#include "particle.h"
#include <vector>

struct Block
{
	Particle			*particle{};
	glm::vec2			position{};
};

class Grid
{
public:
	Grid(glm::vec2 particleSize, glm::vec2 startPos, int windowWidth, int windowHeight);

	const std::vector<Block>& operator[](size_t index) const;
	std::vector<Block>& operator[](size_t index);

private:
	glm::vec2								m_blockSize{};
	std::vector<std::vector<Block>>			m_grid;
};