#include "player.h"
#include "game.h"

#include "common/logger.h"
#include "common/constants.h"

Player::Player(Game *pGame)
	: m_pGame(pGame)
	, m_weapon(pGame)
{
}

void Player::init()
{
	m_weapon.init(R"(.\resources\sprites\weapon\shotgun)", { 11.5f, 3.5f }, 0.4f, 0.16f, 90);
}

void Player::update(float dt)
{
	movement(dt);
	mouseControl(dt);
	singleFire();
	recoverHealth(dt);
	m_weapon.update(dt);
}

void Player::draw()
{
#ifdef SHOW_IN_BLUEPRINT
	drawLineOfSight();
	drawPlayer();
#endif
	m_weapon.draw();
}

glm::ivec2 Player::mapPosition() const
{
	return glm::ivec2{ m_position };
}

void Player::reset()
{
	m_position = PLAYER_POS;
	m_angle = PLAYER_ANGLE;
	m_health = PLAYER_MAX_HEALTH;
	m_bShot = false;
	m_playerRelative = 0;
}

void Player::getDamage(int damage)
{
	if (m_health >= damage)
	{
		m_health -= damage;
	}
	m_pGame->objectRenderer().setPlayPlayerDamage();
	m_pGame->getSound(PLAYER_PAIN)->play();
	checkGameOver();
}

void Player::singleFire()
{
	for (const SDL_Event& event : m_pGame->mouseEvents())
	{
		if (!m_bShot 
			&& event.type == SDL_MOUSEBUTTONDOWN 
			&& event.button.button == SDL_BUTTON_LEFT
			&& !m_pGame->player().weapon().reloading())
		{
			m_pGame->getSound(SoundIndex::SHOTGUN)->play();
			m_bShot = true;
			m_pGame->player().weapon().setReloading(true);
		}
	}
}

void Player::movement(float dt)
{
	const float sinVal = glm::sin(m_angle);
	const float cosVal = glm::cos(m_angle);

	const float speed{ PLAYER_SPEED * dt };

	const float speedSin{ speed * sinVal };
	const float speedCos{ speed * cosVal };

	float dx{};
	float dy{};

	for (const SDL_Event& event : m_pGame->keyboardEvents())
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.sym)
			{
				case SDLK_w:
					dx += speedCos;
					dy += speedSin;
					break;

				case SDLK_s:
					dx += -speedCos;
					dy += -speedSin;
					break;

				case SDLK_a:
					dx += speedSin;
					dy += -speedCos;
					break;

				case SDLK_d:
					dx += -speedSin;
					dy += speedCos;
					break;
			}
			checkWallCollision(dt, dy, dx);
		}
	}

	m_angle = std::fmod(m_angle, TAU);
}

void Player::mouseControl(float dt)
{
	m_playerRelative = 0;
	int x{};
	int y{};

	for (const SDL_Event& event : m_pGame->mouseEvents())
	{
		switch (event.type)
		{
			case SDL_MOUSEMOTION:
				x = event.motion.x;
				y = event.motion.y;

				if (x < MOUSE_BORDER_LEFT || x > MOUSE_BORDER_RIGHT)
				{
					SDL_WarpMouseInWindow(m_pGame->window(), HALF_WIDTH, HALF_HEIGHT);
				}

				m_playerRelative = event.motion.xrel;
				m_playerRelative = std::max(-MOUSE_MAX_REL, std::min(MOUSE_MAX_REL, m_playerRelative));
				m_angle += m_playerRelative * MOUSE_SENSTIVITY * dt;
				break;

			case SDL_MOUSEBUTTONDOWN:
				if (event.button.button == SDL_BUTTON_LEFT)
				{
					;
				}
				else if (event.button.button == SDL_BUTTON_RIGHT)
				{
					;
				}
				else if (event.button.button == SDL_BUTTON_MIDDLE)
				{
					;
				}
				break;

			case SDL_MOUSEBUTTONUP:
				break;

			default:
				break;
		}
	}
}

bool Player::checkWall(int y, int x)
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

void Player::checkWallCollision(float dt, float dy, float dx)
{
	const float scale = PLAYER_SIZE_SCALE / dt;
	if (!checkWall(int(m_position.y), int(m_position.x + dx * scale)))
	{
		m_position.x += dx;
	}

	if (!checkWall(int(m_position.y + dy * scale), int(m_position.x)))
	{
		m_position.y += dy;
	}
}

void Player::recoverHealth(float dt)
{
	if (m_health < PLAYER_MAX_HEALTH && checkHealthRecoveryDelay(dt))
	{
		++m_health;
	}
}

void Player::checkGameOver()
{
	if (m_health < 1)
	{
		m_pGame->setGameOver();
	}
}

bool Player::checkHealthRecoveryDelay(float dt)
{
	m_prevTime += dt;
	if (m_prevTime >= m_healthRecoveryDelay)
	{
		m_prevTime = 0;
		return true;
	}
	return false;
}

void Player::drawLineOfSight()
{
	SDL_Color c = convert(kCOLOR_YELLOW);

	SDL_SetRenderDrawColor(m_pGame->renderer(), c.r, c.g, c.b, c.a);

	SDL_RenderDrawLine(m_pGame->renderer(),
		(int)(m_position.x * 100),
		(int)(m_position.y * 100),
		(int)(m_position.x * 100 + WIDTH * glm::cos(m_angle)),
		(int)(m_position.y * 100 + WIDTH * glm::sin(m_angle)));
}

void Player::drawPlayer()
{
	SDL_Color c = convert(kCOLOR_GREEN);

	SDL_SetRenderDrawColor(m_pGame->renderer(), c.r, c.g, c.b, c.a);

	//SDL_RenderDrawPoint(m_pGame->renderer(), (int)(m_position.x * 100), (int)(m_position.y * 100));
	SDL_Rect rect;
	rect.w = 10;
	rect.h = 10;
	rect.x = int(m_position.x * 100 - rect.w / 2.0f);
	rect.y = int(m_position.y * 100 - rect.h / 2.0f);

	SDL_RenderFillRect(m_pGame->renderer(), &rect);
}