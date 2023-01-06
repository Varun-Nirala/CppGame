#include "weapon.h"
#include "common/constants.h"
#include "game.h"

Weapon::Weapon(Game* pGame)
	: AnimatedSpriteObject(pGame)
{}

void Weapon::init(const std::string& folderPath, const glm::vec2& pos, float scale, float shift, int animationTime)
{
	AnimatedSpriteObject::init(folderPath, pos, scale, shift, animationTime);

	const int width = m_textureObject.pTexture->width();
	const int height = m_textureObject.pTexture->height();

	m_position.x = HALF_WIDTH - (width * scale) / 2.0f;
	m_position.y = float(HEIGHT - (height * scale));

	m_textureObject.srcRect = { 0, 0, width, height };

	m_textureObject.dstRect = { (int)m_position.x, (int)m_position.y, int(width * scale), int(height * scale) };
}

void Weapon::update(float dt)
{
	checkAnimationTime(dt);
}

void Weapon::draw()
{
#ifndef SHOW_IN_BLUEPRINT
	SDL_RenderCopy(m_pGame->renderer(), m_textureObject.pTexture->texture(), &m_textureObject.srcRect, &m_textureObject.dstRect);
	animateShot();
#endif
}

void Weapon::animateShot()
{
	if (m_bReloading)
	{
		m_pGame->player().setShot(false);
		if (m_bAnimationTrigger)
		{
			animateSprite();
			++m_frameCounter;

			if (m_frameCounter == m_numberOfImages)
			{
				m_bReloading = false;
				m_frameCounter = 0;
			}
		}
	}
}