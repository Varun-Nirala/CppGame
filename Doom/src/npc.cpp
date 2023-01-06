#include "npc.h"
#include "game.h"

NPC::NPC(Game* pGame)
	: AnimatedSpriteObject(pGame)
{
}

void NPC::init(const std::string& folderPath, const glm::vec2& pos, float scale, float shift, int animationTime)
{
	// Attack
	AnimatedSpriteObject::init(folderPath + "soldier\\attack", pos, scale, shift, animationTime);
	m_animations[ATTACK] = m_animationTextures;

	// Death
	m_numberOfImages = 0;
	m_animationTextures.clear();
	AnimatedSpriteObject::init(folderPath + "soldier\\death", pos, scale, shift, animationTime);
	m_animations[DEATH] = m_animationTextures;

	// pain
	m_numberOfImages = 0;
	m_animationTextures.clear();
	AnimatedSpriteObject::init(folderPath + "soldier\\pain", pos, scale, shift, animationTime);
	m_animations[PAIN] = m_animationTextures;

	// Walk
	m_numberOfImages = 0;
	m_animationTextures.clear();
	AnimatedSpriteObject::init(folderPath + "soldier\\walk", pos, scale, shift, animationTime);
	m_animations[WALK] = m_animationTextures;

	// Idle
	m_numberOfImages = 0;
	m_animationTextures.clear();
	AnimatedSpriteObject::init(folderPath + "soldier\\idle", pos, scale, shift, animationTime);
	m_animations[IDLE] = m_animationTextures;
}

void NPC::update(float dt)
{
	AnimatedSpriteObject::update(dt);
	run();
}

void NPC::draw()
{
	AnimatedSpriteObject::draw();
#ifdef SHOW_IN_BLUEPRINT
	drawNPC();
	drawRay();
#endif
}

glm::ivec2 NPC::mapPos()
{
	return glm::ivec2{ m_position };
}

bool NPC::raycastPlayerNPC()
{
	if (m_pGame->player().mapPosition() == mapPos())
	{
		return true;
	}

	float wallDist_v{};
	float wallDist_h{};
	float playerDist_v{};
	float playerDist_h{};

	const float px = m_pGame->player().position().x;
	const float py = m_pGame->player().position().y;

	const int map_x = m_pGame->player().mapPosition().x;
	const int map_y = m_pGame->player().mapPosition().y;

	const float rayAngle = m_thetaAngle;

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
		const int tileHorz_x = (int)xHor;
		const int tileHorz_y = (int)yHor;
		if (tileHorz_x == mapPos().x && tileHorz_y == mapPos().y)
		{
			playerDist_h = depthHor;
			break;
		}
		if (m_pGame->map().isValid(tileHorz_y, tileHorz_x) && m_pGame->map()[tileHorz_y][tileHorz_x] != EMPTY_CELL)
		{
			wallDist_h = depthHor;
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
		const int tileVert_x = (int)xVert;
		const int tileVert_y = (int)yVert;
		if (tileVert_x == mapPos().x && tileVert_y == mapPos().y)
		{
			playerDist_v = depthVert;
			break;
		}
		if (m_pGame->map().isValid(tileVert_y, tileVert_x) && m_pGame->map()[tileVert_y][tileVert_x] != EMPTY_CELL)
		{
			wallDist_v = depthVert;
			break;
		}

		xVert += dx;
		yVert += dy;
		depthVert += deltaDepth;
	}

	const float playerDist = std::max(playerDist_v, playerDist_h);
	const float wallDist = std::max(wallDist_v, wallDist_h);

	if ((0 < (int)playerDist && playerDist < wallDist) || !wallDist)
	{
		return true;
	}
	return false;
}

void NPC::checkHealth()
{
	if (m_health < 1)
	{
		m_bAlive = false;
		m_pGame->getSound(SoundIndex::NPC_DEATH)->play();
	}
}

void NPC::animatePain()
{
	if (m_currentAction != PAIN)
	{
		m_currentAction = PAIN;
		m_animationTextures = m_animations[PAIN];
		m_textureObject.pTexture = m_animationTextures.front();
	}
	if (m_bAnimationTrigger)
	{
		m_bPain = false;
	}
}

void NPC::animateIdle()
{
	if (m_currentAction != IDLE)
	{
		m_currentAction = IDLE;
		m_animationTextures = m_animations[IDLE];
		m_textureObject.pTexture = m_animationTextures.front();
	}
}

void NPC::animateDeath()
{
	if (!m_bAlive)
	{
		if (m_bAnimationTrigger && m_frameCounter < m_animations[DEATH].size())
		{
			if (m_currentAction != DEATH)
			{
				m_currentAction = DEATH;
				m_animationTextures = m_animations[DEATH];
			}
			++m_frameCounter;
		}
	}
}

void NPC::run()
{
	if (m_bAlive)
	{
		m_bRaycastValue = raycastPlayerNPC();
		checkHit();
		m_bPain ? animatePain() : animateIdle();
	}
	else
	{
		animateDeath();
	}
}

void NPC::checkHit()
{
	if (m_bRaycastValue && m_pGame->player().isShot())
	{
		if ((HALF_WIDTH - m_spriteHalfWidth) < m_screenX
			&& m_screenX < (HALF_WIDTH + m_spriteHalfWidth))
		{
			m_pGame->getSound(SoundIndex::NPC_PAIN)->play();
			m_pGame->player().setShot(false);
			m_bPain = true;
			m_health -= m_pGame->weapon().damage();
			checkHealth();
		}
	}
}

void NPC::drawRay()
{
	SDL_Color c = convert(kCOLOR_ORANGE);
	SDL_SetRenderDrawColor(m_pGame->renderer(), c.r, c.g, c.b, c.a);

	if (m_bRaycastValue)
	{
		SDL_RenderDrawLine(m_pGame->renderer(), int(100 * m_pGame->player().position().x), int(100 * m_pGame->player().position().y)
		, int(100 * m_position.x), int(100 * m_position.y));
	}
}

void NPC::drawNPC()
{
	SDL_Color c = convert(kCOLOR_RED);

	SDL_SetRenderDrawColor(m_pGame->renderer(), c.r, c.g, c.b, c.a);

	//SDL_RenderDrawPoint(m_pGame->renderer(), (int)(m_position.x * 100), (int)(m_position.y * 100));
	SDL_Rect rect;
	rect.w = 10;
	rect.h = 10;
	rect.x = int(m_position.x * 100 - rect.w / 2.0f);
	rect.y = int(m_position.y * 100 - rect.h / 2.0f);

	SDL_RenderFillRect(m_pGame->renderer(), &rect);
}