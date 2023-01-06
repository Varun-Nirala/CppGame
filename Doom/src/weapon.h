#ifndef __WEAPON_H__
#define __WEAPON_H__

#include "animatedSpriteObject.h"

class Game;

class Weapon : public AnimatedSpriteObject
{
public:
	explicit Weapon(Game* pGame);

	void init(const std::string& folderPath, const glm::vec2& pos = { 11.5f, 3.5f }, float scale = 0.8f, float shift = 0.16f, int animationTime = 120);

	void update(float dt) override;
	void draw() override;

	void setReloading(bool val) { m_bReloading = val; }
	bool reloading() const { return m_bReloading; }
	int damage() const { return m_damage; }

private:
	void animateShot();
private:
	bool		m_bReloading{ false };
	int			m_frameCounter{};
	int			m_damage{ 50 };
};

#endif //!__WEAPON_H__