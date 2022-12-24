#ifndef __RAYCASTING_H__
#define __RAYCASTING_H__

#include "common/logger.h"
#include "common/constants.h"

#include <vector>

class Game;

struct Line
{
	using dataType = int;

	dataType x1{};
	dataType y1{};
	dataType x2{};
	dataType y2{};

	Line() = default;

	Line(dataType x1, dataType y1, dataType x2, dataType y2)
	{
		this->x1 = x1;
		this->y1 = y1;

		this->x2 = x2;
		this->y2 = y2;
	}
};

struct Rectangle
{
	SDL_Rect	rectangle;
	SDL_Color	color;

	Rectangle() = default;

	Rectangle(const SDL_Rect &rect, const SDL_Color &c)
		: rectangle(rect)
		, color(c)
	{}
};

class Raycasting
{
public:
	explicit Raycasting(Game* pGame);

	void raycast();

	void update(float dt);
	void draw();

private:
	void drawRays();
	void drawWalls();

private:
	Game					*m_pGame{};
	std::vector<Line>		m_rays;
	std::vector<Rectangle>	m_rectangles;
};

#endif //!__RAYCASTING_H__