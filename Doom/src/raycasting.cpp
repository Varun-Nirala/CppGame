#include "raycasting.h"

#include "game.h"

Raycasting::Raycasting(Game* pGame)
	: m_pGame(pGame)
{
	m_rays.resize(NUM_RAYS);
	m_rectangles.resize(NUM_RAYS);
}

void Raycasting::raycast()
{
	const float px = m_pGame->player().position().x;
	const float py = m_pGame->player().position().y;

	const int map_x = (int)m_pGame->player().mapPosition().x;
	const int map_y = (int)m_pGame->player().mapPosition().y;

	float rayAngle = m_pGame->player().angle() - HALF_FOV + 0.0001f;

	for (int ray = 0; ray < NUM_RAYS; ++ray)
	{
		const float sinVal = glm::sin(rayAngle);
		const float cosVal = glm::cos(rayAngle);

		// horizontals
		float xHor{}, yHor{};
		float dx{}, dy{};

		if (sinVal > 0.0f)
		{
			yHor = map_y + 1.0f;
			dy = 1;
		}
		else
		{
			yHor = map_y - 0.000001f;
			dy = -1;
		}

		float depthHor = (yHor - py) / sinVal;
		xHor = px + depthHor * cosVal;

		float deltaDepth = dy / sinVal;
		dx = deltaDepth * cosVal;

		for (int d = 0; d < MAX_DEPTH; ++d)
		{
			if (m_pGame->map().isValid((int)yHor, (int)xHor) && m_pGame->map()[(int)yHor][(int)xHor] == FILLED_CELL)
			{
				break;
			}

			xHor += dx;
			yHor += dy;

			depthHor += deltaDepth;
		}

		// verticals
		float xVert{}, yVert{};

		if (cosVal > 0.0f)
		{
			xVert = map_x + 1.0f;
			dx = 1.0f;
		}
		else
		{
			xVert = map_x - 0.000001f;
			dx = -1.0f;
		}

		float depthVert = (xVert - px) / cosVal;
		yVert = py + depthVert * sinVal;

		deltaDepth = dx / cosVal;
		dy = deltaDepth * sinVal;

		for (int d = 0; d < MAX_DEPTH; ++d)
		{
			if (m_pGame->map().isValid((int)yVert, (int)xVert) && m_pGame->map()[(int)yVert][(int)xVert] == FILLED_CELL)
			{
				break;
			}

			xVert += dx;
			yVert += dy;

			depthVert += deltaDepth;
		}

		// depth
		float depth = std::min(depthHor, depthVert);

		// remove fishbowl effect
		depth *= glm::cos(m_pGame->player().angle() - rayAngle);

		// save the ray
		m_rays[ray].x1 = int(px * 100);
		m_rays[ray].y1 = int(py * 100);
		
		m_rays[ray].x2 = (int)(100 * px + 100 * depth * cosVal);
		m_rays[ray].y2 = (int)(100 * py + 100 * depth * sinVal);

		// projection
		float projHeight = SCREEN_DIST / (depth + 0.0001f);

		// save walls
		m_rectangles[ray].rectangle.x = ray * SCALE;
		m_rectangles[ray].rectangle.y = HALF_HEIGHT - (int)(projHeight / 2);
		m_rectangles[ray].rectangle.w = SCALE;
		m_rectangles[ray].rectangle.h = (int)projHeight;

		m_rectangles[ray].color.r = Uint8(255 / (1 + std::pow(depth, 5) * 0.00002f));
		m_rectangles[ray].color.g = m_rectangles[ray].color.r;
		m_rectangles[ray].color.b = m_rectangles[ray].color.r;
		m_rectangles[ray].color.a = 255;

		rayAngle += DELTA_ANGLE;
	}
}

void Raycasting::update(float dt)
{
	(void)dt;
	raycast();
}

void Raycasting::draw()
{
	//drawRays();
	drawWalls();
}

void Raycasting::drawRays()
{
	SDL_Color c = convert(kCOLOR_YELLOW);
	SDL_SetRenderDrawColor(m_pGame->renderer(), c.r, c.g, c.b, c.a);

	for (const Line& ray : m_rays)
	{
		SDL_RenderDrawLine(m_pGame->renderer(), ray.x1, ray.y1, ray.x2, ray.y2);
	}
}

void Raycasting::drawWalls()
{
	SDL_Color c = convert(kCOLOR_WHITE);
	

	for (const Rectangle &rect : m_rectangles)
	{
		SDL_SetRenderDrawColor(m_pGame->renderer(), rect.color.r, rect.color.g, rect.color.b, rect.color.a);
		SDL_RenderFillRect(m_pGame->renderer(), &(rect.rectangle));
	}
	
}