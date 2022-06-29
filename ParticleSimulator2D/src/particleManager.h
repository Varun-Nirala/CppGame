#pragma once

#include <glad/glad.h>

#include <vector>
#include "particle.h"
#include "grid.h"
#include "Common/constants.h"

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

	void update(float elapsedDeltaTimeInSec);
	void render();

private:
	void setProjectionUniform();
	void setModelUnifrom();
	void setColorUnifrom();

	void bindBuffers();
	void unbindBuffers();

	void setVertexData();
	void prepareShaders();
	void prepareBuffers();

	void release();

private:
	GLuint					m_windowWidth{};
	GLuint					m_windowHeight{};
	GLuint					m_shaderProgram{};
	GLuint					m_vao{};
	GLuint					m_vbo{};
	GLuint					m_ebo{};
	VertexData				m_vertexData;
	Grid					m_grid;
	
	Particle				m_particle;

	glm::vec4				m_particleColor{ kCOLOR_SANDY_BROWN, 1.0f };
	bool					m_bDrawInWireFrame{ false };

	const Transformations	m_defaultTransformations;
};