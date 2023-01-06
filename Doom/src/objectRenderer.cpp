#include <algorithm>

#include "objectRenderer.h"

#include "game.h"

ObjectRenderer::ObjectRenderer(Game *pGame)
	: m_pGame(pGame)
{
}

void ObjectRenderer::init()
{
    loadWallTextures();
    m_textureMap[SKY] = createTexture(m_pGame, R"(.\resources\textures\sky.png)", WIDTH, HALF_HEIGHT);
}

void ObjectRenderer::draw()
{
#ifndef SHOW_IN_BLUEPRINT
    drawBackground();
    renderGameObjects();
#endif
}

void ObjectRenderer::loadWallTextures()
{
    m_textureMap[WALL_1] = createTexture(m_pGame, R"(.\resources\textures\1.png)", TEXTURE_SIZE, TEXTURE_SIZE);
	m_textureMap[WALL_2] = createTexture(m_pGame, R"(.\resources\textures\2.png)", TEXTURE_SIZE, TEXTURE_SIZE);
	m_textureMap[WALL_3] = createTexture(m_pGame, R"(.\resources\textures\3.png)", TEXTURE_SIZE, TEXTURE_SIZE);
	m_textureMap[WALL_4] = createTexture(m_pGame, R"(.\resources\textures\4.png)", TEXTURE_SIZE, TEXTURE_SIZE);
	m_textureMap[WALL_5] = createTexture(m_pGame, R"(.\resources\textures\5.png)", TEXTURE_SIZE, TEXTURE_SIZE);
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
    std::vector<TextureObject>& vec = m_pGame->raycasting().getObjectsToRender();

    std::sort(vec.begin(), vec.end(), 
        [](const TextureObject &lhs, const TextureObject &rhs) 
        {
            return lhs.depth > rhs.depth;
        });

    for (TextureObject& obj : vec)
    {
        SDL_RenderCopy(m_pGame->renderer(), obj.pTexture->texture(), &obj.srcRect, &obj.dstRect);
    }
}

void ObjectRenderer::drawBackground()
{
    Texture* skyTexture = m_textureMap[SKY];

    // Sky
    m_skyTextureOffset = int(m_skyTextureOffset + 4.5f * m_pGame->player().relative()) % WIDTH;

    const SDL_Rect dstRect = { -m_skyTextureOffset, 0, WIDTH, HEIGHT / 2 };
    SDL_RenderCopy(m_pGame->renderer(), skyTexture->texture(), nullptr, &dstRect);

    if (m_skyTextureOffset > 0)
    {
        const SDL_Rect dstRect1 = { -m_skyTextureOffset + WIDTH, 0, WIDTH, HEIGHT / 2 };
        SDL_RenderCopy(m_pGame->renderer(), skyTexture->texture(), nullptr, &dstRect1);
    }
    else
    {
        const SDL_Rect dstRect1 = { -(m_skyTextureOffset + WIDTH), 0, WIDTH, HEIGHT / 2 };
        SDL_RenderCopy(m_pGame->renderer(), skyTexture->texture(), nullptr, &dstRect1);
    }

    // Floor
    const SDL_Rect rect = { 0, HALF_HEIGHT, WIDTH, HEIGHT };

    SDL_SetRenderDrawColor(m_pGame->renderer(), FLOOR_COLOR.r, FLOOR_COLOR.g, FLOOR_COLOR.b, FLOOR_COLOR.a);
    SDL_RenderFillRect(m_pGame->renderer(), &rect);
}

Texture* ObjectRenderer::createTexture(Game* pGame, const std::string& path, int w, int h)
{
    Texture* texture = new Texture(pGame);

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