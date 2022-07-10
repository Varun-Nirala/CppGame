#include <glm/gtc/matrix_transform.hpp>

#include "particleManager.h"
#include "shaderProgram.h"
#include "Common/logger.h"
#include <numeric>


const glm::vec2 PARTICLE_SIZE = { 2.0f, 2.0f };
const glm::vec2 PARTICLE_SCALE = { 1.0f, 1.0f };

GLuint VertexData::valuePerVertex() const
{
	return std::accumulate(attribVector.begin(), attribVector.end(), 0);
}

GLuint VertexData::stride() const
{
	return valuePerVertex() * sizeof(GLfloat);
}

GLuint VertexData::sizeInBytes() const
{
	return stride() * vertexCount;
}

ParticleManager::~ParticleManager()
{
	release();
}

ParticleManager::ParticleManager(PARTICLE_TYPE type, int windowWidth, int windowHeight, glm::vec2 gridStartPos)
	: m_grid(PARTICLE_SIZE, PARTICLE_SCALE, gridStartPos, windowWidth, windowHeight)
	, m_defaultParticle(type)
	, m_windowWidth(windowWidth)
	, m_windowHeight(windowHeight)
	, m_defaultTransformations(
		PARTICLE_SIZE,
		PARTICLE_SCALE,
		glm::vec2{ ((m_windowWidth / 2.0f) - (PARTICLE_SIZE.x * PARTICLE_SCALE.x)),	((m_windowHeight / 2.0f) - (PARTICLE_SIZE.y * PARTICLE_SCALE.y)) }
	)
{
	prepareShaders();
	setVertexData();
	prepareBuffers();

	m_defaultParticle.transformations().size = m_defaultTransformations.size;
	m_defaultParticle.transformations().scale = m_defaultTransformations.scale;
	m_defaultParticle.transformations().position = m_defaultTransformations.position;

	switch (m_defaultParticle.type())
	{
		case PARTICLE_TYPE::SAND:
			m_particleColor = glm::vec4{ kCOLOR_SANDY_BROWN, 1.0f };
			break;

		case PARTICLE_TYPE::WATER:
			m_particleColor = glm::vec4{ kCOLOR_AQUA, 1.0f };
			break;

		case PARTICLE_TYPE::FIRE:
			m_particleColor = glm::vec4{ kCOLOR_RED, 1.0f };
			break;
	}

	bindBuffers();
	setProjectionUniform();
	setColorUnifrom();
}

