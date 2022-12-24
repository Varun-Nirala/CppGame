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
private:
	void movement(float dt);

	bool checkWall(int x, int y);

	void checlWallCollision(float dx, float dy);

	void drawLineOfSight();
	void drawPlayer();

private:
	Game		*m_pGame{};
	glm::vec2	m_position{};
	float		m_angle{};
};

#endif // !__PLAYER_H__