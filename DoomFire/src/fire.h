#ifndef __FIRE_H__
#define __FIRE_H__

#include <vector>
#include "common/logger.h"

#include <SDL.h>

class Fire
{
public:
	Fire(int gridWidth, int gridHeight, int pixelWidth, int pixelHeight);

	void start();
	void stop();

	void update(float dt);
	void render(SDL_Renderer* pRenderer);

private:
	void spreadFire(int r, int c);

private:
	std::vector<std::vector<int>>		m_pixels;
	const int							m_width{};
	const int							m_height{};

	const int							m_firePixelHeight{};
	const int							m_firePixelWidth{};

	const int							m_numOfColors{ 37 };

	std::vector<std::vector<int>>		m_fireColorPallet;
};

#endif //!__FIRE_H__