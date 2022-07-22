#pragma once

#include <glad/glad.h>

#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Point : public Drawable
{
public:
	Point(GLuint shaderID, bool bOwnIt, glm::vec2 point);
	Point(GLuint shaderID, bool bOwnIt, glm::vec3 point);
	Point(GLuint shaderID, bool bOwnIt, GLfloat x, GLfloat y, GLfloat z = kDEFAULT_Z);

	void init() override;
	void update(float elapsedDeltaTimeInSec) override;
	void render(GLfloat aspectRatio, const Camera& camera) override;
	void release() override;

	glm::vec3 getCentre() override { return m_point; }
protected:
	void draw(GLfloat aspectRatio, const Camera& camera) override;

private:
	glm::vec3		m_point;
};

Point::Point(GLuint shaderID, bool bOwnIt, glm::vec2 point)
	: Drawable(shaderID, bOwnIt)
	, m_point(point, kDEFAULT_Z)
{
	setPixelSize(2);
}

Point::Point(GLuint shaderID, bool bOwnIt, glm::vec3 point)
	: Drawable(shaderID, bOwnIt)
	, m_point(point)
{
	setPixelSize(2);
}

Point::Point(GLuint shaderID, bool bOwnIt, GLfloat x, GLfloat y, GLfloat z)
	: Drawable(shaderID, bOwnIt)
	, m_point(x, y, z)
{
	setPixelSize(2);
}

inline void Point::init()
{
	setVAO(Drawable::createVAO(), true);
	setVBO(Drawable::createVBO(), true);

	activateVAO();
	activateVBO();

	glBufferData(
		GL_ARRAY_BUFFER,				// target
		sizeof(m_point),				// size
		glm::value_ptr(m_point),		// data
		GL_STATIC_DRAW);				// usage

	glVertexAttribPointer(
		0,								// attrib location (as given in shader)
		3,								// value per vertex
		GL_FLOAT,						// data type
		GL_FALSE,						// should normalize?
		0,								// stride
		(void*)0);						// offset

	glEnableVertexAttribArray(0);		// Enable the above attribute

	deactivateVBO();
	deactivateVAO();
}

inline void Point::update(float elapsedDeltaTimeInSec)
{
	(void)elapsedDeltaTimeInSec;
}

inline void Point::render(GLfloat aspectRatio, const Camera& camera)
{
	activateAll();
	setDrawMode();
	draw(aspectRatio, camera);
	
	deactivateAll();
}

inline void Point::release()
{
	Drawable::release();
}

inline void Point::draw(GLfloat aspectRatio, const Camera& camera)
{
	glPointSize(m_pixelSize);

	setUniformProjection(camera.zoomFactor(), aspectRatio);
	setUniformView(camera);
	setUniformModel();
	setUniformColor();

	glDrawArrays(GL_POINTS, 0, 1);
}