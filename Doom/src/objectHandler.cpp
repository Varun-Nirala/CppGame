#include "objectHandler.h"
#include "game.h"
#include "spriteObject.h"
#include "animatedSpriteObject.h"


ObjectHandler::ObjectHandler(Game* pGame)
	: m_pGame(pGame)
{
}

void ObjectHandler::init()
{
	const std::string staticSpritePath = R"(.\resources\sprites\static_sprites\)";
	const std::string animatedSpritePath = R"(.\resources\sprites\animated_sprites\)";

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

	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 14.5f, 7.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);

	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 12.5f, 7.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);
	
	animatedSpriteObject = new AnimatedSpriteObject(m_pGame);
	animatedSpriteObject->init(animatedSpritePath + "red_light", { 9.5f, 7.5f }, 0.8f, 0.16f, 120);
	addSprite(animatedSpriteObject);
}

void ObjectHandler::update(float dt)
{
	for (SpriteObject* pSprite : m_sprites)
	{
		pSprite->update(dt);
	}
}