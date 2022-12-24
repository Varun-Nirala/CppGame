#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <string>
#include <typeinfo>

#include "transform.h"

class Components;

class GameObject
{
public:
	explicit GameObject(const std::string& name);

	GameObject(const std::string& name, const Transform &transform);

	void addComponent(Components* comp);
	const Components* getComponent(const type_info &typeInfo) const;
	Components* getComponent(const type_info& typeInfo);
	void removeComponent(Components* comp);

	const Transform& getTransform() const;
	Transform& getTransform();

	void start();

	void update(GLfloat dt);

private:
	std::string						m_name;
	std::vector<Components*>		m_components;
	Transform						m_transform;
};