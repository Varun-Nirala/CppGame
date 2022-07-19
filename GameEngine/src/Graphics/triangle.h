#pragma once

#include <array>
#include <vector>
#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Triangle : public Drawable
{
public:
	Triangle(GLuint shaderID, bool bOwnIt);

	void setTriangle(const std::vector<glm::vec2>& vec);
	void setTriangle(const std::vector<glm::vec3> &vec);

	void init() override;
	void update(float elapsedTimeInMs) override;
	void render(GLfloat fovy, GLfloat aspectRatio, const Camera& camera) override;
	void release() override;

	glm::vec3 getCentre() override;
protected:
	void draw(GLfloat fovy, GLfloat aspectRatio, const Camera& camera) override;

private:
	glm::vec3					m_vertices[3];
};

Triangle::Triangle(GLuint shaderID, bool bOwnIt)
	: Drawable(shaderID, bOwnIt)
{
}

inline void Triangle::setTriangle(const std::vector<glm::vec2>& vec)
{
	m_vertices[0] = glm::vec3(vec[0], 0.0f);
	m_vertices[1] = glm::vec3(vec[1], 0.0f);
	m_vertices[2] = glm::vec3(vec[2], 0.0f);
}

inline void Triangle::setTriangle(const std::vector<glm::vec3>& vec)
{
	m_vertices[0] = vec[0];
	m_vertices[1] = vec[1];
	m_vertices[2] = vec[2];
}

inline void Triangle::init()
{
	setVAO(Drawable::createVAO(), true);
	setVBO(Drawable::createVBO(), true);

	activateVAO();
	activateVBO();

	glBufferData(
		GL_ARRAY_BUFFER,				// target
		sizeof(m_vertices),				// size
		m_vertices,						// data
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

inline void Triangle::update(float elapsedTimeInMs)
{
	(void)elapsedTimeInMs;
}

inline void Triangle::render(GLfloat fovy, GLfloat aspectRatio, const Camera& camera)
{
	activateAll();
	setDrawMode();
	draw(fovy, aspectRatio, camera);

	deactivateAll();
}

inline void Triangle::release()
{
	Drawable::release();
}

inline void Triangle::draw(GLfloat fovy, GLfloat aspectRatio, const Camera& camera)
{
	setUniformProjection(fovy, aspectRatio);
	setUniformView(camera);
	setUniformModel();
	setUniformColor();

	glDrawArrays(GL_TRIANGLES, 0, 3);
}

inline glm::vec3 Triangle::getCentre()
{
	glm::vec3 centroid{};
	centroid.x = (m_vertices[0].x + m_vertices[1].x + m_vertices[2].x) / 3.0f;
	centroid.y = (m_vertices[0].y + m_vertices[1].y + m_vertices[2].y) / 3.0f;
	centroid.z = (m_vertices[0].z + m_vertices[1].z + m_vertices[2].z) / 3.0f;
	return centroid;
}