void ParticleManager::setDrawInWireFrameMode(bool val)
{
	m_bDrawInWireFrame = val;
	m_bDrawInWireFrame ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ParticleManager::update(float elapsedDeltaTimeInSec)
{
	if (m_instancePosition.size() < m_grid.size())
	{
		Particle *pNewParticle = m_defaultParticle.clone();
		pNewParticle->transformations().position = m_grid[0][m_grid.cols() / 2].position;

		m_grid[0][m_grid.cols() / 2].particle = pNewParticle;
	}

	switch (m_defaultParticle.type())
	{
		case PARTICLE_TYPE::SAND:
			updateSandParticle(elapsedDeltaTimeInSec);
			break;

		case PARTICLE_TYPE::WATER:
			updateWaterParticle(elapsedDeltaTimeInSec);
			break;

		case PARTICLE_TYPE::FIRE:
			updateFireParticle(elapsedDeltaTimeInSec);
			break;
	}

	for (size_t i = 0, rows = m_grid.rows(); i < rows; ++i)
	{
		for (size_t j = 0, cols = m_grid.cols(); j < cols; ++j)
		{
			if (m_grid[i][j].particle)
			{
				m_instancePosition.push_back(m_grid[i][j].position);
			}
		}
	}
}

void ParticleManager::render()
{
	for (size_t i = 0, rows = m_grid.rows(); i < rows; ++i)
	{
		for (size_t j = 0, cols = m_grid.cols(); j < cols; ++j)
		{
			if (!m_grid.isEmpty(i, j))
			{
				//bindBuffers();
				//setProjectionUniform();
				//setColorUnifrom();
				setModelUnifrom(m_grid[i][j].particle);
				//glDrawElements(GL_TRIANGLES, (GLsizei)m_vertexData.indicesVector.size(), GL_UNSIGNED_INT, 0);
				try
				{
					glDrawElementsInstanced(GL_TRIANGLES, (GLsizei)m_vertexData.indicesVector.size(), GL_UNSIGNED_INT, 0, (GLsizei)m_instancePosition.size());
				}
				catch (std::exception& e)
				{
					ns_Util::Logger::LOG_ERROR("Exception : ", e.what(), '\n');
				}
			}
		}
	}
}

void ParticleManager::setProjectionUniform()
{
	glm::mat4 projection = glm::mat4{ 1.0f };
	projection = glm::ortho(0.0f, (GLfloat)m_windowWidth, (GLfloat)m_windowHeight, 0.0f, -1.0f, 1.0f);
	ShaderProgram::setUniform_fm(m_shaderProgram, "projection", projection);
}

void ParticleManager::setModelUnifrom(Particle *p)
{
	glm::mat4 model = glm::mat4(1.0f);

	// Order :: Scale -> Rotate -> Translate; so because of matrix we have to do it in reverse order

	// 1st translate
	model = glm::translate(model, glm::vec3{ p->transformations().position, 0.0f });									// position

	// 2nd rotate
	model = glm::translate(model, glm::vec3{ 0.5f * p->transformations().size, 0.0f});									// move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(p->transformations().rotationInDeg), p->transformations().rotationVec);		// then rotate
	// 3rd scale
	model = glm::scale(model, glm::vec3{ p->transformations().size * p->transformations().scale, 0.0f });				// size * scale
	model = glm::translate(model, glm::vec3{ -0.5f * p->transformations().size, 0.0f});									// move origin back
	ShaderProgram::setUniform_fm(m_shaderProgram, "model", model);
}

void ParticleManager::setColorUnifrom()
{
	ShaderProgram::setUniform_fv(m_shaderProgram, "color", m_particleColor);
}

void ParticleManager::bindBuffers()
{
	ShaderProgram::activate(m_shaderProgram);
	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
}

void ParticleManager::unbindBuffers()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	ShaderProgram::deactivate();
}

void ParticleManager::setVertexData()
{
	m_vertexData.attribVector.push_back(2);
	m_vertexData.vertexCount = 4;
	m_vertexData.indicesVector = std::vector<GLuint>{
		0, 1, 3,		// 1st Triangle
		1, 2, 3			// 2nd Triangle
	};

	m_vertexData.vertices = std::vector<GLfloat>{
		2.0f, 0.0f,		// Top Right
		2.0f, 2.0f,		// Bottom Right
		0.0f, 2.0f,		// Bottom Left
		0.0f, 0.0f		// Top Left
	};
}

void ParticleManager::prepareShaders()
{
	m_shaderProgram = ShaderProgram::createShader();
	if (!ShaderProgram::attachShader(R"(./resources/Shaders/shader_1.vert)", SHADER_TYPE::VERT, m_shaderProgram))
	{
		ns_Util::Logger::LOG_ERROR("Vertex Shader compilation failed.");
		return;
	}

	if (!ShaderProgram::attachShader(R"(./resources/Shaders/shader_1.frag)", SHADER_TYPE::FRAG, m_shaderProgram))
	{
		ns_Util::Logger::LOG_ERROR("Fragment Shader compilation failed.");
		return;
	}

	if (!ShaderProgram::linkShader(m_shaderProgram))
	{
		ns_Util::Logger::LOG_ERROR("Shader linking failed.");
		return;
	}
}

