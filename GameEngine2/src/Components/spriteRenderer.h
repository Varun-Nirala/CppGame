#pragma once

#include "components.h"
#include "Renderer/texture.h"

#include "Components/sprite.h"

class SpriteRenderer : public Components
{
public:
	~SpriteRenderer()
	{
		delete m_pSprite;
		m_pSprite = nullptr;
	}

	explicit SpriteRenderer(glm::vec4 color = {0.0f, 0.0f, 0.0f, 1.0f});
	explicit SpriteRenderer(Sprite *pSprite);

	void start() override {}
	void update(GLfloat dt) override { (void)dt; }

	const glm::vec4& getColor() const { return m_color; }
	glm::vec4& getColor() { return m_color; }

	const Texture* getTexture() const { return m_pSprite->getTexture(); }
	Texture* getTexture() { return m_pSprite->getTexture(); }

	const std::vector<glm::vec2>& getTexCoords() const { return m_pSprite->getTexCoords(); }
	std::vector<glm::vec2>& getTexCoords() { return m_pSprite->getTexCoords(); }

private:
	glm::vec4				m_color{ 1.0f, 1.0f, 1.0f, 1.0f };
	Sprite					*m_pSprite{};
};

inline SpriteRenderer::SpriteRenderer(glm::vec4 color)
	: m_color(color)
{}

inline SpriteRenderer::SpriteRenderer(Sprite* pSprite)
	: m_pSprite(pSprite)
{}