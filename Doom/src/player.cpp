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

void Player::movement(float dt)
{
	const float sinVal = glm::sin(m_angle);
	const float cosVal = glm::cos(m_angle);

	const float speed{ PLAYER_SPEED * dt };

	const float speedSin{ speed * sinVal };
	const float speedCos{ speed * cosVal };

	float dx{};
	float dy{};

	for (const SDL_Event& event : m_pGame->events())
	{
		if (event.type == SDL_KEYDOWN)
		{
			switch (event.key.keysym.scancode)
			{
				case SDL_SCANCODE_W:
					dx += speedCos;
					dy += speedSin;
					break;

				case SDL_SCANCODE_S:
					dx -= speedCos;
					dy -= speedSin;
					break;

				case SDL_SCANCODE_A:
					dx += speedSin;
					dy -= speedCos;
					break;

				case SDL_SCANCODE_D:
					dx -= speedSin;
					dy += speedCos;
					break;

				case SDL_SCANCODE_LEFT:
					m_angle -= PLAYER_ROT_SPEED * dt;
					break;

				case SDL_SCANCODE_RIGHT:
					m_angle += PLAYER_ROT_SPEED * dt;
					break;
			}
		}
	}

	while (m_angle >= TAU)
	{
		m_angle -= TAU;
	}

	checlWallCollision(dx, dy);
}

bool Player::checkWall(int x, int y)
{
	return m_pGame->map()[y][x] == FILLED_CELL;
}

void Player::checlWallCollision(float dx, float dy)
{
	if (!checkWall(int(m_position.x + dx), int(m_position.y)))
	{
		m_position.x += dx;
	}

	if (!checkWall(int(m_position.x), int(m_position.y + dy)))
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