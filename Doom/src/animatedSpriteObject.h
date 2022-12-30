#ifndef __ANIMATED_SPRITE_OBJECT_H__
#define __ANIMATED_SPRITE_OBJECT_H__

#include "spriteObject.h"
#include <deque>
#include <string>

class AnimatedSpriteObject : public SpriteObject
{
public:
	explicit AnimatedSpriteObject(Game* pGame);

	void init(const std::string& folderPath, const glm::vec2& pos, float scale, float shift, int animationTime);
	void update(float dt) override;
private:
	void animateSprite();
	void checkAnimationTime(float dt);

private:
	int							m_animationTime{};
	std::deque<Texture *>		m_animationTextures;
	float						m_animationPrevTime{};
	bool						m_bAnimationTrigger{ false };
};

#endif //!__ANIMATED_SPRITE_OBJECT_H__