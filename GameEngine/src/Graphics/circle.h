#pragma once

#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "points.h"
#include "lines.h"

class Circle : public Drawable
{
public:
	Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec2 centre);
	Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec3 centre);
	Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, GLfloat x, GLfloat y, GLfloat z = 0.0f);

	void setDrawFilled(bool val) { m_bFilled = val; }

	void init() override;
	void update(float elapsedTimeInMs) override;
	void render() override;
	void release() override;

	void setUniformModel() override;

protected:
	void draw() override;

private:
	glm::vec3		m_centre;
	GLfloat			m_radius{};
	Lines			m_lines;
	bool			m_bFilled{ false };
};

Circle::Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec2 centre)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(centre, 0.0f)
	, m_lines(shaderID, bOwnIt)
{}

Circle::Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec3 centre)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(centre)
	, m_lines(shaderID, bOwnIt)
{}

Circle::Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, GLfloat x, GLfloat y, GLfloat z)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(x, y, z)
	, m_lines(shaderID, bOwnIt)
{}

inline void Circle::init()
{
	// Create and assign points
	// r2 = x2 + y2
	// x = rcos0
	// y = rsin0
	glm::vec3 p1 = m_centre;
	p1.x += m_radius;

	glm::vec3 p2 = p1;
	GLfloat offset = 5.0f;
	for (GLfloat i = 0; i < 360.0f; i += offset)
	{
		p1.x = m_centre.x + m_radius * (GLfloat)std::cos(glm::radians(i));
		p1.y = m_centre.y + m_radius * (GLfloat)std::sin(glm::radians(i));

		p2.x = m_centre.x + m_radius * (GLfloat)std::cos(glm::radians(i + offset));
		p2.y = m_centre.y + m_radius * (GLfloat)std::sin(glm::radians(i + offset));
		m_lines.addine(p1, p2);

		if (m_bFilled && i <= 180.0f)
		{
			for (GLfloat j = i, k = 0; k <= offset; j++, k++)
			{
				p1.x = m_centre.x + m_radius * (GLfloat)std::cos(glm::radians(j));
				p1.y = m_centre.y + m_radius * (GLfloat)std::sin(glm::radians(j));

				p2.x = m_centre.x + m_radius * (GLfloat)std::cos(glm::radians(180 + j));
				p2.y = m_centre.y + m_radius * (GLfloat)std::sin(glm::radians(180 + j));
				m_lines.addine(p1, p2);
			}
		}
	}
	m_lines.init();
}

inline void Circle::update(float elapsedTimeInMs)
{
	m_lines.update(elapsedTimeInMs);
}

inline void Circle::render()
{
	m_lines.render();
}

inline void Circle::release()
{
	Drawable::release();
}

inline void Circle::draw()
{
	;
}

inline void Circle::setUniformModel()
{
	m_lines.setUniformModel();
}