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
	Circle(GLuint shaderID, bool bOwnIt, GLfloat radius, GLfloat x, GLfloat y, GLfloat z = kDEFAULT_Z);

	void setDrawInWireFrameMode(bool mode) override;

	void init() override;
	void update(float elapsedDeltaTimeInSec) override;
	void render(GLfloat aspectRatio, const Camera& camera) override;
	void release() override;

	void setUniformModel() override;

	glm::vec3 getCentre() override { return m_centre; }

protected:
	void draw(GLfloat aspectRatio, const Camera& camera) override;
	void allocateTriangle(GLuint shaderID, bool bOwnIt);
private:
	glm::vec3				m_centre;
	GLfloat					m_radius{};
	std::vector<Triangle*>	m_triangles;
	const GLuint			m_triangleCount{ 45 };
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

inline void Circle::setDrawInWireFrameMode(bool mode)
{
	if (m_bDrawInWireFrameMode != mode)
	{
		m_bDrawInWireFrameMode = mode;
		for (size_t i = 0; i < m_triangles.size(); ++i)
		{
			m_triangles[i]->setDrawInWireFrameMode(mode);
		}
	}
}

inline void Circle::init()
{
	// Create and assign points
	// r2 = x2 + y2
	// x = rcos0
	// y = rsin0
	glm::vec3 p1 = m_centre;

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

inline void Circle::update(float elapsedDeltaTimeInSec)
{
	for (GLuint i = 0; i < m_triangleCount; ++i)
	{
		m_triangles[i]->update(elapsedDeltaTimeInSec);
	}
}

inline void Circle::render(GLfloat aspectRatio, const Camera& camera)
{
	for (GLuint i = 0; i < m_triangleCount; ++i)
	{
		m_triangles[i]->render(aspectRatio, camera);
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

inline void Circle::draw(GLfloat aspectRatio, const Camera& camera)
{
	(void)camera;
	(void)aspectRatio;
}

inline void Circle::allocateTriangle(GLuint shaderID, bool bOwnIt)
{
	m_triangles.resize(m_triangleCount);
	for (GLuint i = 0; i < m_triangleCount; ++i)
	{
		m_triangles[i] = new Triangle(shaderID, bOwnIt);
		m_triangles[i]->setDrawInWireFrameMode(m_bDrawInWireFrameMode);
	}
}

inline void Circle::setUniformModel()
{
	for (GLuint i = 0; i < m_triangleCount; ++i)
	{
		m_triangles[i]->setUniformModel();
	}
}