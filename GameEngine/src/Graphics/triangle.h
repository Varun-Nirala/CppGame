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
	void render() override;
	void release() override;

protected:
	void draw() override;

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

inline void Triangle::render()
{
	activateAll();

	draw();

	deactivateAll();
}

inline void Triangle::release()
{
	Drawable::release();
}

inline void Triangle::draw()
{
	ShaderProgram::setUniform_fv(m_shader.first, "color", m_color);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}