#pragma once

#include <vector>

#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "points.h"

#include "lines.h"

#include "triangleStrip.h"

class Sphere : public Drawable
{
public:
	Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec2 centre, GLint longitude, GLint latitude);
	Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec3 centre, GLint longitude, GLint latitude);
	Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, GLfloat x, GLfloat y, GLfloat z, GLint longitude, GLint latitude);

	void setDrawInWireFrameMode(bool mode) override;

	void init() override;
	void update(float elapsedTimeInMs) override;
	void render(GLfloat fovy, GLfloat aspectRatio, const Camera& camera) override;
	void release() override;

	void setUniformModel() override;

	glm::vec3 getCentre() override { return m_centre; }

protected:
	void draw(GLfloat fovy, GLfloat aspectRatio, const Camera& camera) override;
	void allocateTriangleStrip(GLuint shaderID, bool bOwnIt);
	GLfloat mapValue(GLint value, GLint currRangeMin, GLint currRangeMax, GLfloat targetRangeMin, GLfloat targetRangeMax);

private:
	glm::vec3						m_centre;
	GLfloat							m_radius{ 1.0f };
	GLint							m_longitude{ 3 };		// Horizontal
	GLint							m_latitude{ 2 };		// Vertical

	std::vector<TriangleStrip*>		m_triStrips;
};

Sphere::Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec2 centre, GLint longitude, GLint latitude)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(centre, 0.0f)
	, m_longitude(longitude)
	, m_latitude(latitude)
{
	allocateTriangleStrip(shaderID, false);
}

Sphere::Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec3 centre, GLint longitude, GLint latitude)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(centre)
	, m_longitude(longitude)
	, m_latitude(latitude)
{
	allocateTriangleStrip(shaderID, false);
}

Sphere::Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, GLfloat x, GLfloat y, GLfloat z, GLint longitude, GLint latitude)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(x, y, z)
	, m_longitude(longitude)
	, m_latitude(latitude)
{
	allocateTriangleStrip(shaderID, false);
}

inline void Sphere::setDrawInWireFrameMode(bool mode)
{
	if (m_bDrawInWireFrameMode != mode)
	{
		m_bDrawInWireFrameMode = mode;
		for (size_t i = 0; i < m_latitude; ++i)
		{
			m_triStrips[i]->setDrawInWireFrameMode(mode);
		}
	}
}

inline void Sphere::init()
{
	constexpr GLfloat PI = glm::pi<float>();
	constexpr GLfloat HALF_PI = PI / 2.0f;

	std::vector<std::vector<glm::vec3>> grid(m_latitude + 1, std::vector<glm::vec3>(m_longitude + 1, glm::vec3{}));

	for (GLint lat = 0; lat < m_latitude + 1; ++lat)
	{
		GLfloat latAngle = mapValue(lat, 0, m_latitude, -HALF_PI, HALF_PI);
		for (GLint lon = 0; lon < m_longitude + 1; ++lon)
		{
			GLfloat lonAngle = mapValue(lon, 0, m_longitude, -PI, PI);
		
			glm::vec3 vertex;
			vertex.x = m_radius * std::sinf(lonAngle) * std::cosf(latAngle);
			vertex.y = m_radius * std::sinf(lonAngle) * std::sinf(latAngle);
			vertex.z = m_radius * std::cosf(lonAngle);

			grid[lat][lon] = vertex + m_centre;
		}
	}

	for (GLint lat = 0; lat < m_latitude; ++lat)
	{
		m_triStrips[lat]->setDrawInWireFrameMode(m_bDrawInWireFrameMode);
		for (GLint lon = 0; lon < m_longitude + 1; ++lon)
		{
			// v1 v3 v5
			// v2 v4 v6
			m_triStrips[lat]->addTriangleVertex(grid[lat][lon]);			// v1
			m_triStrips[lat]->addTriangleVertex(grid[lat + 1][lon]);		// v2
		}
	}

	for (GLint lat = 0; lat < m_latitude; ++lat)
	{
		m_triStrips[lat]->init();
	}
}

inline void Sphere::update(float elapsedTimeInMs)
{
	for (GLint lat = 0; lat < m_latitude; ++lat)
	{
		m_triStrips[lat]->update(elapsedTimeInMs);
	}
}

inline void Sphere::render(GLfloat fovy, GLfloat aspectRatio, const Camera& camera)
{
	setDrawMode();
	for (GLint lat = 0; lat < m_latitude; ++lat)
	{
		m_triStrips[lat]->render(fovy, aspectRatio, camera);
	}
}

inline void Sphere::release()
{
	Drawable::release();

	for (GLint lat = 0; lat < m_latitude; ++lat)
	{
		delete m_triStrips[lat];
	}
	m_triStrips.clear();
}

inline void Sphere::setUniformModel()
{
	for (GLint lat = 0; lat < m_latitude; ++lat)
	{
		m_triStrips[lat]->setUniformModel();
	}
}

inline void Sphere::draw(GLfloat fovy, GLfloat aspectRatio, const Camera& camera)
{
	(void)camera;
	(void)fovy;
	(void)aspectRatio;
	return;
}

inline void Sphere::allocateTriangleStrip(GLuint shaderID, bool bOwnIt)
{
	m_triStrips.resize(m_latitude);
	for (GLint lat = 0; lat < m_latitude; ++lat)
	{
		m_triStrips[lat] = new TriangleStrip(shaderID, bOwnIt);
		m_triStrips[lat]->setDrawInWireFrameMode(m_bDrawInWireFrameMode);
	}
}

inline GLfloat Sphere::mapValue(GLint value, GLint currRangeMin, GLint currRangeMax, GLfloat targetRangeMin, GLfloat targetRangeMax)
{
	return ((value - currRangeMin) / GLfloat(currRangeMax - currRangeMin)) * (targetRangeMax - targetRangeMin) + targetRangeMin;
}