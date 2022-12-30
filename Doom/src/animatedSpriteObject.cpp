#include <filesystem>

#include "animatedSpriteObject.h"

#include "game.h"

AnimatedSpriteObject::AnimatedSpriteObject(Game* pGame)
	: SpriteObject(pGame)
{
}

void AnimatedSpriteObject::init(const std::string& folderPath, const glm::vec2& pos, float scale, float shift, int animationTime)
{
	m_animationTime = animationTime;

	bool bFirstImage = true;
	for (auto& entry : std::filesystem::directory_iterator(folderPath))
	{
		if (entry.path().extension() == ".png")
		{
			const std::string str = entry.path().generic_string();
			if (bFirstImage)
			{
				SpriteObject::init(str, pos, scale, shift);
				bFirstImage = false;
			}
			m_animationTextures.push_back(ObjectRenderer::createTexture(m_pGame, str));
		}
	}

	delete m_textureObject.pTexture;
	m_textureObject.pTexture = m_animationTextures.front();
}

void AnimatedSpriteObject::update(float dt)
{
	SpriteObject::update(dt);
	checkAnimationTime(dt);
	animateSprite();
}

void AnimatedSpriteObject::animateSprite()
{
	if (m_bAnimationTrigger)
	{
		Texture* front = m_animationTextures.front();
		m_animationTextures.pop_front();
		m_animationTextures.push_back(front);
		m_textureObject.pTexture = m_animationTextures.front();
	}
}

void AnimatedSpriteObject::checkAnimationTime(float dt)
{
	m_bAnimationTrigger = false;
	m_animationPrevTime += dt;

	if (m_animationPrevTime > m_animationTime)
	{
		m_animationPrevTime = 0.0f;
		m_bAnimationTrigger = true;
	}
}