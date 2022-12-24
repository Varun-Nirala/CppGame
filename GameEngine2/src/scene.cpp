#include "scene.h"
#include "gameObject.h"

void Scene::start()
{
	for (size_t i = 0, size = m_gameObjects.size(); i < size; ++i)
	{
		m_gameObjects[i]->start();
		m_renderer.add(m_gameObjects[i]);
	}
	m_bIsRunning = true;
}

void Scene::addGameObjectToScene(GameObject* pGameObject)
{
	if (!m_bIsRunning)
	{
		m_gameObjects.push_back(pGameObject);
	}
	else
	{
		m_gameObjects.push_back(pGameObject);
		pGameObject->start();
		m_renderer.add(pGameObject);
	}
}