#include "player.h"
#include "game.h"

#include "common/logger.h"

Player::Player(Game *pGame)
	: m_pGame(pGame)
	, m_position(PLAYER_POS)
	, m_angle(PLAYER_ANGLE)
{}

void Player::update(float dt)
{
	movement(dt);
	mouseControl(dt);
	singleFire();
}

void Player::draw()
{
	drawLineOfSight();
	drawPlayer();
}

glm::vec2 Player::mapPosition()
{
	return m_position;
}

void Player::singleFire()
{
	for (const SDL_Event& event : m_pGame->mouseEvents())
	{
		if (!m_bShot 
			&& event.type == SDL_MOUSEBUTTONDOWN 
			&& event.button.button == SDL_BUTTON_LEFT
			&& !m_pGame->weapon().reloading())
		{
			m_pGame->shotSound()->play();
			m_bShot = true;
			m_pGame->weapon().setReloading(true);
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

				/*case SDLK_LEFT:
					m_angle -= PLAYER_ROT_SPEED * dt;
					break;

				case SDLK_RIGHT:
					m_angle += PLAYER_ROT_SPEED * dt;
					break;
				*/
			}
			checlWallCollision(dt, dx, dy);
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

bool Player::checkWall(int x, int y)
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

void Player::checlWallCollision(float dt, float dx, float dy)
{
	const float scale = PLAYER_SIZE_SCALE / dt;
	if (!checkWall(int(m_position.x + dx * scale), int(m_position.y)))
	{
		m_position.x += dx;
	}

	if (!checkWall(int(m_position.x), int(m_position.y + dy * scale)))
	{
		m_position.y += dy;
	}
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