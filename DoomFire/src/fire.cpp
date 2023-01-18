#include "fire.h"

Fire::Fire(int gridWidth, int gridHeight, int pixelWidth, int pixelHeight)
	: m_pixels(gridHeight, std::vector<int>(gridWidth, 0))
	, m_width(gridWidth)
	, m_height(gridHeight)
	, m_firePixelWidth(pixelWidth)
	, m_firePixelHeight(pixelHeight)
{
	m_fireColorPallet = {
		{ 0x07,0x07,0x07 }, // near black
		{ 0x1F,0x07,0x07 },
		{ 0x2F,0x0F,0x07 },
		{ 0x47,0x0F,0x07 },
		{ 0x57,0x17,0x07 },
		{ 0x67,0x1F,0x07 },
		{ 0x77,0x1F,0x07 },
		{ 0x8F,0x27,0x07 },
		{ 0x9F,0x2F,0x07 },
		{ 0xAF,0x3F,0x07 },
		{ 0xBF,0x47,0x07 },
		{ 0xC7,0x47,0x07 },
		{ 0xDF,0x4F,0x07 },
		{ 0xDF,0x57,0x07 },
		{ 0xDF,0x57,0x07 },
		{ 0xD7,0x5F,0x07 },
		{ 0xD7,0x5F,0x07 },
		{ 0xD7,0x67,0x0F },
		{ 0xCF,0x6F,0x0F },
		{ 0xCF,0x77,0x0F },
		{ 0xCF,0x7F,0x0F },
		{ 0xCF,0x87,0x17 },
		{ 0xC7,0x87,0x17 },
		{ 0xC7,0x8F,0x17 },
		{ 0xC7,0x97,0x1F },
		{ 0xBF,0x9F,0x1F },
		{ 0xBF,0x9F,0x1F },
		{ 0xBF,0xA7,0x27 },
		{ 0xBF,0xA7,0x27 },
		{ 0xBF,0xAF,0x2F },
		{ 0xB7,0xAF,0x2F },
		{ 0xB7,0xB7,0x2F },
		{ 0xB7,0xB7,0x37 },
		{ 0xCF,0xCF,0x6F },
		{ 0xDF,0xDF,0x9F },
		{ 0xEF,0xEF,0xC7 },
		{ 0xFF,0xFF,0xFF }, // white
	};
}

void Fire::start()
{
	for (int c = 0; c < m_width; ++c)
	{
		m_pixels[m_height - 1][c] = m_numOfColors - 1;
	}
}

void Fire::stop()
{
	for (int c = 0; c < m_width; ++c)
	{
		if (m_pixels[m_height - 1][c] > 0)
		{
			m_pixels[m_height - 1][c] -= 2;
		}
	}
}

void Fire::update(float dt)
{
	(void)dt;
	// spread fire
	for (int r = 1; r < m_height; ++r)	// skipping 1st row
	{
		for (int c = 0; c < m_width; ++c)
		{
			spreadFire(r, c);
		}
	}
}

void Fire::render(SDL_Renderer *pRenderer)
{
	SDL_Rect dstRect;

	for (int r = 0; r < m_height; ++r)
	{
		for (int c = 0; c < m_width; ++c)
		{
			const std::vector<int> &color = m_fireColorPallet[m_pixels[r][c]];
			SDL_SetRenderDrawColor(pRenderer, (Uint8)color[0], (Uint8)color[1], (Uint8)color[2], 255);

			dstRect = { c * m_firePixelWidth, r * m_firePixelHeight, m_firePixelWidth, m_firePixelHeight };
			SDL_RenderFillRect(pRenderer, &dstRect);
		}
	}
}

void Fire::spreadFire(int r, int c)
{
	if (r - 1 >= 0)
	{
		if (m_pixels[r][c] == 0)
		{
			m_pixels[r - 1][c] = 0;
		}
		else
		{
			const int colorDimFactor = std::rand() % 3;

			int newX{};
			do
			{
				int xAxisFactor = std::rand() % 3;
				newX = c - xAxisFactor + 1;
			} while (newX < 0 || newX >= m_width);

			m_pixels[r - 1][newX] = m_pixels[r][c] - (colorDimFactor & 1);
		}
	}
}