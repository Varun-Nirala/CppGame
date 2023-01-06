#ifndef __NPC_H__
#define __NPC_H__

#include "animatedSpriteObject.h"
#include <unordered_map>

enum Action
{
	IDLE,
	WALK,
	ATTACK,
	PAIN,
	DEATH
};

class NPC : public AnimatedSpriteObject
{
public:
	NPC(Game* pGame);

	void init(const std::string& folderPath, const glm::vec2& pos = { 10.5f, 5.5f }, float scale = 0.6f, float shift = 0.38f, int animationTime = 180);
	void update(float dt) override;
	void draw() override;

	glm::ivec2 mapPos();

	bool raycastPlayerNPC();
private:
	void checkHealth();
	void animatePain();
	void animateIdle();
	void animateDeath();
	void run();
	void checkHit();
	void drawRay();
	void drawNPC();
private:
	std::unordered_map<Action, std::deque<Texture*>>	m_animations;
	int													m_attackDist{ getRandomNumber(3, 6) };
	float												m_speed{ 0.03f };
	int													m_size{ 10 };
	int													m_health{ 100 };
	int													m_attackDamage{ 10 };
	float												m_accuracy{ 0.15f };
	bool												m_bAlive{ true };
	bool												m_bPain{ false };
	Action												m_currentAction { IDLE };

	bool												m_bRaycastValue{ false };

	int													m_frameCounter{};
};

#endif //!__NPC_H__