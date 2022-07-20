#pragma once

#include <utility>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Common/constants.h"
#include "shaderProgram.h"
#include "Camera/camera.h"

class Drawable
{
public:
	Drawable(GLuint shaderID, bool bOwnIt)
	{
		m_shader.first = shaderID;
		m_shader.second = bOwnIt;
	}

	void setPixelSize(GLfloat size) { m_pixelSize = size; }
	void setRotationAngle(GLfloat angleInDeg) { m_rotAngleInDegree = angleInDeg; }
	void setRotationAxis(const glm::vec3 &axis) { m_rotAxis = axis; }
	void setRotationAxis(GLfloat x, GLfloat y, GLfloat z) { m_rotAxis = glm::vec3{ x, y, z }; }
	void setTranslatePosition(const glm::vec3& pos) { m_translatePosition = pos; }
	void setTranslatePosition(GLfloat x, GLfloat y, GLfloat z) { m_translatePosition = glm::vec3{ x, y, z }; }
	void setScale(const glm::vec3& pos) { m_scale = pos; }
	void setScale(GLfloat x, GLfloat y, GLfloat z) { m_scale = glm::vec3{ x, y, z }; }

	GLfloat getPixelSize() const { return m_pixelSize; }
	GLfloat getRotationAngleInDeg() { return m_rotAngleInDegree; }
	glm::vec3 getRotationAxis() { return m_rotAxis; }
	glm::vec3 setTranslatePosition() const{ return m_translatePosition; }
	glm::vec3 setScale() const { return m_scale; }

	void setColor(glm::vec3 color) { m_color = glm::vec4(color, 1.0f); }
	void setColor(glm::vec4 color) { m_color = color; }

	void setShader(GLuint id, bool bOwnIt) { m_shader.first = id; m_shader.second = bOwnIt; }
	void setVAO(GLuint id, bool bOwnIt) { m_vao.first = id; m_vao.second = bOwnIt; }
	void setVBO(GLuint id, bool bOwnIt) { m_vbo.first = id; m_vbo.second = bOwnIt; }

	virtual void setDrawInWireFrameMode(bool mode) { m_bDrawInWireFrameMode = mode; }

	void activateShader() { glUseProgram(m_shader.first); }
	void activateVAO() { glBindVertexArray(m_vao.first); }
	void activateVBO() { glBindBuffer(GL_ARRAY_BUFFER, m_vbo.first); }

	void deactivateShader() { glUseProgram(0); }
	void deactivateVAO() { glBindVertexArray(0); }
	void deactivateVBO() { glBindBuffer(GL_ARRAY_BUFFER, 0); }

	virtual void init() = 0;
	virtual void update(float elapsedTimeInMs) = 0;
	virtual void render(GLfloat fovy, GLfloat aspectRatio, const Camera &camera) = 0;

	virtual void release();

	virtual void activateAll();
	virtual void deactivateAll();

	virtual void setUniformProjection(GLfloat fovy, GLfloat aspectRatio);
	virtual void setUniformView(const Camera& camera);
	virtual void setUniformModel();
	virtual void setUniformColor();

	virtual glm::vec3 getCentre() = 0;

	static GLuint createVAO();
	static GLuint createVBO();
	static GLuint createEBO();
protected:
	void setDrawMode();
	virtual void draw(GLfloat fovy, GLfloat aspectRatio, const Camera& camera) = 0;

protected:
	std::pair<GLuint, bool>			m_shader;
	std::pair<GLuint, bool>			m_vao;
	std::pair<GLuint, bool>			m_vbo;
	glm::vec4						m_color{ 1.0f, 0.0f, 0.0f, 1.0f };
	GLfloat							m_pixelSize{ 1 };

	GLfloat							m_rotAngleInDegree{};
	glm::vec3						m_rotAxis{ 0.0f, 0.0f, 1.0f };
	glm::vec3						m_scale{ 1.0f };
	glm::vec3						m_translatePosition{ 0.0f, 0.0f, -2.0f };

	bool							m_bDrawInWireFrameMode{ false };
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

inline void Drawable::setUniformProjection(GLfloat fovy, GLfloat aspectRatio)
{
	glm::mat4 projection = glm::identity<glm::mat4>();
	if (kbOrthographicView)
	{
		projection = glm::ortho(0.0f, (GLfloat)WIDTH, (GLfloat)HEIGHT, 0.0f, kORTHOGRAPHIC_NEAR, kORTHOGRAPHIC_FAR);
	}
	else
	{
		projection = glm::perspective(glm::radians(fovy), aspectRatio, kPERSPECTIVE_NEAR, kPERSPECTIVE_FAR);
	}
	ShaderProgram::setUniform_fm(m_shader.first, "projection", projection);
}

inline void Drawable::setUniformView(const Camera& camera)
{
	ShaderProgram::setUniform_fm(m_shader.first, "view", camera.viewMatrix());
}

inline void Drawable::setUniformModel()
{
	glm::mat4 model(1.0f);

	// Order :: Scale -> Rotate -> Translate; so because of matrix we have to do it in reverse order

	glm::vec3 orthoGrpahicTranslate{};
	GLfloat orthoGraphicScale = 1.0f;
	if (kbOrthographicView)
	{
		orthoGrpahicTranslate = glm::vec3(WIDTH / 2.0f, HEIGHT / 2.0f, -kDEFAULT_Z);
		orthoGraphicScale = 100.0f;
	}

	// 1st translate
	model = glm::translate(model, m_translatePosition + orthoGrpahicTranslate);

	// 2nd rotate

	glm::vec3 centroid = getCentre();

	model = glm::translate(model, centroid);										// move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(m_rotAngleInDegree), m_rotAxis);		// then rotate
	model = glm::translate(model, -centroid);										// move origin back

	// 3rd scale
	model = glm::scale(model, m_scale * orthoGraphicScale);

	ShaderProgram::setUniform_fm(m_shader.first, "model", model);
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

inline void Drawable::setDrawMode()
{
	if (m_bDrawInWireFrameMode)
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else
	{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
}