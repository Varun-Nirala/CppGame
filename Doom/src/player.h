#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <glm/glm.hpp>
#include "common/constants.h"

class Game;

class Player
{
public:
	explicit Player(Game* pGame);

	void update(float dt);

	void draw();

	glm::ivec2 mapPosition() const;

	void reset();

	const glm::vec2& position() const { return m_position; }
	glm::vec2& position() { return m_position; }

	void setPosition(const glm::vec2& pos) { m_position = pos; }

	float angle() const { return m_angle; }
	void setAngle(float angle) { m_angle = angle; }

	int relative() const { return m_playerRelative; }

	void setShot(bool val) { m_bShot = val; }
	bool isShot() const { return m_bShot; }

	void getDamage(int damage);

	int health() const { return m_health; }
private:
	void singleFire();

	void movement(float dt);
	void mouseControl(float dt);

	bool checkWall(int y, int x);

	void checkWallCollision(float dt, float dy, float dx);

	void checkGameOver();

	void drawLineOfSight();
	void drawPlayer();

private:
	Game			*m_pGame{};
	glm::vec2		m_position{ PLAYER_POS };
	float			m_angle{ PLAYER_ANGLE };
	int				m_playerRelative{};

	bool			m_bShot{ false };
	int				m_health{ PLAYER_MAX_HEALTH };
};

#endif // !__PLAYER_H__