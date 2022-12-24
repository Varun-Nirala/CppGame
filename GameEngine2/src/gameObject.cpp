#include "gameObject.h"
#include "Components/components.h"

GameObject::GameObject(const std::string& name)
	: m_name(name)
{
}

GameObject::GameObject(const std::string& name, const Transform &transform)
	: m_name(name)
	, m_transform(transform)
{
}

void GameObject::addComponent(Components* comp)
{
	m_components.push_back(comp);
	comp->setGameObject(this);
}

const Components* GameObject::getComponent(const type_info& typeInfo) const
{
	// TODO
	for (size_t i = 0, size = m_components.size(); i < size; ++i)
	{
		if (typeid(*m_components[i]) == typeInfo)
		{
			return m_components[i];
		}
	}
	return nullptr;
}

Components* GameObject::getComponent(const type_info& typeInfo)
{
	// TODO
	for (size_t i = 0, size = m_components.size(); i < size; ++i)
	{	
		if (typeid(*m_components[i]) == typeInfo)
		{
			return m_components[i];
		}
	}
	return nullptr;
}

void GameObject::removeComponent(Components* comp)
{
	(void)std::remove(m_components.begin(), m_components.end(), comp);
}

const Transform& GameObject::getTransform() const
{
	return m_transform;

}

Transform& GameObject::getTransform()
{
	return m_transform;
}

void GameObject::start()
{
	for (size_t i = 0, size = m_components.size(); i < size; ++i)
	{
		m_components[i]->start();
	}
}

void GameObject::update(GLfloat dt)
{
	for (size_t i = 0, size = m_components.size(); i < size; ++i)
	{
		m_components[i]->update(dt);
	}
}