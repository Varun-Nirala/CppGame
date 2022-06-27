#include "grid.h"


Grid::Grid(glm::vec2 particleSize, glm::vec2 startPos, int windowWidth, int windowHeight)
{
    int rows = int(windowWidth / particleSize.x);
    int cols = int(windowHeight / particleSize.y);

    m_grid.resize(rows, std::vector<Block>(cols, Block{}));

    glm::vec2 pos{ startPos };

    for (size_t i = 0, rsize = m_grid.size(); i < rsize; ++i)
    {
        for (size_t j = 0, csize = m_grid[i].size(); j < csize; ++j)
        {
            m_grid[i][j].position = pos;
            pos.x += particleSize.x;
        }
        pos.y += particleSize.y;
        pos.x = startPos.x;
    }
}

const std::vector<Block>& Grid::operator[](size_t index) const
{
    return m_grid.at(index);
}

std::vector<Block>& Grid::operator[](size_t index)
{
    return m_grid[index];
}
