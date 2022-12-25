#include "texture.h"

#include "game.h"

#include "common/logger.h"

Texture::Texture(Game* pGame)
	: m_pGame(pGame)
{
}

Texture::Texture(const Texture& obj)
{
	m_width = obj.m_width;
	m_height = obj.m_height;
	m_pGame = obj.m_pGame;

	m_pTexture = obj.m_pTexture ? copyTexture(obj.m_pTexture, m_width, m_height) : nullptr;
}

Texture::Texture(Texture&& obj) noexcept
{
	m_width = obj.m_width;
	m_height = obj.m_height;
	m_pGame = obj.m_pGame;
	m_pTexture = obj.m_pTexture;

	obj.m_pGame = nullptr;
	obj.m_pTexture = nullptr;
}

Texture& Texture::operator=(const Texture& obj)
{
	if (this != &obj)
	{
		clear();

		m_width = obj.m_width;
		m_height = obj.m_height;
		m_pGame = obj.m_pGame;

		m_pTexture = obj.m_pTexture ? copyTexture(obj.m_pTexture, m_width, m_height) : nullptr;
	}
	return *this;
}

Texture& Texture::operator=(Texture&& obj) noexcept
{
	if (this != &obj)
	{
		clear();

		m_width = obj.m_width;
		m_height = obj.m_height;
		m_pGame = obj.m_pGame;
		m_pTexture = obj.m_pTexture;

		obj.m_pGame = nullptr;
		obj.m_pTexture = nullptr;
	}
	return *this;
}

bool Texture::loadTexture(const std::string& path)
{
	clear();

	m_pTexture = IMG_LoadTexture(m_pGame->renderer(), path.c_str());

	if (!m_pTexture)
	{
		clear();
		ns_Util::Logger::LOG_ERROR("Unable to create texture from surface. ", path, "! SDL Error : ", SDL_GetError(), '\n');
		assert(false);
		return false;
	}

	if (SDL_QueryTexture(m_pTexture, nullptr, nullptr, &m_width, &m_height) < 0)
	{
		clear();
		ns_Util::Logger::LOG_ERROR("Unable to query texture created from ", path, "! SDL Error : ", SDL_GetError(), '\n');
		assert(false);
		return false;
	}

	return true;
}

bool Texture::loadTexture(const std::string& path, int w, int h)
{
	if (!loadTexture(path))
	{
		clear();
		ns_Util::Logger::LOG_ERROR("Unable to create texture from surface. ", path, "! SDL Error : ", SDL_GetError(), '\n');
		assert(false);
		return false;
	}

	if (m_width != w || m_height != h)
	{
		if (!scaleTexture(w, h))
		{
			clear();
			ns_Util::Logger::LOG_ERROR("Unable to scale texture to the requested size. ", path, "! SDL Error : ", SDL_GetError(), '\n');
			assert(false);
			return false;
		}
	}
	return true;
}

Texture Texture::subTexture(int posX, int posY, int w, int h) const
{
	Texture newTexture(m_pGame);

	newTexture.m_width = w;
	newTexture.m_height = h;

	newTexture.m_pTexture = SDL_CreateTexture(m_pGame->renderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, w, h);

	SDL_Rect srcRect = { posX, posY, w, h };

	// draw to texture
	if (SDL_SetRenderTarget(m_pGame->renderer(), newTexture.m_pTexture) < 0)
	{
		ns_Util::Logger::LOG_ERROR("Unable to set render target! SDL Error : ", SDL_GetError(), '\n');
		SDL_DestroyTexture(newTexture.m_pTexture);
		newTexture.m_pTexture = nullptr;
		assert(false);
		return newTexture;
	}

	if (SDL_RenderCopy(m_pGame->renderer(), m_pTexture, &srcRect, nullptr) < 0)
	{
		ns_Util::Logger::LOG_ERROR("Unable to copy texture! SDL Error : ", SDL_GetError(), '\n');
		SDL_DestroyTexture(newTexture.m_pTexture);
		newTexture.m_pTexture = nullptr;
		assert(false);
		return newTexture;
	}

	// draw to screen
	if (SDL_SetRenderTarget(m_pGame->renderer(), nullptr) < 0)
	{
		ns_Util::Logger::LOG_ERROR("Unable to set render target! SDL Error : ", SDL_GetError(), '\n');
		SDL_DestroyTexture(newTexture.m_pTexture);
		newTexture.m_pTexture = nullptr;
		assert(false);
		return newTexture;
	}

	return newTexture;
}

void Texture::scale(int w, int h)
{
	if (!scaleTexture(w, h))
	{
		clear();
		ns_Util::Logger::LOG_ERROR("Unable to scale texture to the requested size! SDL Error : ", SDL_GetError(), '\n');
		assert(false);
		return;
	}
}

void Texture::clear()
{
	if (m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = nullptr;
	}
	m_width = m_height = 0;
}

SDL_Texture* Texture::copyTexture(SDL_Texture* pTexture, int w, int h) const
{
	SDL_Texture* newTexture = SDL_CreateTexture(m_pGame->renderer(), SDL_PIXELFORMAT_RGB888, SDL_TEXTUREACCESS_TARGET, w, h);

	// draw to texture
	if (SDL_SetRenderTarget(m_pGame->renderer(), newTexture) < 0)
	{
		ns_Util::Logger::LOG_ERROR("Unable to set render target! SDL Error : ", SDL_GetError(), '\n');
		SDL_DestroyTexture(newTexture);
		assert(false);
		return nullptr;
	}

	if (SDL_RenderCopy(m_pGame->renderer(), pTexture, nullptr, nullptr) < 0)
	{
		ns_Util::Logger::LOG_ERROR("Unable to copy texture! SDL Error : ", SDL_GetError(), '\n');
		SDL_DestroyTexture(newTexture);
		assert(false);
		return nullptr;
	}

	// draw to screen
	if (SDL_SetRenderTarget(m_pGame->renderer(), nullptr) < 0)
	{
		ns_Util::Logger::LOG_ERROR("Unable to set render target! SDL Error : ", SDL_GetError(), '\n');
		SDL_DestroyTexture(newTexture);
		assert(false);
		return nullptr;
	}

	return newTexture;
}

bool Texture::scaleTexture(int w, int h)
{
	SDL_Texture* pScaledTexture = copyTexture(m_pTexture, w, h);

	clear();

	m_pTexture = pScaledTexture;
	m_width = w;
	m_height = h;

	return true;
}