#pragma once

#include <vector>

#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "points.h"

class Sphere : public Drawable
{
public:
	Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec2 centre, GLint longitude, GLint latitude);
	Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec3 centre, GLint longitude, GLint latitude);
	Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, GLfloat x, GLfloat y, GLfloat z, GLint longitude, GLint latitude);

	void init() override;
	void update(float elapsedTimeInMs) override;
	void render(GLfloat fovy, GLfloat aspectRatio) override;
	void release() override;

	void setUniformModel() override;

	glm::vec3 getCentre() override { return m_centre; }

protected:
	void draw(GLfloat fovy, GLfloat aspectRatio) override;
	GLfloat mapValue(GLint value, GLint currRangeMin, GLint currRangeMax, GLfloat targetRangeMin, GLfloat targetRangeMax);
private:
	GLuint					m_ebo{};

	glm::vec3				m_centre;
	GLfloat					m_radius{ 1.0f };
	GLint					m_longitude{ 3 };		// Horizontal
	GLint					m_latitude{ 2 };		// Vertical

	Points					m_points;
};

Sphere::Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec2 centre, GLint longitude, GLint latitude)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(centre, 0.0f)
	, m_longitude(longitude)
	, m_latitude(latitude)
	, m_points(shaderID, bOwnIt)
{
	init();
}

Sphere::Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, glm::vec3 centre, GLint longitude, GLint latitude)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(centre)
	, m_longitude(longitude)
	, m_latitude(latitude)
	, m_points(shaderID, bOwnIt)
{
	init();
}

Sphere::Sphere(GLuint shaderID, bool bOwnIt, GLfloat radius, GLfloat x, GLfloat y, GLfloat z, GLint longitude, GLint latitude)
	: Drawable(shaderID, bOwnIt)
	, m_radius(radius)
	, m_centre(x, y, z)
	, m_longitude(longitude)
	, m_latitude(latitude)
	, m_points(shaderID, bOwnIt)
{
	init();
}

inline void Sphere::init()
{
	constexpr GLfloat PI = glm::pi<float>();
	constexpr GLfloat HALF_PI = PI / 2.0f;

	for (GLint i = 0; i < m_longitude; ++i)
	{
		GLfloat lonAngle = mapValue(i, 0, m_longitude, -PI, PI);

		for (GLint j = 0; j < m_latitude; ++j)
		{
			GLfloat latAngle = mapValue(j, 0, m_latitude, -HALF_PI, HALF_PI);

			glm::vec3 vertex;
			vertex.x = m_radius * std::sinf(lonAngle) * std::cosf(latAngle);
			vertex.y = m_radius * std::sinf(lonAngle) * std::sinf(latAngle);
			vertex.z = m_radius * std::cosf(lonAngle);
			m_points.addPoint(vertex + m_centre);
		}
	}
	m_points.init();
}

inline void Sphere::update(float elapsedTimeInMs)
{
	m_points.update(elapsedTimeInMs);
}

inline void Sphere::render(GLfloat fovy, GLfloat aspectRatio)
{
	m_points.render(fovy, aspectRatio);
}

inline void Sphere::release()
{
	Drawable::release();
	m_points.release();
}

inline void Sphere::setUniformModel()
{
	m_points.setUniformModel();
}

inline void Sphere::draw(GLfloat fovy, GLfloat aspectRatio)
{
	(void)fovy;
	(void)aspectRatio;
	return;
}

inline GLfloat Sphere::mapValue(GLint value, GLint currRangeMin, GLint currRangeMax, GLfloat targetRangeMin, GLfloat targetRangeMax)
{
	return ((value - currRangeMin) / GLfloat(currRangeMax - currRangeMin)) * (targetRangeMax - targetRangeMin) + targetRangeMin;
}