#include "raycasting.h"

#include "game.h"

Raycasting::Raycasting(Game* pGame)
	: m_pGame(pGame)
{
	m_rays.resize(NUM_RAYS);
	m_rectangles.resize(NUM_RAYS);
	m_results.resize(NUM_RAYS);
	m_objectsToRender.resize(NUM_RAYS);
}

void Raycasting::raycast()
{
	const float px = m_pGame->player().position().x;
	const float py = m_pGame->player().position().y;

	const int map_x = (int)m_pGame->player().mapPosition().x;
	const int map_y = (int)m_pGame->player().mapPosition().y;

	float rayAngle = m_pGame->player().angle() - HALF_FOV + 0.0001f;

	char textureHor{ '1' };
	char textureVert{ '1' };

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
			dy = 1.0f;
		}
		else
		{
			yHor = map_y - 0.000001f;
			dy = -1.0f;
		}

		float depthHor = (yHor - py) / sinVal;
		xHor = px + depthHor * cosVal;

		float deltaDepth = dy / sinVal;
		dx = deltaDepth * cosVal;

		for (int d = 0; d < MAX_DEPTH; ++d)
		{
			if (m_pGame->map().isValid((int)yHor, (int)xHor) && m_pGame->map()[(int)yHor][(int)xHor] != EMPTY_CELL)
			{
				textureHor = m_pGame->map()[(int)yHor][(int)xHor];
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
			if (m_pGame->map().isValid((int)yVert, (int)xVert) && m_pGame->map()[(int)yVert][(int)xVert] != EMPTY_CELL)
			{
				textureVert = m_pGame->map()[(int)yVert][(int)xVert];
				break;
			}

			xVert += dx;
			yVert += dy;

			depthVert += deltaDepth;
		}

		// depth
		float depth{};
		char textureKey{};
		float offset{};

		if (depthVert < depthHor)
		{
			depth = depthVert;
			textureKey = textureVert;
			yVert = std::fmodf(yVert, 1.0f);
			offset = (cosVal > 0) ? yVert : (1 - yVert);
		}
		else
		{
			depth = depthHor;
			textureKey = textureHor;
			xHor = std::fmodf(xHor, 1.0f);
			offset = (sinVal > 0) ? (1 - xHor) : xHor;
		}
		
		// projection
		float projHeight = SCREEN_DIST / (depth + 0.0001f);

		// remove fishbowl effect
		depth *= glm::cos(m_pGame->player().angle() - rayAngle);

		// save the ray
		m_rays[ray].p1 = { int(px * 100), int(py * 100) };
		
		m_rays[ray].p2 = { (int)(100 * px + 100 * depth * cosVal), (int)(100 * py + 100 * depth * sinVal) };

		// save walls
		m_rectangles[ray].rect.x = ray * SCALE;
		m_rectangles[ray].rect.y = HALF_HEIGHT - (int)(projHeight / 2);
		m_rectangles[ray].rect.w = SCALE;
		m_rectangles[ray].rect.h = (int)projHeight;

		m_rectangles[ray].color.r = Uint8(255 / (1 + std::pow(depth, 5) * 0.00002f));
		m_rectangles[ray].color.g = m_rectangles[ray].color.r;
		m_rectangles[ray].color.b = m_rectangles[ray].color.r;
		m_rectangles[ray].color.a = 255;

		m_results[ray].depth = depth;
		m_results[ray].projectionHeight = projHeight;
		m_results[ray].textureKey = textureKey;
		m_results[ray].offset = offset;

		rayAngle += DELTA_ANGLE;
	}
}

void Raycasting::update(float dt)
{
	(void)dt;
	raycast();
	fillObjectsToRender();
}

void Raycasting::draw()
{
	//drawRays();
	//drawWalls();
}

void Raycasting::fillObjectsToRender()
{
	for (int ray = 0; ray < NUM_RAYS; ++ray)
	{
		const RaycastingResult& res = m_results[ray];

		m_objectsToRender[ray].depth = res.depth;
		m_objectsToRender[ray].pTexture = m_pGame->objectRenderer().getTexture(res.textureKey);

		if (res.projectionHeight < HEIGHT)
		{
			m_objectsToRender[ray].srcRect.x = int(res.offset * (TEXTURE_SIZE - SCALE));
			m_objectsToRender[ray].srcRect.y = 0;
			m_objectsToRender[ray].srcRect.w = SCALE;
			m_objectsToRender[ray].srcRect.h = TEXTURE_SIZE;

			m_objectsToRender[ray].dstRect.x = int(ray * SCALE);
			m_objectsToRender[ray].dstRect.y = HALF_HEIGHT - int(res.projectionHeight / 2);
			m_objectsToRender[ray].dstRect.w = SCALE;
			m_objectsToRender[ray].dstRect.h = (int)res.projectionHeight;
		}
		else
		{
			int textureHeight = int(TEXTURE_SIZE * HEIGHT / res.projectionHeight);

			m_objectsToRender[ray].srcRect.x = int(res.offset * (TEXTURE_SIZE - SCALE));
			m_objectsToRender[ray].srcRect.y = HALF_TEXTURE_SIZE - textureHeight / 2;
			m_objectsToRender[ray].srcRect.w = SCALE;
			m_objectsToRender[ray].srcRect.h = textureHeight;

			m_objectsToRender[ray].dstRect.x = int(ray * SCALE);
			m_objectsToRender[ray].dstRect.y = 0;
			m_objectsToRender[ray].dstRect.w = SCALE;
			m_objectsToRender[ray].dstRect.h = HEIGHT;
		}
	}
}

void Raycasting::drawRays()
{
	SDL_Color c = convert(kCOLOR_YELLOW);
	SDL_SetRenderDrawColor(m_pGame->renderer(), c.r, c.g, c.b, c.a);

	for (const Line& ray : m_rays)
	{
		SDL_RenderDrawLine(m_pGame->renderer(), ray.p1.x, ray.p1.y, ray.p2.x, ray.p2.y);
	}
}

void Raycasting::drawWalls()
{
	SDL_Color c = convert(kCOLOR_WHITE);
	
	for (const Rectangle &rect : m_rectangles)
	{
		SDL_SetRenderDrawColor(m_pGame->renderer(), rect.color.r, rect.color.g, rect.color.b, rect.color.a);
		SDL_RenderFillRect(m_pGame->renderer(), &(rect.rect));
	}
	
}