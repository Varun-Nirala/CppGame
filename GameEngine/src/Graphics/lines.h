#pragma once

#include "drawable.h"

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

class Lines : public Drawable
{
public:
	Lines(GLuint shaderID, bool bOwnIt);

	void setLines(const std::vector<glm::vec2> &lines);
	void setLines(const std::vector<glm::vec3> &lines);
	
	void addine(const glm::vec2 p1, const glm::vec2 p2);
	void addine(const glm::vec3 p1, const glm::vec3 p2);

	void setMakeLoop(bool val);
	
	void init() override;
	void update(float elapsedTimeInMs) override;
	void render() override;
	void release() override;

	void setUniformModel() override;
	glm::vec3 getCentre() override { return {}; }
protected:
	void draw() override;

private:
	std::vector<glm::vec3>			m_lines;
	bool							m_bMakeLoop{ false };
};

Lines::Lines(GLuint shaderID, bool bOwnIt)
	: Drawable(shaderID, bOwnIt)
{
	setLineWidth(2);
}

inline void Lines::setLines(const std::vector<glm::vec2>& lines)
{
	m_lines.clear();
	m_lines.reserve(lines.size());
	for (auto& x : lines)
	{
		m_lines.push_back(glm::vec3(x, 0.0f));
	}
}

inline void Lines::setLines(const std::vector<glm::vec3>& lines)
{
	m_lines = lines;
}

inline void Lines::addine(const glm::vec2 p1, const glm::vec2 p2)
{
	m_lines.push_back(glm::vec3(p1, 0.0f));
	m_lines.push_back(glm::vec3(p2, 0.0f));
}

inline void Lines::addine(const glm::vec3 p1, const glm::vec3 p2)
{
	m_lines.push_back(p1);
	m_lines.push_back(p2);
}

inline void Lines::setMakeLoop(bool val)
{
	m_bMakeLoop = val;
}

inline void Lines::init()
{
	setVAO(Drawable::createVAO(), true);
	setVBO(Drawable::createVBO(), true);

	activateVAO();
	activateVBO();

	glBufferData(
		GL_ARRAY_BUFFER,							// target
		sizeof(GLfloat) * 3 * m_lines.size(),		// size
		glm::value_ptr(m_lines[0]),					// data
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

inline void Lines::update(float elapsedTimeInMs)
{
	(void)elapsedTimeInMs;
}

inline void Lines::render()
{
	activateAll();

	draw();

	deactivateAll();
}

inline void Lines::release()
{
	Drawable::release();
}

inline void Lines::draw()
{
	glPointSize(m_pixelSize);
	glLineWidth(m_lineWidth);

	setUniformProjection();
	setUniformView();
	setUniformModel();
	setUniformColor();
	
	if (m_bMakeLoop)
	{
		glDrawArrays(GL_LINE_LOOP, 0, (GLsizei)m_lines.size());
	}
	else
	{
		glDrawArrays(GL_LINES, 0, (GLsizei)m_lines.size());
	}
}

inline void Lines::setUniformModel()
{
	glm::mat4 model = glm::identity<glm::mat4>();

	// Order :: Scale -> Rotate -> Translate; so because of matrix we have to do it in reverse order

	// 1st translate
	//model = glm::translate(model, m_lines[0]);

	// 2nd rotate
	//model = glm::translate(model, glm::vec3{ 0.5f * size });				// move origin of rotation to center of quad
	//model = glm::rotate(model, glm::radians(rotationInDeg), rotationVec);	// then rotate
	//model = glm::translate(model, glm::vec3{ -0.5f * size });				// move origin back

	// 3rd scale
	//model = glm::scale(model, size * scale);

	ShaderProgram::setUniform_fm(m_shader.first, "model", model);
}