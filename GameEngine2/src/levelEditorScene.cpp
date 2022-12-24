#include "levelEditorScene.h"

#include "Components/spriteRenderer.h"
#include "Components/spriteSheet.h"
#include "gameObject.h"

void LevelEditorScene::init()
{
	m_pSpriteSheet = new Spritesheet(new Texture(R"(.\resources\Images\spritesheet.png)"), 16, 16, 26, 0);

	GameObject* g1 = new GameObject("Object_1", Transform(glm::vec2{ 0, 0 }, glm::vec2(256, 256)));
	g1->addComponent(new SpriteRenderer(new Sprite(new Texture(R"(.\resources\Images\testImage.png)"))));

	addGameObjectToScene(g1);

	GameObject* g2 = new GameObject("Object_2", Transform(glm::vec2{ 400, 0 }, glm::vec2(256, 256)));
	g2->addComponent(new SpriteRenderer(new Sprite(new Texture(R"(.\resources\Images\testImage2.png)"))));

	addGameObjectToScene(g2);

	GameObject* g3 = new GameObject("Object_3", Transform(glm::vec2{ 400, 0 }, glm::vec2(256, 256)));
	g3->addComponent(new SpriteRenderer(m_pSpriteSheet->getSrite(0)));

	addGameObjectToScene(g3);

	GameObject* g4 = new GameObject("Object_4", Transform(glm::vec2{ 400, 400 }, glm::vec2(256, 256)));
	g4->addComponent(new SpriteRenderer(m_pSpriteSheet->getSrite(10)));

	addGameObjectToScene(g4);

	/*GLint xOffset{10};
	GLint yOffset{ 10 };

	GLfloat totalWidth = (GLfloat)(600 - xOffset * 2);
	GLfloat totalHeight = (GLfloat)(300 - yOffset * 2);


	GLfloat sizeX = totalWidth / 100.0f;
	GLfloat sizeY = totalHeight / 100.0f;

	for (GLint x = 0; x < 100; ++x)
	{
		for (GLint y = 0; y < 100; ++y)
		{
			GLfloat xPos = xOffset + (x * sizeX);
			GLfloat yPos = yOffset + (y * sizeY);

			GameObject* g = new GameObject("Obj-" + std::to_string(x) + std::to_string(y), Transform(glm::vec2{xPos, yPos}, glm::vec2{sizeX, sizeY}));
			g->addComponent(new SpriteRenderer(glm::vec4{xPos / totalWidth, yPos / totalHeight, 1.0f, 1.0f}));

			addGameObjectToScene(g);
		}
	}*/
}

void LevelEditorScene::update(GLfloat dt)
{
	ns_Util::Logger::LOG_MSG("FPS : ", 1.0f / dt, '\n');

	for (size_t i = 0, size = m_gameObjects.size(); i < size; ++i)
	{
		m_gameObjects[i]->update(dt);
	}

	m_renderer.render();
}