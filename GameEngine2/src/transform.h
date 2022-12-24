#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Transform
{
public:
	Transform() = default;

	explicit Transform(glm::vec2 pos)
		: m_position(pos)
	{
	}

	Transform(glm::vec2 pos, glm::vec2 scale)
		: m_position(pos)
		, m_scale(scale)
	{
	}

	void init(const glm::vec2& pos, const glm::vec2& scale)
	{
		m_position = pos;
		m_scale = scale;
	}

	const glm::vec2& getPosition() const
	{
		return m_position;
	}

	glm::vec2& getPosition()
	{
		return m_position;
	}

	const glm::vec2& getScale() const
	{
		return m_scale;
	}

	glm::vec2& getScale()
	{
		return m_scale;
	}


private:
	glm::vec2		m_position{};
	glm::vec2		m_scale{};
};