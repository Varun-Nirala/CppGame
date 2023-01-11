#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__

#include "common/common.h"
#include "common/logger.h"
#include "common/constants.h"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

class Game;

class Pathfinding
{
	using VecOfPoint = std::vector<glm::ivec2>;
public:
	explicit Pathfinding(Game* pGame);

	glm::ivec2 getPath(glm::ivec2 start, glm::ivec2 goal);
private:
	void getGraph();
	VecOfPoint getNextNodes(int y, int x);

	VecOfPoint bfs(glm::ivec2 start, glm::ivec2 goal);
private:
	Game									*m_pGame{};
	VecOfPoint								m_ways;
	std::vector<std::vector<VecOfPoint>>	m_graph;
};

#endif //!__PATHFINDING_H__