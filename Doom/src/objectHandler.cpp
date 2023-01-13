#include "objectHandler.h"
#include "game.h"
#include "spriteObject.h"
#include "animatedSpriteObject.h"
#include "npc.h"

ObjectHandler::ObjectHandler(Game* pGame)
	: m_pGame(pGame)
{
}

void ObjectHandler::init()
{
	clear();
	const std::string staticSpritePath = R"(.\resources\sprites\static_sprites\)";
	const std::string animatedSpritePath = R"(.\resources\sprites\animated_sprites\)";
	const std::string npcSpritePath = R"(.\resources\sprites\npc\)";

	//candlebra.png
	SpriteObject* spriteObject = SpriteObject::createSpriteObject(m_pGame);
	spriteObject->init(staticSpritePath + "candlebra.png", { 10.5f, 3.5f }, 0.7f, 0.27f);
	addSprite(spriteObject);

	//green_light
	AnimatedSpriteObject* animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 11.5f, 3.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 1.5f, 1.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 1.5f, 7.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 5.5f, 3.25f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 5.5f, 4.75f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 7.5f, 2.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 7.5f, 5.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 14.5f, 1.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 14.5f, 4.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 14.5f, 24.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 14.5f, 30.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 1.5f, 30.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 1.5f, 24.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	//red_light
	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 14.5f, 5.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 14.5f, 7.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 12.5f, 7.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);
	
	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 9.5f, 7.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 14.5f, 12.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 9.5f, 20.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 10.5f, 20.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 10.5f, 20.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 3.5f, 14.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = AnimatedSpriteObject::createAnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 3.5f, 18.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	for (int y = 0; y < 10; ++y)
	{
		for (int x = 0; x < 10; ++x)
		{
			m_restrictedArea.push_back({ x, y });
		}
	}

	spawnNPC();
}

void ObjectHandler::reset()
{
	init();
}

void ObjectHandler::update(float dt)
{
	m_npcPositions.clear();
	for (NPC* pNPC : m_npcs)
	{
		if (pNPC->alive())
		{
			m_npcPositions.insert(pNPC->mapPosition());
		}
	}

	for (SpriteObject* pSprite : m_sprites)
	{
		pSprite->update(dt);
	}

	for (NPC* pNPC : m_npcs)
	{
		pNPC->update(dt);
	}

	checkWin();
}

void ObjectHandler::draw()
{
#ifndef SHOW_IN_BLUEPRINT
	for (SpriteObject* pSprite : m_sprites)
	{
		pSprite->draw();
	}
#endif
	for (NPC* pNPC : m_npcs)
	{
		pNPC->draw();
	}
}

void ObjectHandler::checkWin()
{
	if (m_npcPositions.empty())
	{
		m_pGame->setGameWon();
	}
}

bool ObjectHandler::isNotInNPCpos(const glm::ivec2& pos) const
{
	for (const glm::ivec2& p : m_npcPositions)
	{
		if (p == pos)
		{
			return false;
		}
	}
	return true;
}

void ObjectHandler::spawnNPC()
{
	for (int i = 0; i < m_npcCount; ++i)
	{
		const NPC_TYPE npcType = getRandomNPCType();
		NPC* pNPC{};

		switch (npcType)
		{
			case SOLDIER:
				pNPC = SoldierNPC::createSoldierNPC(m_pGame);
				dynamic_cast<SoldierNPC*>(pNPC)->init();
				break;

			case COCODEMON:
				pNPC = CacoDemonNPC::createCacoDemonNPC(m_pGame);
				dynamic_cast<CacoDemonNPC*>(pNPC)->init();
				break;

			case CYBERDEMON:
				pNPC = CyberDemonNPC::createCyberDemonNPC(m_pGame);
				dynamic_cast<CyberDemonNPC*>(pNPC)->init();
				break;

			default:
				pNPC = SoldierNPC::createSoldierNPC(m_pGame);
				dynamic_cast<SoldierNPC*>(pNPC)->init();
				break;
		}
		pNPC->setPosition(getRandomPosition());
		addNPC(pNPC);
	}
}

NPC_TYPE ObjectHandler::getRandomNPCType() const
{
	static const std::vector<int> weights{ 70, 20, 10 };
	
	const int randomNum = getRandomNumber(0, 100);

	NPC_TYPE npcType{ SOLDIER };

	for (int k = 0; k < weights.size(); ++k)
	{
		if (randomNum >= weights[k])
		{
			npcType = (NPC_TYPE)k;
			break;
		}
	}
	return npcType;
}

glm::vec2 ObjectHandler::getRandomPosition() const
{
	glm::vec2 pos;

	do
	{
		pos.x = (float)getRandomNumber(0, (int)m_pGame->map().cols());
		pos.y = (float)getRandomNumber(0, (int)m_pGame->map().rows());
	} while (!m_pGame->map().isEmpty(pos) || isInRestrictedArea(pos));

	pos.x += 0.5f;
	pos.y += 0.5f;

	return pos;
}

bool ObjectHandler::isInRestrictedArea(const glm::vec2 &pos) const
{
	return std::find(m_restrictedArea.begin(), m_restrictedArea.end(), pos) != m_restrictedArea.end();
}

void ObjectHandler::clear()
{
	std::for_each(m_sprites.begin(), m_sprites.end(), [](SpriteObject* pObj) { delete pObj; });

	std::for_each(m_npcs.begin(), m_npcs.end(), [](NPC* pObj) { delete pObj; });

	m_sprites.clear();
	m_npcs.clear();
}