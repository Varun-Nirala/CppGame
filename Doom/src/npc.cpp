#include "npc.h"
#include "game.h"

int NPC::m_staticID = 0;

NPC::NPC(Game* pGame)
	: AnimatedSpriteObject(pGame)
	, m_id(m_staticID++)
{
}

void NPC::init(const std::string& folderPath, const glm::vec2& pos, float scale, float shift, int animationTime)
{
	// Attack
	AnimatedSpriteObject::init(folderPath + "attack", pos, scale, shift, animationTime);
	m_animations[ATTACK] = m_animationTextures;

	// Death
	m_numberOfImages = 0;
	m_animationTextures.clear();
	AnimatedSpriteObject::init(folderPath + "death", pos, scale, shift, animationTime);
	m_animations[DEATH] = m_animationTextures;

	// pain
	m_numberOfImages = 0;
	m_animationTextures.clear();
	AnimatedSpriteObject::init(folderPath + "pain", pos, scale, shift, animationTime);
	m_animations[PAIN] = m_animationTextures;

	// Walk
	m_numberOfImages = 0;
	m_animationTextures.clear();
	AnimatedSpriteObject::init(folderPath + "walk", pos, scale, shift, animationTime);
	m_animations[WALK] = m_animationTextures;

	// Idle
	m_numberOfImages = 0;
	m_animationTextures.clear();
	AnimatedSpriteObject::init(folderPath + "idle", pos, scale, shift, animationTime);
	m_animations[IDLE] = m_animationTextures;

	m_nextPos = m_position;
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
	drawNextPositionBlock();
#endif
}

glm::ivec2 NPC::mapPosition() const
{
	return glm::ivec2{ m_position };
}

bool NPC::raycastPlayerNPC()
{
	if (m_pGame->player().mapPosition() == mapPosition())
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
		if (tileHorz_x == mapPosition().x && tileHorz_y == mapPosition().y)
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
		if (tileVert_x == mapPosition().x && tileVert_y == mapPosition().y)
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

void NPC::attack()
{
	if (m_bAnimationTrigger)
	{
		m_pGame->getSound(NPC_SHOT)->play();

		if (getRandomNumber(0, 100) <= m_accuracy)
		{
			m_pGame->player().getDamage(m_attackDamage);
		}
	}
}

void NPC::movement()
{
	m_nextPos = m_pGame->pathfinding().getPath(mapPosition(), m_pGame->player().mapPosition());

	const int nextX = m_nextPos.x;
	const int nextY = m_nextPos.y;

	if (m_pGame->objectHandler().isNotInNPCpos(m_nextPos))
	{
		const float angle = std::atan2(nextY + 0.5f - m_position.y, nextX + 0.5f - m_position.x);

		const float dx = std::cosf(angle) * m_speed;
		const float dy = std::sinf(angle) * m_speed;

		checkWallCollision(dy, dx);
	}
}

bool NPC::checkWall(int y, int x)
{
	if (!m_pGame->map().isValid(y, x))
	{
		return true;
	}

	if (m_pGame->map()[y][x] != EMPTY_CELL)
	{
		return true;
	}

	return false;
}

void NPC::checkWallCollision(float dy, float dx)
{
	if (!checkWall(int(m_position.y), int(m_position.x + dx * m_size)))
	{
		m_position.x += dx;
	}

	if (!checkWall(int(m_position.y + dy * m_size), int(m_position.x)))
	{
		m_position.y += dy;
	}
}

void NPC::checkHealth()
{
	if (m_health < 1)
	{
		m_bAlive = false;
		m_pGame->getSound(SoundIndex::NPC_DEATH)->play();
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

void NPC::animateWalk()
{
	if (m_currentAction != WALK)
	{
		m_currentAction = WALK;
		m_animationTextures = m_animations[WALK];
		m_textureObject.pTexture = m_animationTextures.front();
	}
}

void NPC::animateAttack()
{
	if (m_currentAction != ATTACK)
	{
		m_currentAction = ATTACK;
		m_animationTextures = m_animations[ATTACK];
		m_textureObject.pTexture = m_animationTextures.front();
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
				m_pGame->player().incrememtKillCount();
				ns_Util::Logger::LOG_MSG("Killed NPC id : ", m_id, '\n');
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

		if (m_bPain)
		{
			animatePain();
		}
		else if (m_bRaycastValue)
		{
			m_bPlayerSearchTrigger = true;

			if (m_distance < m_attackDist)
			{
				animateAttack();
				attack();
			}
			else
			{
				animateWalk();
				movement();
			}
		}
		else if (m_bPlayerSearchTrigger)
		{
			animateWalk();
			movement();
		}
		else
		{
			animateIdle();
		}
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
	if (m_bRaycastValue)
	{
		const SDL_Color c = convert(kCOLOR_ORANGE);
		SDL_SetRenderDrawColor(m_pGame->renderer(), c.r, c.g, c.b, c.a);
		SDL_RenderDrawLine(m_pGame->renderer(), int(100 * m_pGame->player().position().x), int(100 * m_pGame->player().position().y)
		, int(100 * m_position.x), int(100 * m_position.y));
	}
}

void NPC::drawNPC()
{
	const SDL_Color c = convert(kCOLOR_RED);

	SDL_SetRenderDrawColor(m_pGame->renderer(), c.r, c.g, c.b, c.a);

	//SDL_RenderDrawPoint(m_pGame->renderer(), (int)(m_position.x * 100), (int)(m_position.y * 100));
	SDL_Rect rect;
	rect.w = 10;
	rect.h = 10;
	rect.x = int(m_position.x * 100 - rect.w / 2.0f);
	rect.y = int(m_position.y * 100 - rect.h / 2.0f);

	SDL_RenderFillRect(m_pGame->renderer(), &rect);
}

void NPC::drawNextPositionBlock()
{
	SDL_Color c = convert(kCOLOR_BLUE);
	SDL_SetRenderDrawColor(m_pGame->renderer(), c.r, c.g, c.b, c.a);

	SDL_Rect rect;
	rect.w = 100;
	rect.h = 100;
	rect.x = m_nextPos.x * 100;
	rect.y = m_nextPos.y * 100;

	SDL_RenderFillRect(m_pGame->renderer(), &rect);
}

void NPC::clear()
{
	for (auto& p : m_animations)
	{
		auto& deq = p.second;
		while (!deq.empty())
		{
			delete deq.front();
			deq.pop_front();
		}
	}

	m_animations.clear();

	// clear the base class dequqe, as we have allready deallocated all memory
	m_animationTextures.clear();
}


void SoldierNPC::init(const std::string& folderPath, const glm::vec2& pos, float scale, float shift, int animationTime)
{
	NPC::init(folderPath, pos, scale, shift, animationTime);
}

void CacoDemonNPC::init(const std::string& folderPath, const glm::vec2& pos, float scale, float shift, int animationTime)
{
	NPC::init(folderPath, pos, scale, shift, animationTime);
	m_attackDist = 1;
	m_health = 150;
	m_attackDamage = 25;
	m_speed = 0.05f;
	m_accuracy = 35;
}

void CyberDemonNPC::init(const std::string& folderPath, const glm::vec2& pos, float scale, float shift, int animationTime)
{
	NPC::init(folderPath, pos, scale, shift, animationTime);
	m_attackDist = 6;
	m_health = 350;
	m_attackDamage = 15;
	m_speed = 0.055f;
	m_accuracy = 25;
}