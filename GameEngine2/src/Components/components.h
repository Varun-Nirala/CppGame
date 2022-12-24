#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include "gameObject.h"

class Components
{
public:
	virtual ~Components()
	{
		delete m_pGameObject;
		m_pGameObject = nullptr;
	}

	void setGameObject(GameObject* gameObject);
	const GameObject* getGameObject() const;
	GameObject* getGameObject();

	virtual void start() = 0;
	virtual void update(GLfloat dt) = 0;

protected:
	GameObject			*m_pGameObject{};
};

inline void Components::setGameObject(GameObject* gameObject)
{
	m_pGameObject = gameObject;
}

inline const GameObject* Components::getGameObject() const
{
	return m_pGameObject;
}

inline GameObject* Components::getGameObject()
{
	return m_pGameObject;
}