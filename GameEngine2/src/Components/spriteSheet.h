#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "Renderer/texture.h"
#include "Components/sprite.h"

class Spritesheet
{
public:
	Spritesheet(Texture* pTexture, GLint spriteWidth, GLint spriteHeight, GLint numSprites, GLint spacing)
		: m_pTexture(pTexture)
	{
		m_sprites.resize(numSprites);

		GLint currentX{};
		GLint currentY = m_pTexture->getHeight() - spriteHeight;

		for (GLint i = 0; i < numSprites; ++i)
		{
			GLfloat topY = (currentY + spriteHeight) / (GLfloat)m_pTexture->getHeight();
			GLfloat rightX = (currentX + spriteWidth) / (GLfloat)m_pTexture->getWidth();
			GLfloat leftX = currentX / (GLfloat)m_pTexture->getWidth();
			GLfloat bottomY = currentY / (GLfloat)m_pTexture->getHeight();

			std::vector<glm::vec2> texCoords = {
				glm::vec2{rightX, topY},
				glm::vec2{rightX, bottomY},
				glm::vec2{leftX, bottomY},
				glm::vec2{leftX, topY}
			};

			Sprite* pSprite = new Sprite(m_pTexture, texCoords);
			m_sprites[i] = pSprite;

			currentX += spriteWidth + spacing;

			if (currentX >= m_pTexture->getWidth())
			{
				currentX = 0;
				currentY -= spriteHeight + spacing;
			}
		}
	}

	const Sprite* getSrite(GLint index) const { return m_sprites[index]; }
	Sprite* getSrite(GLint index) { return m_sprites[index]; }

private:
	Texture					*m_pTexture{};
	std::vector<Sprite*>	m_sprites;
};