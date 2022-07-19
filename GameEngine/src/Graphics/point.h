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
	Point(GLuint shaderID, bool bOwnIt, GLfloat x, GLfloat y, GLfloat z = 0.0f);

	void init() override;
	void update(float elapsedTimeInMs) override;
	void render(GLfloat fovy, GLfloat aspectRatio, const Camera& camera) override;
	void release() override;

	void setUniformModel() override;

	glm::vec3 getCentre() override { return m_point; }
protected:
	void draw(GLfloat fovy, GLfloat aspectRatio, const Camera& camera) override;

private:
	glm::vec3		m_point;
};

Point::Point(GLuint shaderID, bool bOwnIt, glm::vec2 point)
	: Drawable(shaderID, bOwnIt)
	, m_point(point, 0.0f)
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

inline void Point::update(float elapsedTimeInMs)
{
	(void)elapsedTimeInMs;
}

inline void Point::render(GLfloat fovy, GLfloat aspectRatio, const Camera& camera)
{
	activateAll();
	setDrawMode();
	draw(fovy, aspectRatio, camera);
	
	deactivateAll();
}

inline void Point::release()
{
	Drawable::release();
}

inline void Point::draw(GLfloat fovy, GLfloat aspectRatio, const Camera& camera)
{
	glPointSize(m_pixelSize);

	setUniformProjection(fovy, aspectRatio);
	setUniformView(camera);
	setUniformModel();
	setUniformColor();

	glDrawArrays(GL_POINTS, 0, 1);
}

inline void Point::setUniformModel()
{
	glm::mat4 model = glm::identity<glm::mat4>();

	// Order :: Scale -> Rotate -> Translate; so because of matrix we have to do it in reverse order

	// 1st translate
	//model = glm::translate(model, m_point);

	// 2nd rotate
	//model = glm::translate(model, glm::vec3{ 0.5f * size });				// move origin of rotation to center of quad
	//model = glm::rotate(model, glm::radians(rotationInDeg), rotationVec);	// then rotate
	//model = glm::translate(model, glm::vec3{ -0.5f * size });				// move origin back

	// 3rd scale
	//model = glm::scale(model, size * scale);

	ShaderProgram::setUniform_fm(m_shader.first, "model", model);
}
