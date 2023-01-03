#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <glm/glm.hpp>

class Game;

class Player
{
public:
	explicit Player(Game* pGame);

	void update(float dt);

	void draw();

	glm::vec2 mapPosition();

	const glm::vec2& position() const { return m_position; }
	glm::vec2& position() { return m_position; }

	void setPosition(const glm::vec2& pos) { m_position = pos; }

	float angle() const { return m_angle; }
	void setAngle(float angle) { m_angle = angle; }

	int relative() const { return m_playerRelative; }

	void setShot(bool val) { m_bShot = val; }
	bool isShot() const { return m_bShot; }
private:
	void singleFire();

	void movement(float dt);
	void mouseControl(float dt);

	bool checkWall(int x, int y);

	void checlWallCollision(float dt, float dx, float dy);

	void drawLineOfSight();
	void drawPlayer();

private:
	Game			*m_pGame{};
	glm::vec2		m_position{};
	float			m_angle{};
	int				m_playerRelative{};

	bool			m_bShot{ false };
};

#endif // !__PLAYER_H__