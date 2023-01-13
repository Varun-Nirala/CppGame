#include "pathfinding.h"
#include "game.h"
#include "map.h"

#include <queue>

Pathfinding::Pathfinding(Game* pGame)
	: m_pGame(pGame)
{
	m_ways = {
		{ -1,  0 },
		{  0, -1 },
		{  1,  0 },
		{  0,  1 },
		{ -1, -1 },
		{  1, -1 },
		{  1,  1 },
		{ -1,  1 }
	};

	getGraph();
}

glm::ivec2 Pathfinding::getPath(glm::ivec2 start, glm::ivec2 goal)
{
	if (start == goal)
	{
		return start;
	}

	const std::unordered_map<glm::ivec2, glm::ivec2, HashFunc> visited = bfs(start, goal);

	VecOfPoint path;

	path.push_back(goal);

	glm::ivec2 currNode = goal;
	while (currNode != start && visited.count(currNode))
	{
		path.push_back(currNode);
		currNode = visited.at(currNode);
	}
	return path.back();
}

void Pathfinding::getGraph()
{
	const Map& map = m_pGame->map();

	m_graph.resize(map.rows());
	for (size_t y = 0, rows = map.rows(); y < rows; ++y)
	{
		m_graph[y].resize(map.cols());
		for (size_t x = 0, cols = map.cols(); x < cols; ++x)
		{
			if (map[y][x] == EMPTY_CELL)
			{
				const VecOfPoint res = getNextNodes((int)y, (int)x);
				m_graph[y][x].insert(m_graph[y][x].end(), res.begin(), res.end());
			}
		}
	}
}

Pathfinding::VecOfPoint Pathfinding::getNextNodes(int y, int x)
{
	VecOfPoint res;
	for (size_t i = 0, size = m_ways.size(); i < size; ++i)
	{
		const glm::ivec2& point = m_ways[i];
		int newX = x + point.x;
		int newY = y + point.y;

		if (m_pGame->map().isValid(newY, newX) && m_pGame->map()[newY][newX] == EMPTY_CELL)
		{
			res.push_back({ newX, newY });
		}
	}
	return res;
}
std::unordered_map<glm::ivec2, glm::ivec2, HashFunc> Pathfinding::bfs(glm::ivec2 start, glm::ivec2 goal)
{
	std::queue<glm::ivec2> que;

	que.push(start);

	std::unordered_map<glm::ivec2, glm::ivec2, HashFunc> res;

	std::vector<std::vector<bool>> visited(HEIGHT, std::vector<bool>(WIDTH, false));
	
	visited[start.y][start.x] = true;

	while (!que.empty())
	{
		const glm::ivec2 currNode = que.front();
		que.pop();

		if (currNode == goal)
			break;

		const VecOfPoint& nextNodes = m_graph[currNode.y][currNode.x];

		for (const glm::ivec2 &nextNode : nextNodes)
		{
			if (!visited[nextNode.y][nextNode.x] && m_pGame->objectHandler().isNotInNPCpos(nextNode))
			{
				que.push(nextNode);
				visited[nextNode.y][nextNode.x] = true;

				res[nextNode] = currNode;
			}
		}
	}
	return res;
}