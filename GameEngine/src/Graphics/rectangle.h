#pragma once

#include <array>
#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Rectangle : public Drawable
{
public:
	Rectangle(GLuint shaderID, bool bOwnIt);

	void setRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height);

	void setEBO(GLuint id, bool bOwnIt) { m_ebo.first = id; m_ebo.second = bOwnIt; }

	void init() override;
	void update(float elapsedTimeInMs) override;
	void render() override;
	void release() override;

	void activateAll() override;
	void deactivateAll() override;

	void activateEBO();
	void deactivateEBO();
protected:
	void draw() override;

private:
	glm::vec3					m_vertices[4];
	std::array<GLuint, 6>		m_indices;
	std::pair<GLuint, bool>		m_ebo;
};

Rectangle::Rectangle(GLuint shaderID, bool bOwnIt)
	: Drawable(shaderID, bOwnIt)
{}

inline void Rectangle::setRectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
{
	m_vertices[0].x = x;
	m_vertices[0].y = y;

	m_vertices[1].x = x + width;
	m_vertices[1].y = y;

	m_vertices[2].x = x;
	m_vertices[2].y = y + height;

	m_vertices[3].x = x + width;
	m_vertices[3].y = y + height;

	m_vertices[0].z = m_vertices[1].z = m_vertices[2].z = m_vertices[3].z = 0.0f;

	m_indices = { 0, 1, 2, 1, 2, 3 };
}

inline void Rectangle::init()
{
	setVAO(Drawable::createVAO(), true);
	setVBO(Drawable::createVBO(), true);
	setEBO(Drawable::createEBO(), true);

	activateVAO();
	activateVBO();
	activateEBO();

	glBufferData(
		GL_ARRAY_BUFFER,				// target
		sizeof(m_vertices),				// size
		m_vertices,						// data
		GL_STATIC_DRAW);				// usage

	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		(GLsizei)m_indices.size() * sizeof(GLuint),
		m_indices.data(),
		GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,								// attrib location (as given in shader)
		3,								// value per vertex
		GL_FLOAT,						// data type
		GL_FALSE,						// should normalize?
		0,								// stride
		(void*)0);						// offset

	glEnableVertexAttribArray(0);		// Enable the above attribute

	deactivateEBO();
	deactivateVBO();
	deactivateVAO();
}

inline void Rectangle::update(float elapsedTimeInMs)
{
	(void)elapsedTimeInMs;
}

inline void Rectangle::render()
{
	activateAll();

	draw();

	deactivateAll();
}

inline void Rectangle::release()
{
	Drawable::release();
	if (m_ebo.second && m_ebo.first)
	{
		glDeleteBuffers(1, &m_ebo.first);
	}
	m_ebo.first = 0;
}

inline void Rectangle::activateAll()
{
	activateShader();
	activateVAO();
	activateVBO();
	activateEBO();
}

inline void Rectangle::deactivateAll()
{
	deactivateVBO();
	deactivateVAO();
	deactivateShader();
	deactivateEBO();
}

inline void Rectangle::activateEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo.first);
}

inline void Rectangle::deactivateEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

inline void Rectangle::draw()
{
	ShaderProgram::setUniform_fv(m_shader.first, "color", m_color);
	glDrawElements(GL_TRIANGLES, (GLsizei)m_indices.size(), GL_UNSIGNED_INT, 0);
}