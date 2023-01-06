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
	const std::string staticSpritePath = R"(.\resources\sprites\static_sprites\)";
	const std::string animatedSpritePath = R"(.\resources\sprites\animated_sprites\)";
	const std::string npcSpritePath = R"(.\resources\sprites\npc\)";

	//candlebra.png
	SpriteObject* spriteObject = new SpriteObject(m_pGame);
	spriteObject->init(staticSpritePath + "candlebra.png", { 10.5f, 3.5f }, 0.7f, 0.27f);
	addSprite(spriteObject);

	//green_light
	AnimatedSpriteObject* animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 11.5f, 3.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 1.5f, 1.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 1.5f, 7.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 5.5f, 3.25f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 5.5f, 4.75f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 7.5f, 2.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 7.5f, 5.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "green_light", { 14.5f, 1.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	//red_light
	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 14.5f, 7.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 12.5f, 7.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);
	
	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 9.5f, 7.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	//npc
	NPC* npcObject = new NPC(m_pGame);
	npcObject->init(npcSpritePath);
	addNPC(npcObject);
}

void ObjectHandler::update(float dt)
{
	for (SpriteObject* pSprite : m_sprites)
	{
		pSprite->update(dt);
	}

	for (NPC* pNPC : m_npcs)
	{
		pNPC->update(dt);
	}
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