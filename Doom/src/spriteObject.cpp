#include "spriteObject.h"

#include "game.h"
#include "objectRenderer.h"
#include "texture.h"

#include "common/constants.h"
#include "common/logger.h"

SpriteObject::SpriteObject(Game* pGame)
	: m_pGame(pGame)
{
}

void SpriteObject::init(const std::string& path, const glm::vec2& pos, float scale, float shift)
{
	m_position = pos;
	m_spriteScale = scale;
	m_spriteHeightShift = shift;

	m_textureObject.pTexture = ObjectRenderer::createTexture(m_pGame, path, SDL_BLENDMODE_BLEND);

	m_imageHalfWidth = m_textureObject.pTexture->width() / 2;
	m_imageRatio = m_textureObject.pTexture->width() / (float)m_textureObject.pTexture->height();
}

void SpriteObject::update(float dt)
{
	(void)dt;
	fillObjectToRender();
}

void SpriteObject::calculateSpritePosition(float normalDistance)
{
	const float projection = SCREEN_DIST / normalDistance * m_spriteScale;

	const float projWidth = projection * m_imageRatio;
	const float projHeight = projection;

	// Scale image to projWidth and projHeight

	m_spriteHalfWidth = projWidth / 2.0f;

	const float heightShift = projHeight * m_spriteHeightShift;

	const glm::vec2 pos = { m_screenX - m_spriteHalfWidth, HALF_HEIGHT - projHeight / 2.0f + heightShift };

	m_textureObject.depth = normalDistance;

	m_textureObject.srcRect.x = 0;
	m_textureObject.srcRect.y = 0;
	m_textureObject.srcRect.w = m_textureObject.pTexture->width();
	m_textureObject.srcRect.h = m_textureObject.pTexture->height();

	m_textureObject.dstRect.x = (int)pos.x;
	m_textureObject.dstRect.y = (int)pos.y;
	m_textureObject.dstRect.w = (int)projWidth;
	m_textureObject.dstRect.h = (int)projHeight;

	m_pGame->raycasting().push_back(m_textureObject);
}

void SpriteObject::fillObjectToRender()
{
	const Player& p = m_pGame->player();

	const float dx = m_position.x - p.position().x;
	const float dy = m_position.y - p.position().y;

	m_thetaAngle = std::atan2(dy, dx);

	float deltaAngle = m_thetaAngle - p.angle();

	if ((dx < 0.0f && dy < 0.0f) || (dx > 0.0f && p.angle() > M_PI))
	{
		deltaAngle += TAU;
	}

	const float deltaRays = deltaAngle / DELTA_ANGLE;

	m_screenX = (HALF_NUM_RAYS + deltaRays) * SCALE;

	m_distance = std::hypotf(dx, dy);
	const float normalDistance = m_distance * std::cosf(deltaAngle);

	if (-m_imageHalfWidth < m_screenX && m_screenX < (WIDTH + m_imageHalfWidth) && normalDistance > 0.5f)
		calculateSpritePosition(normalDistance);
}

void SpriteObject::clear()
{
	delete m_textureObject.pTexture;
	m_textureObject.pTexture = nullptr;
}