#include <glm/gtc/matrix_transform.hpp>

#include "particleManager.h"
#include "shaderProgram.h"
#include "Common/logger.h"
#include <numeric>


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

ParticleManager::ParticleManager(int windowWidth, int windowHeight, glm::vec2 gridStartPos)
	: m_grid(glm::vec2{ 2.0f, 2.0f }, gridStartPos, windowWidth, windowHeight)
	, m_windowWidth(windowWidth)
	, m_windowHeight(windowHeight)
	, m_defaultTransformations(
		glm::vec2{ 2.0f, 2.0f },
		glm::vec2{ ((m_windowWidth / 2.0f) - 2.0f / 2.0f), ((m_windowHeight / 2.0f) - 2.0f / 2.0f) },
		glm::vec2{ 50.0f, 50.0f }
	)
{
	prepareShaders();
	setVertexData();
	prepareBuffers();
	
	bindBuffers();
	setProjectionUniform();

	m_particle.transformations().size = m_defaultTransformations.size;
	m_particle.transformations().scale = m_defaultTransformations.scale;
	m_particle.transformations().position = m_defaultTransformations.position;
}

void ParticleManager::setDrawInWireFrameMode(bool val)
{
	m_bDrawInWireFrame = val;
	m_bDrawInWireFrame ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void ParticleManager::update(float elapsedDeltaTimeInSec)
{
	(void)elapsedDeltaTimeInSec;
}

void ParticleManager::render()
{
	bindBuffers();

	setProjectionUniform();
	setModelUnifrom();
	setColorUnifrom();

	glDrawElements(GL_TRIANGLES, (GLsizei)m_vertexData.indicesVector.size(), GL_UNSIGNED_INT, 0);
}

void ParticleManager::setProjectionUniform()
{
	glm::mat4 projection = glm::mat4{ 1.0f };
	projection = glm::ortho(0.0f, (GLfloat)m_windowWidth, (GLfloat)m_windowHeight, 0.0f, -1.0f, 1.0f);
	ShaderProgram::setUniform_fm(m_shaderProgram, "projection", projection);
}

void ParticleManager::setModelUnifrom()
{
	glm::mat4 model = glm::mat4(1.0f);

	// Order :: Scale -> Rotate -> Translate; so because of matrix we have to do it in reverse order

	// 1st translate
	model = glm::translate(model, glm::vec3{ m_particle.transformations().position, 0.0f });											// position

	// 2nd rotate
	model = glm::translate(model, glm::vec3{ 0.5f * m_particle.transformations().size, 0.0f});											// move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(m_particle.transformations().rotationInDeg), m_particle.transformations().rotationVec);		// then rotate
	// 3rd scale
	model = glm::scale(model, glm::vec3{ m_particle.transformations().size * m_particle.transformations().scale, 0.0f });				// size * scale
	model = glm::translate(model, glm::vec3{ -0.5f * m_particle.transformations().size, 0.0f});											// move origin back
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
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
}

void ParticleManager::unbindBuffers()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
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
	if (!ShaderProgram::attachShader(R"(./resources/Shaders/shader_0.vert)", SHADER_TYPE::VERT, m_shaderProgram))
	{
		ns_Util::Logger::LOG_ERROR("Vertex Shader compilation failed.");
		return;
	}

	if (!ShaderProgram::attachShader(R"(./resources/Shaders/shader_0.frag)", SHADER_TYPE::FRAG, m_shaderProgram))
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
	glGenBuffers(1, &m_vbo);
	glBindVertexArray(m_vao);

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
}


void ParticleManager::release()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	m_vao = m_vbo = m_ebo = 0;
}