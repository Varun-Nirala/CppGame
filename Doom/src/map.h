#ifndef __MAP_H__
#define __MAP_H__

#include <SDL.h>
#include <vector>

class Game;
class Map
{
	using dataType = char;
	using GridMap = std::vector<std::vector<dataType>>;
public:
	explicit Map(Game* pGame);
	Map(Game* pGame, const GridMap &map);

	const GridMap& grid() const { return m_map; }
	GridMap& grid() { return m_map; }

	const std::vector<dataType>& operator[](size_t i) const { return m_map[i]; }
	std::vector<dataType>& operator[](size_t i) { return m_map[i]; }

	size_t rows() const { return m_map.size(); }
	size_t cols() const { return m_map[0].size(); }

	// x = horizontal axis, y = vertical axis
	bool isValid(int y, int x) const;

	void draw();

private:
	void drawRectanlge(int posX, int posY, int w, int h, bool bFilledRectange, const SDL_Color& color);

private:
	GridMap		m_map;
	Game		*m_pGame{};
};
#endif !__MAP_H__