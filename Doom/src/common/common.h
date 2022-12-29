#ifndef __COMMON_H__
#define __COMMON_H__

#include "../texture.h"

struct Line
{
	SDL_Point		p1;
	SDL_Point		p2;

	Line() = default;

	Line(int x1, int y1, int x2, int y2)
	{
		p1 = { x1, y1 };

		p2 = { x2, y2 };
	}

	Line(SDL_Point point1, SDL_Point point2)
		: p1(point1)
		, p2(point2)
	{}
};

struct Rectangle
{
	SDL_Rect		rect{};
	SDL_Color		color{};

	Rectangle() = default;

	Rectangle(const SDL_Rect& r, const SDL_Color& c)
		: rect(r)
		, color(c)
	{}
};

struct RaycastingResult
{
	float			depth{};
	float			projectionHeight{};
	float			offset{};
	char			textureKey{};

	RaycastingResult() = default;

	RaycastingResult(float depth, float projectionHeight, char textureKey, float offset)
	{
		this->depth = depth;
		this->projectionHeight = projectionHeight;
		this->textureKey = textureKey;
		this->offset = offset;
	}
};

struct TextureObject
{
	Texture			*pTexture{};
	float			depth{};
	SDL_Rect		srcRect{};
	SDL_Rect		dstRect{};
};

#endif //!__COMMON_H__