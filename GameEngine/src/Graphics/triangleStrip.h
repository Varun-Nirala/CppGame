#pragma once

#include <array>
#include <vector>
#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class TriangleStrip : public Drawable
{
public:
	TriangleStrip(GLuint shaderID, bool bOwnIt);

	void addTriangleVertex(const glm::vec2 v);
	void addTriangleVertex(const glm::vec3 v);

	void init() override;
	void update(float elapsedTimeInMs) override;
	void render(GLfloat fovy, GLfloat aspectRatio, const Camera& camera) override;
	void release() override;

	glm::vec3 getCentre() override { return {}; }
protected:
	void draw(GLfloat fovy, GLfloat aspectRatio, const Camera& camera) override;

private:
	std::vector<glm::vec3>				m_vertices;
};

TriangleStrip::TriangleStrip(GLuint shaderID, bool bOwnIt)
	: Drawable(shaderID, bOwnIt)
{
}

inline void TriangleStrip::addTriangleVertex(const glm::vec2 v)
{
	m_vertices.push_back(glm::vec3(v, kDEFAULT_Z));
}

inline void TriangleStrip::addTriangleVertex(const glm::vec3 v)
{
	m_vertices.push_back(v);
}

inline void TriangleStrip::init()
{
	setVAO(Drawable::createVAO(), true);
	setVBO(Drawable::createVBO(), true);

	activateVAO();
	activateVBO();

	glBufferData(
		GL_ARRAY_BUFFER,							// target
		sizeof(GLfloat) * 3 * m_vertices.size(),	// size
		glm::value_ptr(m_vertices[0]), 				// data
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

inline void TriangleStrip::update(float elapsedTimeInMs)
{
	(void)elapsedTimeInMs;
}

inline void TriangleStrip::render(GLfloat fovy, GLfloat aspectRatio, const Camera& camera)
{
	activateAll();
	setDrawMode();
	draw(fovy, aspectRatio, camera);

	deactivateAll();
}

inline void TriangleStrip::release()
{
	Drawable::release();
}

inline void TriangleStrip::draw(GLfloat fovy, GLfloat aspectRatio, const Camera& camera)
{
	setUniformProjection(fovy, aspectRatio);
	setUniformView(camera);
	setUniformModel();
	setUniformColor();

	glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)m_vertices.size());
}