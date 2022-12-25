#include "objectRenderer.h"

#include "game.h"

ObjectRenderer::ObjectRenderer(Game *pGame)
	: m_pGame(pGame)
{
}

void ObjectRenderer::init()
{
    loadWallTextures(TEXTURE_SIZE, TEXTURE_SIZE);
}

void ObjectRenderer::draw()
{
    renderGameObjects();
}

void ObjectRenderer::loadWallTextures()
{
	m_textureMap['1'] = createTexture(m_pGame, R"(.\resources\textures\1.png)");
	m_textureMap['2'] = createTexture(m_pGame, R"(.\resources\textures\2.png)");
	m_textureMap['3'] = createTexture(m_pGame, R"(.\resources\textures\3.png)");
	m_textureMap['4'] = createTexture(m_pGame, R"(.\resources\textures\4.png)");
	m_textureMap['5'] = createTexture(m_pGame, R"(.\resources\textures\5.png)");
}

void ObjectRenderer::loadWallTextures(int w, int h)
{
    m_textureMap['1'] = createTexture(m_pGame, R"(.\resources\textures\1.png)", w, h);
    m_textureMap['2'] = createTexture(m_pGame, R"(.\resources\textures\2.png)", w, h);
    m_textureMap['3'] = createTexture(m_pGame, R"(.\resources\textures\3.png)", w, h);
    m_textureMap['4'] = createTexture(m_pGame, R"(.\resources\textures\4.png)", w, h);
    m_textureMap['5'] = createTexture(m_pGame, R"(.\resources\textures\5.png)", w, h);
}

const Texture* ObjectRenderer::getTexture(char textureKey) const
{
    if (!m_textureMap.count(textureKey))
    {
        ns_Util::Logger::LOG_ERROR("Texture not found. Key : ", textureKey, '\n');
        assert(false);
        return nullptr;
    }
    return m_textureMap.at(textureKey);
}

Texture* ObjectRenderer::getTexture(char textureKey)
{
    if (!m_textureMap.count(textureKey))
    {
        ns_Util::Logger::LOG_ERROR("Texture not found. Key : ", textureKey, '\n');
        assert(false);
        return nullptr;
    }
    return m_textureMap[textureKey];
}

void ObjectRenderer::renderGameObjects()
{
    for (TextureObject& obj : m_pGame->raycasting().getObjectsToRender())
    {
        const SDL_Rect dstRect = { (int)obj.position.x, (int)obj.position.y, obj.texture.width(), obj.texture.height() };
        SDL_RenderCopy(m_pGame->renderer(), obj.texture.getTexture(), nullptr, &dstRect);
    }
}

Texture* ObjectRenderer::createTexture(Game* pGame, const std::string& path, int w, int h)
{
    Texture *texture = new Texture(pGame);

    if (!texture->loadTexture(path.c_str(), w, h))
    {
        ns_Util::Logger::LOG_ERROR("Unable to create texture from ", path, "! SDL_image Error : ", IMG_GetError(), '\n');
        assert(false);
    }

    return texture;
}

Texture* ObjectRenderer::createTexture(Game* pGame, const std::string& path)
{
    Texture* texture = new Texture(pGame);

    if (!texture->loadTexture(path.c_str()))
    {
        ns_Util::Logger::LOG_ERROR("Unable to create texture from ", path, "! SDL_image Error : ", IMG_GetError(), '\n');
        assert(false);
    }

    return texture;
}

void ObjectRenderer::clear()
{
    for (auto &p : m_textureMap)
    {
        delete p.second;
    }

    m_textureMap.clear();
}