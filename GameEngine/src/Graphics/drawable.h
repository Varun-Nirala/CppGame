#pragma once

#include <utility>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Common/constants.h"
#include "shaderProgram.h"

class Drawable
{
public:
	Drawable(GLuint shaderID, bool bOwnIt)
	{
		m_shader.first = shaderID;
		m_shader.second = bOwnIt;
	}

	void setPixelSize(GLfloat size) { m_pixelSize = size; }
	void setLineWidth(GLfloat width) { m_lineWidth = width; }
	void setRotationAngle(GLfloat angleInDeg) { m_rotAngleInDegree = angleInDeg; }
	void setRotationAxis(glm::vec3 axis) { m_rotAxis = axis; }
	void setRotationAxis(GLfloat x, GLfloat y, GLfloat z) { m_rotAxis = glm::vec3{ x, y, z }; }

	GLfloat getPixelSize() const { return m_pixelSize; }
	GLfloat getLineWidth() const { return m_lineWidth; }
	GLfloat getRotationAngleInDeg() { return m_rotAngleInDegree; }
	glm::vec3 getRotationAxis() { return m_rotAxis; }

	void setColor(glm::vec3 color) { m_color = glm::vec4(color, 1.0f); }
	void setColor(glm::vec4 color) { m_color = color; }

	void setShader(GLuint id, bool bOwnIt) { m_shader.first = id; m_shader.second = bOwnIt; }
	void setVAO(GLuint id, bool bOwnIt) { m_vao.first = id; m_vao.second = bOwnIt; }
	void setVBO(GLuint id, bool bOwnIt) { m_vbo.first = id; m_vbo.second = bOwnIt; }

	void activateShader() { glUseProgram(m_shader.first); }
	void activateVAO() { glBindVertexArray(m_vao.first); }
	void activateVBO() { glBindBuffer(GL_ARRAY_BUFFER, m_vbo.first); }

	void deactivateShader() { glUseProgram(0); }
	void deactivateVAO() { glBindVertexArray(0); }
	void deactivateVBO() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	virtual void init() = 0;
	virtual void update(float elapsedTimeInMs) = 0;
	virtual void render() = 0;

	virtual void release();

	virtual void activateAll();
	virtual void deactivateAll();

	virtual void setUniformProjection();
	virtual void setUniformView();
	virtual void setUniformModel() = 0;
	virtual void setUniformColor();

	virtual glm::vec3 getCentre() = 0;

	static GLuint createVAO();
	static GLuint createVBO();
	static GLuint createEBO();
protected:
	virtual void draw() = 0;

protected:
	std::pair<GLuint, bool>			m_shader;
	std::pair<GLuint, bool>			m_vao;
	std::pair<GLuint, bool>			m_vbo;
	glm::vec4						m_color{ 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat							m_pixelSize{ 1 };
	GLfloat							m_lineWidth{ 1 };
	GLfloat							m_rotAngleInDegree{};
	glm::vec3						m_rotAxis{ 0.0f, 0.0f, 1.0f };
};

inline void Drawable::release()
{
	if (m_shader.second && m_shader.first)
	{
		glDeleteProgram(m_shader.first);
	}

	if (m_vao.second && m_vao.first)
	{
		glDeleteVertexArrays(1, &m_vao.first);
	}

	if (m_vbo.second && m_vbo.first)
	{
		glDeleteBuffers(1, &m_vbo.first);
	}
	m_shader.first = m_vao.first = m_vbo.first = 0;
}

inline void Drawable::activateAll()
{
	activateShader();
	activateVAO();
	activateVBO();
}

inline void Drawable::deactivateAll()
{
	deactivateVBO();
	deactivateVAO();
	deactivateShader();
}

inline void Drawable::setUniformProjection()
{
	glm::mat4 projection = glm::identity<glm::mat4>();
	
	projection = glm::ortho(0.0f, (GLfloat)WIDTH, (GLfloat)HEIGHT, 0.0f, CAM_NEAR, CAM_FAR);
	
	ShaderProgram::setUniform_fm(m_shader.first, "projection", projection);
}

inline void Drawable::setUniformModel()
{
	glm::mat4 model = glm::identity<glm::mat4>();

	// Order :: Scale -> Rotate -> Translate; so because of matrix we have to do it in reverse order

	// 1st translate
	//model = glm::translate(model, position);

	// 2nd rotate
	//model = glm::translate(model, glm::vec3{ 0.5f * size });				// move origin of rotation to center of quad
	//model = glm::rotate(model, glm::radians(rotationInDeg), rotationVec);	// then rotate
	//model = glm::translate(model, glm::vec3{ -0.5f * size });				// move origin back

	// 3rd scale
	//model = glm::scale(model, size * scale);

	ShaderProgram::setUniform_fm(m_shader.first, "model", model);
}

inline void Drawable::setUniformView()
{
	glm::mat4 view = glm::identity<glm::mat4>();

	view = glm::lookAt(VIEW_POSITION, VIEW_POSITION + VIEW_FRONT, VIEW_UP);

	ShaderProgram::setUniform_fm(m_shader.first, "view", view);
}

inline void Drawable::setUniformColor()
{
	ShaderProgram::setUniform_fv(m_shader.first, "color", m_color);
}

inline GLuint Drawable::createVAO()
{
	GLuint id{};
	glGenVertexArrays(1, &id);
	return id;
}

inline GLuint Drawable::createVBO()
{
	GLuint id{};
	glGenBuffers(1, &id);
	return id;
}

inline GLuint Drawable::createEBO()
{
	GLuint id{};
	glGenBuffers(1, &id);
	return id;
}