void ParticleManager::prepareBuffers()
{
	// Create buffers
	glGenVertexArrays(1, &m_vao);
	glBindVertexArray(m_vao);

	glGenBuffers(1, &m_vbo);

	// VBO 
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
	glBufferData(
		GL_ARRAY_BUFFER,				// target
		m_vertexData.sizeInBytes(),		// size
		m_vertexData.vertices.data(),	// data
		GL_STATIC_DRAW);				// usage

	GLint buffSize = 0;
	glGetBufferParameteriv(GL_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffSize);

	if (m_vertexData.sizeInBytes() != (GLuint)buffSize)
	{
		ns_Util::Logger::LOG_ERROR("Error setting Vertex Array Buffer data.\n");
	}

	// VBO Attribs
	glVertexAttribPointer(0, m_vertexData.attribVector[0], GL_FLOAT, GL_FALSE, m_vertexData.stride(), (void*)0);
	glEnableVertexAttribArray(0);


	// EBO
	glGenBuffers(1, &m_ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_vertexData.indicesVector.size() * sizeof(GLuint), m_vertexData.indicesVector.data(), GL_STATIC_DRAW);

	buffSize = 0;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &buffSize);

	if (m_vertexData.indicesVector.size() * sizeof(GLuint) != (GLuint)buffSize)
	{
		ns_Util::Logger::LOG_ERROR("Error setting Vertex Element Buffer data.\n");
	}

	// Instance VBO
	m_instancePosition.reserve(m_grid.size());
	glGenBuffers(1, &m_instanceVbo);
	glBindBuffer(GL_ARRAY_BUFFER, m_instanceVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_instancePosition.size(), m_instancePosition.data(), GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, m_instanceVbo);		 // this attribute comes from a different vertex buffer
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glVertexAttribDivisor(1, 1);						// tell OpenGL this is an instanced vertex attribute.
}

void ParticleManager::updateSandParticle(float elapsedDeltaTimeInSec)
{
	(void)elapsedDeltaTimeInSec;
	for (size_t i = m_grid.rows(); i-- > 0;)
	{
		for (size_t j = 0, cols = m_grid.cols() - 1; j < cols; ++j)
		{
			if (!m_grid.isEmpty(i, j) && m_grid[i][j].particle->canUpdate())
			{
				if (m_grid.isEmpty(i, j, Direction::BELOW))
				{
					m_grid.move(i, j, Direction::BELOW);
				}
				else if (m_grid.isEmpty(i, j, Direction::BELOW_LEFT))
				{
					m_grid.move(i, j, Direction::BELOW_LEFT);
				}
				else if (m_grid.isEmpty(i, j, Direction::BELOW_RIGHT))
				{
					m_grid.move(i, j, Direction::BELOW_RIGHT);
				}
				else
				{
					m_grid[i][j].particle->setCanUpdate(false);
				}
			}
		}
	}
}

void ParticleManager::updateWaterParticle(float elapsedDeltaTimeInSec)
{
	(void)elapsedDeltaTimeInSec;
	for (size_t i = m_grid.rows(); i-- > 0;)
	{
		for (size_t j = 0, cols = m_grid.cols() - 1; j < cols; ++j)
		{
			if (!m_grid.isEmpty(i, j) && m_grid[i][j].particle->canUpdate())
			{
				if (m_grid.isEmpty(i, j, Direction::BELOW))
				{
					m_grid.move(i, j, Direction::BELOW);
				}
				else if (m_grid.isEmpty(i, j, Direction::BELOW_LEFT))
				{
					m_grid.move(i, j, Direction::BELOW_LEFT);
				}
				else if (m_grid.isEmpty(i, j, Direction::BELOW_RIGHT))
				{
					m_grid.move(i, j, Direction::BELOW_RIGHT);
				}
				else if (m_grid.isEmpty(i, j, Direction::LEFT))
				{
					m_grid.move(i, j, Direction::LEFT);
				}
				else if (m_grid.isEmpty(i, j, Direction::RIGHT))
				{
					m_grid.move(i, j, Direction::RIGHT);
				}
				else
				{
					m_grid[i][j].particle->setCanUpdate(false);
				}
			}
		}
	}
}

void ParticleManager::updateFireParticle(float elapsedDeltaTimeInSec)
{
	(void)elapsedDeltaTimeInSec;
}

void ParticleManager::release()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	glDeleteBuffers(1, &m_instanceVbo);
	m_instanceVbo = m_vao = m_vbo = m_ebo = 0;
}