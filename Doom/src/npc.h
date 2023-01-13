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
	static NPC* createNPC(Game* pGame)
	{
		return new NPC(pGame);
	}

	~NPC() { clear(); }
	explicit NPC(Game* pGame);

	void init(const std::string& folderPath, const glm::vec2& pos = { 10.5f, 5.5f }, float scale = 0.6f, float shift = 0.38f, int animationTime = 180);
	void update(float dt) override;
	void draw() override;

	glm::ivec2 mapPosition() const;

	bool raycastPlayerNPC();

	void attack();

	bool alive() const { return m_bAlive; }
private:
	void movement();
	bool checkWall(int y, int x);
	void checkWallCollision(float dy, float dx);

	void checkHealth();
	void animateIdle();
	void animateWalk();
	void animateAttack();
	void animatePain();
	void animateDeath();
	void run();
	void checkHit();
	void drawRay();
	void drawNPC();
	void drawNextPositionBlock();

	void clear();
private:
	std::unordered_map<Action, std::deque<Texture*>>	m_animations;
	int													m_attackDist{ getRandomNumber(3, 6) };
	float												m_speed{ 0.03f };
	int													m_size{ 10 };
	int													m_health{ 100 };
	int													m_attackDamage{ 10 };
	int													m_accuracy{ 15 };
	bool												m_bAlive{ true };
	bool												m_bPain{ false };
	Action												m_currentAction { IDLE };

	bool												m_bRaycastValue{ false };

	int													m_frameCounter{};
	bool												m_bPlayerSearchTrigger{ false };

	glm::ivec2											m_nextPos{};
};

#endif //!__NPC_H__