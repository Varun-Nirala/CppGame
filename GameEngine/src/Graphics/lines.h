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
	void update(float elapsedDeltaTimeInSec) override;
	void render(GLfloat aspectRatio, const Camera& camera) override;
	void release() override;

	glm::vec3 getCentre() override { return {}; }
protected:
	void draw(GLfloat aspectRatio, const Camera& camera) override;

private:
	std::vector<glm::vec3>			m_lines;
	bool							m_bMakeLoop{ false };
};

Lines::Lines(GLuint shaderID, bool bOwnIt)
	: Drawable(shaderID, bOwnIt)
{
}

inline void Lines::setLines(const std::vector<glm::vec2>& lines)
{
	m_lines.clear();
	m_lines.reserve(lines.size());
	for (auto& x : lines)
	{
		m_lines.push_back(glm::vec3(x, kDEFAULT_Z));
	}
}

inline void Lines::setLines(const std::vector<glm::vec3>& lines)
{
	m_lines = lines;
}

inline void Lines::addine(const glm::vec2 p1, const glm::vec2 p2)
{
	m_lines.push_back(glm::vec3(p1, kDEFAULT_Z));
	m_lines.push_back(glm::vec3(p2, kDEFAULT_Z));
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

inline void Lines::update(float elapsedDeltaTimeInSec)
{
	(void)elapsedDeltaTimeInSec;
}

inline void Lines::render(GLfloat aspectRatio, const Camera& camera)
{
	activateAll();
	setDrawMode();

	draw(aspectRatio, camera);

	deactivateAll();
}

inline void Lines::release()
{
	Drawable::release();
}

inline void Lines::draw(GLfloat aspectRatio, const Camera& camera)
{
	glPointSize(m_pixelSize);

	setUniformProjection(camera.zoomFactor(), aspectRatio);
	setUniformView(camera);
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