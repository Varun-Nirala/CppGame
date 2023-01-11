#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>
#include <SDL.h>
#include <SDL_image.h>

#include <unordered_map>

class Game;

class Texture
{
public:
	static Texture* createTexture(Game *pGame)
	{
		return new Texture(pGame);
	}

	~Texture() { clear(); };
	explicit Texture(Game* pGame);

	int width() const { return m_width; }
	int height() const { return m_height; }

	const SDL_Texture* texture() const { return m_pTexture; }
	SDL_Texture* texture() { return m_pTexture; }

	bool loadTexture(const std::string& path);
	bool loadTexture(const std::string& path, int w, int h);

private:
	SDL_Texture* copyTexture(SDL_Texture* pTexture, int w, int h) const;
	bool scaleTexture(int w, int h);

	void clear();

private:
	Game			*m_pGame{};

	int				m_width{};
	int				m_height{};

	SDL_Texture		*m_pTexture{};
};

#endif //!__TEXTURE_H__