#ifndef __OBJECT_HANDLER_H__
#define __OBJECT_HANDLER_H__

#include <vector>

class Game;
class SpriteObject;
class AnimatedSpriteObject;
class NPC;

class ObjectHandler
{
public:
	~ObjectHandler() { clear(); }
	explicit ObjectHandler(Game* pGame);

	void init();

	void addSprite(SpriteObject* pSpriteObject) { m_sprites.push_back(pSpriteObject); }
	void addNPC(NPC* pNPC) { m_npcs.push_back(pNPC); }

	void update(float dt);

	void draw();
private:
	void clear();

private:
	Game									*m_pGame{};
	std::vector<SpriteObject*>				m_sprites;
	std::vector<NPC*>						m_npcs;
};

#endif //!__OBJECT_HANDLER_H__