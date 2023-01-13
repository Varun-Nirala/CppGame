#ifndef __OBJECT_RENDERER_H__
#define __OBJECT_RENDERER_H__

#include <unordered_map>
#include <string>

#include "common/constants.h"
#include "texture.h"

class Game;

class ObjectRenderer
{
public:
	~ObjectRenderer() { clear(); }
	explicit ObjectRenderer(Game* pGame);

	void init();
	void draw();

	void reset();

	void loadWallTextures();

	const Texture* getTexture(char textureKey) const;
	Texture* getTexture(char textureKey);

	void drawGameOver();
	void drawVictory();

	void setPlayPlayerDamage() { m_bPlayPlayerDamage = true; }

	static Texture* createTexture(Game* pGame, const std::string& path, SDL_BlendMode blendMode);
	static Texture* createTexture(Game* pGame, const std::string& path, int w, int h, SDL_BlendMode blendMode);

private:
	void renderGameObjects();
	void drawPlayerHealthAndKillCount();
	void drawBackground();
	void playPlayerDamage();
	void clear();
private:
	Game									*m_pGame{};
	std::unordered_map<char, Texture *>		m_textureMap;
	int										m_skyTextureOffset{};
	bool									m_bPlayPlayerDamage{ false };

	int										m_digitSize{ 90 };
	std::unordered_map<char, Texture*>		m_digitTextureMap;

};
#endif //!__OBJECT_RENDERER_H__