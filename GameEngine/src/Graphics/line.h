#pragma once

#include "drawable.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Line : public Drawable
{
public:
	Line(GLuint shaderID, bool bOwnIt, glm::vec2 p1, glm::vec2 p2);
	Line(GLuint shaderID, bool bOwnIt, glm::vec3 p1, glm::vec3 p2);
	Line(GLuint shaderID, bool bOwnIt, GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2);

	void setLine(const glm::vec3& p1, const glm::vec3& p2);
	void setLine(const glm::vec2& p1, const glm::vec2& p2);

	void init() override;
	void update(float elapsedTimeInMs) override;
	void render(GLfloat fovy, GLfloat aspectRatio) override;
	void release() override;

	void setUniformModel() override;

	glm::vec3 getCentre() override { return m_p[0] + (m_p[1] - m_p[0]) / 2.0f; }
protected:
	void draw(GLfloat fovy, GLfloat aspectRatio) override;

private:
	glm::vec3		m_p[2];
};

Line::Line(GLuint shaderID, bool bOwnIt, glm::vec2 p1, glm::vec2 p2)
	: Drawable(shaderID, bOwnIt)
{
	setLine(p1, p2);
}

Line::Line(GLuint shaderID, bool bOwnIt, glm::vec3 p1, glm::vec3 p2)
	: Drawable(shaderID, bOwnIt)
{
	setLine(p1, p2);
}

Line::Line(GLuint shaderID, bool bOwnIt, GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2)
	: Drawable(shaderID, bOwnIt)
{
	m_p[0] = glm::vec3(x1, y1, z1);
	m_p[1] = glm::vec3(x2, y2, z2);
}

inline void Line::setLine(const glm::vec3& p1, const glm::vec3& p2)
{
	m_p[0] = p1;
	m_p[1] = p2;
}

inline void Line::setLine(const glm::vec2& p1, const glm::vec2& p2)
{
	m_p[0] = glm::vec3(p1, 0.0f);
	m_p[1] = glm::vec3(p2, 0.0f);
}

inline void Line::init()
{
	setVAO(Drawable::createVAO(), true);
	setVBO(Drawable::createVBO(), true);

	activateVAO();
	activateVBO();

	glBufferData(
		GL_ARRAY_BUFFER,				// target
		sizeof(GLfloat) * 3 * 2,		// size
		glm::value_ptr(m_p[0]),			// data
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

inline void Line::update(float elapsedTimeInMs)
{
	(void)elapsedTimeInMs;
}

inline void Line::render(GLfloat fovy, GLfloat aspectRatio)
{
	activateAll();

	draw(fovy, aspectRatio);

	deactivateAll();
}

inline void Line::release()
{
	Drawable::release();
}

inline void Line::draw(GLfloat fovy, GLfloat aspectRatio)
{
	glPointSize(m_pixelSize);
	
	setUniformProjection(fovy, aspectRatio);
	setUniformView();
	setUniformModel();
	setUniformColor();

	glDrawArrays(GL_LINES, 0, 2);
}

inline void Line::setUniformModel()
{
	glm::mat4 model = glm::identity<glm::mat4>();

	// Order :: Scale -> Rotate -> Translate; so because of matrix we have to do it in reverse order

	// 1st translate
	//model = glm::translate(model, m_p[0]);

	// 2nd rotate
	glm::vec3 centroid = getCentre();

	model = glm::translate(model, centroid);										// move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(m_rotAngleInDegree), m_rotAxis);		// then rotate
	model = glm::translate(model, -centroid);										// move origin back

	// 3rd scale
	//model = glm::scale(model, size * scale);

	ShaderProgram::setUniform_fm(m_shader.first, "model", model);
}