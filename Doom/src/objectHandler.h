#ifndef __OBJECT_HANDLER_H__
#define __OBJECT_HANDLER_H__

#include <vector>
#include <unordered_set>

#include <glm/glm.hpp>

#include "common/common.h"

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

	void reset();

	void addSprite(SpriteObject* pSpriteObject) { m_sprites.push_back(pSpriteObject); }
	void addNPC(NPC* pNPC) { m_npcs.push_back(pNPC); }

	void update(float dt);

	void draw();

	bool isNotInNPCpos(const glm::ivec2& pos) const;
private:
	void clear();

private:
	Game										*m_pGame{};
	std::vector<SpriteObject*>					m_sprites;
	std::vector<NPC*>							m_npcs;

	std::unordered_set<glm::ivec2, HashFunc>	m_npcPositions;
};

#endif //!__OBJECT_HANDLER_H__