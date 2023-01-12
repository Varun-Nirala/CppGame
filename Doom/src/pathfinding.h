#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__

#include "common/common.h"
#include "common/logger.h"
#include "common/constants.h"

#include <glm/glm.hpp>

#include <vector>
#include <deque>

class Game;

inline bool operator==(const glm::ivec2& val1, const glm::ivec2& val2)
{
	return val1.x == val2.x && val1.y == val2.y;
}

struct HashFunc
{
	size_t operator()(const glm::ivec2& val) const
	{
		size_t hash = val.x * 100000;
		hash += val.y;
		return hash;
	}
};

class Pathfinding
{
	using VecOfPoint = std::vector<glm::ivec2>;
public:
	explicit Pathfinding(Game* pGame);

	glm::ivec2 getPath(glm::ivec2 start, glm::ivec2 goal);
private:
	void getGraph();
	VecOfPoint getNextNodes(int y, int x);

	std::unordered_map<glm::ivec2, glm::ivec2, HashFunc> bfs(glm::ivec2 start, glm::ivec2 goal);
private:
	Game									*m_pGame{};
	VecOfPoint								m_ways;
	std::vector<std::vector<VecOfPoint>>	m_graph;
};

#endif //!__PATHFINDING_H__