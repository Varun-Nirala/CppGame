#include "grid.h"


Grid::Grid(glm::vec2 particleSize, glm::vec2 particleScale, glm::vec2 startPos, int windowWidth, int windowHeight)
{
    float particleW = (particleSize.x * particleScale.x);
    float particleH = (particleSize.y * particleScale.y);

    int rows = int(windowHeight / particleW);
    int cols = int(windowWidth / particleH);

    m_grid.resize(rows, std::vector<Block>(cols, Block{}));

    glm::vec2 pos{ startPos };

    for (size_t i = 0; i < rows; ++i)
    {
        for (size_t j = 0; j < cols; ++j)
        {
            m_grid[i][j].position = pos;
            pos.x += particleW;
        }
        pos.y += particleH;
        pos.x = startPos.x;
    }
}

void Grid::move(size_t srcR, size_t srcC, Direction dir)
{
    size_t dstR{}, dstC{};

    switch (dir)
    {
        case Direction::BELOW:
            dstR = srcR + 1;
            dstC = srcC;
            break;

        case Direction::BELOW_LEFT:
            dstR = srcR + 1;
            dstC = srcC - 1;
            break;

        case Direction::BELOW_RIGHT:
            dstR = srcR + 1;
            dstC = srcC + 1;
            break;

        case Direction::LEFT:
            dstR = srcR;
            dstC = srcC - 1;
            break;

        case Direction::RIGHT:
            dstR = srcR;
            dstC = srcC + 1;
            break;

        default:
            break;
    }

    m_grid[dstR][dstC].particle = m_grid[srcR][srcC].particle;
    m_grid[dstR][dstC].particle->transformations().position = m_grid[dstR][dstC].position;
    m_grid[srcR][srcC].particle = nullptr;
}

const std::vector<Block>& Grid::operator[](size_t index) const
{
    return m_grid.at(index);
}

std::vector<Block>& Grid::operator[](size_t index)
{
    return m_grid[index];
}

bool Grid::isEmpty(size_t r, size_t c, Direction dir) const
{
    bool retCode = true;
    switch (dir)
    {
        case Direction::BELOW:
            if (r >= (m_grid.size() - 1))
            {
                retCode = false;
            }
            else
            {
                retCode = isEmpty(r + 1, c);
            }
            break;

        case Direction::BELOW_LEFT:
            if (r >= (m_grid.size() - 1) || c == 0)
            {
                retCode = false;
            }
            else
            {
                retCode = isEmpty(r + 1, c - 1);
            }
            break;

        case Direction::BELOW_RIGHT:
            if (r >= (m_grid.size() - 1) || c >= (m_grid[0].size() - 1))
            {
                retCode = false;
            }
            else
            {
                retCode = isEmpty(r + 1, c + 1);
            }
            break;

        case Direction::LEFT:
            if (r >= m_grid.size() || c == 0)
            {
                retCode = false;
            }
            else
            {
                retCode = isEmpty(r, c - 1);
            }
            break;

        case Direction::RIGHT:
            if (r >= m_grid.size() || c >= (m_grid[0].size() - 1))
            {
                retCode = false;
            }
            else
            {
                retCode = isEmpty(r, c + 1);
            }
            break;
        default:
            break;
    }
    return retCode;
}
