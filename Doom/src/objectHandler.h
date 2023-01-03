#ifndef __OBJECT_HANDLER_H__
#define __OBJECT_HANDLER_H__

#include <vector>

class SpriteObject;
class AnimatedSpriteObject;
class Game;

class ObjectHandler
{
public:
	explicit ObjectHandler(Game* pGame);

	void init();

	void addSprite(SpriteObject* pSpriteObject) { m_sprites.push_back(pSpriteObject); }

	void update(float dt);

	void draw();

private:
	Game									*m_pGame{};
	std::vector<SpriteObject*>				m_sprites;
};

#endif //!__OBJECT_HANDLER_H__