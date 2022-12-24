#include "map.h"
#include "game.h"

#include "common/logger.h"

#include <SDL.h>

Map::Map(Game* pGame)
	: m_pGame(pGame)
{
	m_map =
	{
		{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' },
		{ '1', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '1' },
		{ '1', '_', '_', '1', '1', '1', '1', '_', '_', '_', '1', '1', '1', '_', '_', '1' },
		{ '1', '_', '_', '_', '_', '_', '1', '_', '_', '_', '_', '_', '1', '_', '_', '1' },
		{ '1', '_', '_', '_', '_', '_', '1', '_', '_', '_', '_', '_', '1', '_', '_', '1' },
		{ '1', '_', '_', '1', '1', '1', '1', '_', '_', '_', '_', '_', '1', '_', '_', '1' },
		{ '1', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '_', '1' },
		{ '1', '_', '_', '_', '_', '_', '_', '1', '_', '_', '_', '_', '_', '_', '_', '1' },
		{ '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1', '1' }
	};
}

Map::Map(Game* pGame, const GridMap& map)
	: m_pGame(pGame)
	, m_map(map)
{
}

bool Map::isValid(int r, int c) const
{
	return r >= 0 && r < m_map.size() && c >= 0 && c < m_map[0].size();
}

void Map::draw()
{
	const SDL_Color color{ convert(kCOLOR_DARK_GRAY) };

	for (int r = 0, maxRows = (int)rows(); r < maxRows; ++r)
	{
		for (int c = 0, maxCols = (int)cols(); c < maxCols; ++c)
		{
			if (m_map[r][c] == FILLED_CELL)
			{
				drawRectanlge(c * 100, r * 100, 100, 100, false, color);
			}
		}
	}
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