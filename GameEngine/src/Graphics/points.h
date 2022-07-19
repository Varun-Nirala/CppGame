#pragma once

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "drawable.h"

class Points : public Drawable
{
public:
	Points(GLuint shaderID, bool bOwnIt);

	void setPoints(const std::vector<glm::vec3>& points);
	void addPoint(const glm::vec3& point);

	void init() override;
	void update(float elapsedTimeInMs) override;
	void render(GLfloat fovy, GLfloat aspectRatio, const Camera& camera) override;
	void release() override;

	glm::vec3 getCentre() override { return {}; }
protected:
	void draw(GLfloat fovy, GLfloat aspectRatio, const Camera& camera) override;

private:
	std::vector<glm::vec3>		m_points;
};

Points::Points(GLuint shaderID, bool bOwnIt)
	: Drawable(shaderID, bOwnIt)
{
	setPixelSize(2);
}

inline void Points::setPoints(const std::vector<glm::vec3>& points)
{
	m_points = points;
}

inline void Points::addPoint(const glm::vec3& point)
{
	m_points.push_back(point);
}

inline void Points::init()
{
	setVAO(Drawable::createVAO(), true);
	setVBO(Drawable::createVBO(), true);

	activateVAO();
	activateVBO();

	glBufferData(
		GL_ARRAY_BUFFER,							// target
		sizeof(GLfloat) * 3 * m_points.size(),		// size
		glm::value_ptr(m_points[0]),				// data
		GL_STATIC_DRAW);							// usage

	glVertexAttribPointer(
		0,											// attrib location (as given in shader)
		3,											// value per vertex
		GL_FLOAT,									// data type
		GL_FALSE,									// should normalize?
		0,											// stride
		(void*)0);									// offset

	glEnableVertexAttribArray(0);					// Enable the above attribute

	deactivateVBO();
	deactivateVAO();
}

inline void Points::update(float elapsedTimeInMs)
{
	(void)elapsedTimeInMs;
}

inline void Points::render(GLfloat fovy, GLfloat aspectRatio, const Camera& camera)
{
	activateAll();
	setDrawMode();
	draw(fovy, aspectRatio, camera);

	deactivateAll();
}

inline void Points::release()
{
	Drawable::release();
}

inline void Points::draw(GLfloat fovy, GLfloat aspectRatio, const Camera& camera)
{
	glPointSize(m_pixelSize);

	setUniformProjection(fovy, aspectRatio);
	setUniformView(camera);
	setUniformModel();
	setUniformColor();

	glDrawArrays(GL_POINTS, 0, (GLsizei)m_points.size());
}