#include "weapon.h"
#include "common/constants.h"
#include "game.h"

Weapon::Weapon(Game* pGame)
	: m_weaponAnimation(pGame)
	, m_pGame(pGame)
{
}

void Weapon::init(const std::string& folderPath, const glm::vec2& pos, float scale, float shift, int animationTime)
{
	m_weaponAnimation.init(folderPath, pos, scale, shift, animationTime);

	const int width = m_weaponAnimation.textureObject().pTexture->width();
	const int height = m_weaponAnimation.textureObject().pTexture->height();

	m_weaponAnimation.setPosition({ (HALF_WIDTH - (width * scale) / 2.0f), float(HEIGHT - (height * scale)) });

	m_weaponAnimation.textureObject().srcRect = { 0, 0, width, height };

	m_weaponAnimation.textureObject().dstRect = { (int)m_weaponAnimation.position().x, (int)m_weaponAnimation.position().y, int(width * scale), int(height * scale)};
}

void Weapon::update(float dt)
{
	m_weaponAnimation.checkAnimationTime(dt);
}

void Weapon::draw()
{
#ifndef SHOW_IN_BLUEPRINT
	
	SDL_RenderCopy(
		m_pGame->renderer(), 
		m_weaponAnimation.textureObject().pTexture->texture(), 
		&m_weaponAnimation.textureObject().srcRect, 
		&m_weaponAnimation.textureObject().dstRect);

	animateShot();
#endif
}

void Weapon::animateShot()
{
	if (m_bReloading)
	{
		m_pGame->player().setShot(false);
		if (m_weaponAnimation.animationTriggered())
		{
			m_weaponAnimation.animateSprite();
			++m_frameCounter;

			if (m_frameCounter == m_weaponAnimation.numberOfImages())
			{
				m_bReloading = false;
				m_frameCounter = 0;
			}
		}
	}
}