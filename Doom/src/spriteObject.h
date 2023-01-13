#ifndef __SPRITE_OBJECT_H__
#define __SPRITE_OBJECT_H__

#include <string>

#include <glm/glm.hpp>

#include <SDL.h>

#include "common/common.h"

class Game;

class SpriteObject
{
public:
	static SpriteObject* createSpriteObject(Game* pGame)
	{
		return new SpriteObject(pGame);
	}

	virtual ~SpriteObject() { clear(); }
	explicit SpriteObject(Game* pGame);

	void init(const std::string& path, const glm::vec2& pos = { 10.5f, 3.5f }, float scale = 0.7f, float shift = 0.27f);
	virtual void update(float dt);
	virtual void draw() {}

	float spriteHalfWidth() const { return m_spriteHalfWidth; }
	float screenX() const { return m_screenX; }
	float thetaAngle() const { return m_thetaAngle; }
	float distance() const { return m_distance; }

	void setPosition(const glm::vec2& pos) { m_position = pos; }

protected:
	void calculateSpritePosition(float normalDistance);
	void fillObjectToRender();
	void clear();

protected:
	Game			*m_pGame{};
	TextureObject	m_textureObject{};
	glm::vec2		m_position{};

	int				m_imageHalfWidth{};
	float			m_imageRatio{};
	float			m_spriteScale{};
	float			m_spriteHeightShift{};
	float			m_spriteHalfWidth{};
	float			m_screenX{};
	float			m_thetaAngle{};
	float			m_distance{};
};

#endif //!__SPRITE_OBJECT_H__