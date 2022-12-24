#include "Renderer/renderer.h"

#include "gameObject.h"
#include "Renderer/renderBatch.h"
#include "Components/spriteRenderer.h"

void Renderer::add(GameObject* pGameObject)
{
	SpriteRenderer* pSpriteRenderer = static_cast<SpriteRenderer*>(pGameObject->getComponent(typeid(SpriteRenderer)));
	if (pSpriteRenderer)
	{
		add(pSpriteRenderer);
	}
}

void Renderer::render()
{
	for (size_t i = 0, size = m_batches.size(); i < size; ++i)
	{
		m_batches[i]->render();
	}
}

void Renderer::add(SpriteRenderer* pSpriteRenderer)
{
	bool bAdded{ false };

	for (size_t i = 0, size = m_batches.size(); i < size; ++i)
	{
		if (m_batches[i]->hasRoom())
		{
			Texture* pTexture = pSpriteRenderer->getTexture();
			if (!pTexture || (m_batches[i]->hasTexture(pTexture) || m_batches[i]->hasTextureRoom()))
			{
				m_batches[i]->addSprite(pSpriteRenderer);
				bAdded = true;
				break;
			}
		}
	}

	if (!bAdded)
	{
		RenderBatch* pRenderBatch = new RenderBatch(m_MAX_BATCH_SIZE);
		pRenderBatch->start();
		m_batches.push_back(pRenderBatch);
		pRenderBatch->addSprite(pSpriteRenderer);
	}
}