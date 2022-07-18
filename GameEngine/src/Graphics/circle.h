#pragma once

#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "triangle.h"

class Circle : public Drawable
{
public:
	Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec2 centre);
	Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec3 centre);
	Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, GLfloat x, GLfloat y, GLfloat z = 0.0f);

	void setDrawFilled(bool val) { m_bFilled = val; }

	void init() override;
	void update(float elapsedTimeInMs) override;
	void render(GLfloat fovy, GLfloat aspectRatio) override;
	void release() override;

	void setUniformModel() override;

	glm::vec3 getCentre() override { return m_centre; }

protected:
	void draw(GLfloat fovy, GLfloat aspectRatio) override;
	void allocateTriangle(GLuint shaderID, bool bOwnIt);
private:
	glm::vec3				m_centre;
	GLfloat					m_radius{};
	std::vector<Triangle*>	m_triangles;
	GLuint					m_triangleCount{ 45 };
	bool					m_bFilled{ false };
};

Circle::Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec2 centre)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(centre, 0.0f)
{
	allocateTriangle(shaderID, false);
}

Circle::Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec3 centre)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(centre)
{
	allocateTriangle(shaderID, false);
}

Circle::Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, GLfloat x, GLfloat y, GLfloat z)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(x, y, z)
{
	allocateTriangle(shaderID, false);
}

inline void Circle::init()
{
	// Create and assign points
	// r2 = x2 + y2
	// x = rcos0
	// y = rsin0
	glm::vec3 p1 = m_centre;
	p1.x += m_radius;

	glm::vec3 p2 = p1;
	GLfloat offset = 360.0f / m_triangleCount;

	std::vector<glm::vec3> vec(3);
	GLuint id = 0;
	for (GLfloat i = 0; i < 360.0f; i += offset)
	{
		p1.x = m_centre.x + m_radius * (GLfloat)std::cos(glm::radians(i));
		p1.y = m_centre.y + m_radius * (GLfloat)std::sin(glm::radians(i));

		p2.x = m_centre.x + m_radius * (GLfloat)std::cos(glm::radians(i + offset));
		p2.y = m_centre.y + m_radius * (GLfloat)std::sin(glm::radians(i + offset));

		vec[0] = p1;
		vec[1] = p2;
		vec[2] = m_centre;

		m_triangles[id]->setTriangle(vec);
		m_triangles[id++]->init();
	}
}

inline void Circle::update(float elapsedTimeInMs)
{
	for (GLuint i = 0; i < m_triangleCount; ++i)
	{
		m_triangles[i]->update(elapsedTimeInMs);
	}
}

inline void Circle::render(GLfloat fovy, GLfloat aspectRatio)
{
	for (GLuint i = 0; i < m_triangleCount; ++i)
	{
		m_triangles[i]->render(fovy, aspectRatio);
	}
}

inline void Circle::release()
{
	Drawable::release();
	for (GLuint i = 0; i < m_triangleCount; ++i)
	{
		delete m_triangles[i];
	}
	m_triangles.clear();
}

inline void Circle::draw(GLfloat fovy, GLfloat aspectRatio)
{
	(void)fovy;
	(void)aspectRatio;
}

inline void Circle::allocateTriangle(GLuint shaderID, bool bOwnIt)
{
	m_triangles.resize(m_triangleCount);
	for (GLuint i = 0; i < m_triangleCount; ++i)
	{
		m_triangles[i] = new Triangle(shaderID, bOwnIt);
	}
}

inline void Circle::setUniformModel()
{
	for (GLuint i = 0; i < m_triangleCount; ++i)
	{
		m_triangles[i]->setUniformModel();
	}
}