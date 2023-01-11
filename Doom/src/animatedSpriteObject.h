#ifndef __ANIMATED_SPRITE_OBJECT_H__
#define __ANIMATED_SPRITE_OBJECT_H__

#include "spriteObject.h"
#include <deque>
#include <string>

class AnimatedSpriteObject : public SpriteObject
{
public:
	static AnimatedSpriteObject* createAnimatedSpriteObject(Game* pGame)
	{
		return new AnimatedSpriteObject(pGame);
	}

	~AnimatedSpriteObject() { clear(); }
	explicit AnimatedSpriteObject(Game* pGame);

	void init(const std::string& folderPath, const glm::vec2& pos = { 11.5f, 3.5f }, float scale = 0.8f, float shift = 0.16f, int animationTime = 120);
	void update(float dt) override;
	void draw() override;

	int numberOfImages() const { return m_numberOfImages; }

protected:
	void animateSprite();
	void checkAnimationTime(float dt);

	void clear();

protected:
	int							m_numberOfImages{};
	int							m_animationTime{};
	std::deque<Texture *>		m_animationTextures;
	float						m_animationPrevTime{};
	bool						m_bAnimationTrigger{ false };
};

#endif //!__ANIMATED_SPRITE_OBJECT_H__