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
	explicit SpriteObject(Game* pGame);

	void init(const std::string& path, const glm::vec2& pos = { 10.5f, 3.5f }, float scale = 0.7f, float shift = 0.27f);
	virtual void update(float dt);
	virtual void draw() {}

protected:
	void calculateSpritePosition(float screenX, float normalDistance);
	void fillObjectToRender();

protected:
	Game			*m_pGame{};
	TextureObject	m_textureObject{};
	glm::vec2		m_position{};

	int				m_imageHalfWidth{};
	float			m_imageRatio{};
	float			m_spriteScale{};
	float			m_spriteHeightShift{};
};

#endif //!__SPRITE_OBJECT_H__