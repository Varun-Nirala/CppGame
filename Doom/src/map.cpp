#include "map.h"
#include "game.h"

#include "common/logger.h"

#include <SDL.h>

Map::Map(Game* pGame)
	: m_pGame(pGame)
{
	// '1' = WALL_1
	// '2' = WALL_2
	// '3' = WALL_3
	// '4' = WALL_4
	// '5' = WALL_5
	m_map =
	{
		{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' },
		{ '1', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '1' },
		{ '1', '_', '_', '3', '3', '3', '3', '_', '_', '_', '2', '2', '2', '_', '_', '1' },
		{ '1', '_', '_', '_', '_', '_', '4', '_', '_', '_', '_', '_', '2', '_', '_', '1' },
		{ '1', '_', '_', '_', '_', '_', '4', '_', '_', '_', '_', '_', '2', '_', '_', '1' },
		{ '1', '_', '_', '3', '3', '3', '3', '_', '_', '_', '_', '_', '2', '_', '_', '1' },
		{ '1', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '1' },
		{ '1', '_', '_', '_', '4', '_', '_', '_', '4', '_', '_', '_', '_', '_', '_', '1' },
		{ '1', '1', '1', '3', '1', '3', '1', '1', '1', '3', '3', '3', '3', '1', '1', '1' }
	};
}

Map::Map(Game* pGame, const GridMap& map)
	: m_pGame(pGame)
	, m_map(map)
{
}

bool Map::isValid(int y, int x) const
{
	return y >= 0 && y < m_map.size() && x >= 0 && x < m_map[0].size();
}

bool Map::isValid(const glm::vec2 pos) const
{
	return isValid((int)pos.y, (int)pos.x);
}

bool Map::isValid(const glm::ivec2 pos) const
{
	return isValid(pos.y, pos.x);
}

bool Map::isEmpty(int y, int x) const
{
	return isValid(y, x) && m_map[y][x] == EMPTY_CELL;
}

bool Map::isEmpty(const glm::vec2 pos) const
{
	return isEmpty((int)pos.y, (int)pos.x);
}

bool Map::isEmpty(const glm::ivec2 pos) const
{
	return isEmpty(pos.y, pos.x);
}

void Map::draw()
{
#ifdef SHOW_IN_BLUEPRINT
	const SDL_Color color{ convert(kCOLOR_DARK_GRAY) };

	for (int y = 0, maxRows = (int)rows(); y < maxRows; ++y)		// horizontal axis
	{
		for (int x = 0, maxCols = (int)cols(); x < maxCols; ++x)	// vertical axis
		{
			if (!isEmpty(y, x))
			{
				drawRectanlge(x * 100, y * 100, 100, 100, false, color);
			}
		}
	}
#endif
}

void Map::drawRectanlge(int posX, int posY, int w, int h, bool bFilledRectange, const SDL_Color &color)
{
	SDL_Rect rect;
	rect.x = posX;
	rect.y = posY;
	rect.w = w;
	rect.h = h;

	SDL_SetRenderDrawColor(m_pGame->renderer(), color.r, color.g, color.b, color.a);

	if (bFilledRectange)
	{
		SDL_RenderFillRect(m_pGame->renderer(), &rect);
	}
	else
	{
		SDL_RenderDrawRect(m_pGame->renderer(), &rect);
	}
}