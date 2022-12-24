#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>

#include "Renderer/texture.h"

class Sprite
{
public:
	~Sprite()
	{
		delete m_pTexture;
		m_pTexture = nullptr;
	}

	Sprite(Texture* pTexture)
		: m_pTexture(pTexture)
	{
		m_texCoords = { 
			glm::vec2{1, 1},
			glm::vec2{1, 0},
			glm::vec2{0, 0},
			glm::vec2{0, 1}
		};
	}

	Sprite(Texture *pTexture, const std::vector<glm::vec2> &texCoords)
		: m_pTexture(pTexture)
		, m_texCoords(texCoords)
	{}

	const Texture* getTexture() const { return m_pTexture; }
	Texture* getTexture() { return m_pTexture; }

	const std::vector<glm::vec2>& getTexCoords() const { return m_texCoords; }
	std::vector<glm::vec2>& getTexCoords() { return m_texCoords; }

private:
	Texture					*m_pTexture{};
	std::vector<glm::vec2>	m_texCoords;
};