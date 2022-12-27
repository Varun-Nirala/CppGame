#include "objectRenderer.h"

#include "game.h"

ObjectRenderer::ObjectRenderer(Game *pGame)
	: m_pGame(pGame)
{
}

void ObjectRenderer::init()
{
    loadWallTextures();
    m_textureMap[SKY] = createTexture(m_pGame, R"(.\resources\textures\sky.png)", TEXTURE_SIZE, TEXTURE_SIZE);
}

void ObjectRenderer::draw()
{
    drawBackground();
    renderGameObjects();
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
    for (TextureObject& obj : m_pGame->raycasting().getObjectsToRender())
    {
        SDL_RenderCopy(m_pGame->renderer(), m_textureMap[obj.textureKey]->texture(), &obj.srcRect, &obj.dstRect);
    }
}

void ObjectRenderer::drawBackground()
{
    Texture* skyTexture = m_textureMap[SKY];
    // Sky
    m_skyTextureOffset = int(m_skyTextureOffset + 4.5f * m_pGame->player().relative()) % WIDTH;

    SDL_Rect dstRect = { -m_skyTextureOffset, 0, WIDTH, HEIGHT };
    SDL_RenderCopy(m_pGame->renderer(), skyTexture->texture(), nullptr, &dstRect);

    dstRect = { -m_skyTextureOffset + WIDTH, 0, WIDTH, HEIGHT };
    SDL_RenderCopy(m_pGame->renderer(), skyTexture->texture(), nullptr, &dstRect);

    // Floor
    SDL_Rect rect;
    rect.x = 0;
    rect.y = HALF_HEIGHT;
    rect.w = WIDTH;
    rect.h = HEIGHT;

    SDL_SetRenderDrawColor(m_pGame->renderer(), FLOOR_COLOR.r, FLOOR_COLOR.g, FLOOR_COLOR.b, FLOOR_COLOR.a);

    bool bFilledRectange = true;
    if (bFilledRectange)
    {
        SDL_RenderFillRect(m_pGame->renderer(), &rect);
    }
    else
    {
        SDL_RenderDrawRect(m_pGame->renderer(), &rect);
    }
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

void ObjectRenderer::clear()
{
    for (auto &p : m_textureMap)
    {
        delete p.second;
    }

    m_textureMap.clear();
}