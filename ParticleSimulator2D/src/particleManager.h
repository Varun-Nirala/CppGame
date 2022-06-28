#pragma once

#include <glad/glad.h>

#include <vector>
#include "particle.h"
#include "grid.h"

struct VertexData
{
	GLuint					vertexCount;
	std::vector<GLuint>		attribVector;
	std::vector<GLuint>		indicesVector;
	std::vector<GLfloat>	vertices;

	GLuint valuePerVertex() const;
	GLuint stride() const;
	GLuint sizeInBytes() const;
};



class ParticleManager
{
public:
	~ParticleManager();
	ParticleManager(int windowWidth, int windowHeight, glm::vec2 gridStartPos = { 0.0f, 0.0f });

	void setDrawInWireFrameMode(bool val);

	void bindBuffers();
	void unbindBuffers();
	void update(float elapsedDeltaTimeInSec);
	void render();

private:
	void setProjectionUniform();
	void setModelUnifrom();
	void setColorUnifrom();
	void release();

private:
	GLuint			m_windowWidth{};
	GLuint			m_windowHeight{};
	GLuint			m_shaderProgram{};
	GLuint			m_vao{};
	GLuint			m_vbo{};
	GLuint			m_ebo{};
	VertexData		m_VertexData;
	Grid			m_grid;
	
	glm::vec4		m_particleColor{};
	bool			m_bDrawInWireFrame{ false };
};