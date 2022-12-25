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

	void loadWallTextures();
	void loadWallTextures(int w, int h);

	const Texture* getTexture(char textureKey) const;
	Texture* getTexture(char textureKey);

	static Texture* createTexture(Game *pGame, const std::string& path, int w, int h);
	static Texture* createTexture(Game* pGame, const std::string& path);

private:
	void renderGameObjects();
	void clear();
private:
	Game									*m_pGame{};
	std::unordered_map<char, Texture *>		m_textureMap;
};

#endif //!__OBJECT_RENDERER_H__