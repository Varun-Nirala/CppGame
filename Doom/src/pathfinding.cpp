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

	VecOfPoint visited = bfs(start, goal);
	return visited.back();
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

Pathfinding::VecOfPoint Pathfinding::bfs(glm::ivec2 start, glm::ivec2 goal)
{
	std::queue<glm::ivec2> que;

	que.push(start);

	std::vector<std::vector<bool>> visited(HEIGHT, std::vector<bool>(WIDTH, false));
	
	VecOfPoint res;

	while (!que.empty())
	{
		const glm::ivec2 curr = que.front();
		que.pop();

		if (curr == goal)
			break;

		const VecOfPoint& nextNodes = m_graph[curr.y][curr.x];

		for (const glm::ivec2 &nextNode : nextNodes)
		{
			if (!visited[nextNode.y][nextNode.x])
			{
				que.push(nextNode);
				visited[nextNode.y][nextNode.x] = true;

				res.push_back(nextNode);
			}
		}
	}
	return res;
}