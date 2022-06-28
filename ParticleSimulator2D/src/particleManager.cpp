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
{
	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);
	glGenBuffers(1, &m_ebo);

	m_VertexData.attribVector.push_back(2);
	m_VertexData.vertexCount = 4;
	m_VertexData.indicesVector = std::vector<GLuint>{
		0, 1, 3,		// 1st Triangle
		1, 2, 3			// 2nd Triangle
	};

	m_VertexData.vertices = std::vector<GLfloat>{
		0.0f, 1.0f,		// Top Right
		0.0f, 0.0f,		// Bottom Right
		1.0f, 0.0f,		// Bottom Left
		1.0f, 1.0f		// Top Left
	};

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

void ParticleManager::setDrawInWireFrameMode(bool val)
{
	m_bDrawInWireFrame = val;
	m_bDrawInWireFrame ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
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

void ParticleManager::update(float elapsedDeltaTimeInSec)
{
	(void)elapsedDeltaTimeInSec;
}

void ParticleManager::render()
{

}

void ParticleManager::setProjectionUniform()
{
	glm::mat4 projection = glm::ortho(0.0f, (GLfloat)m_windowWidth, (GLfloat)m_windowHeight, 0.0f, -1.0f, 1.0f);
	ShaderProgram::setUniform_fm(m_shaderProgram, "uniform_projection", projection);
}

void ParticleManager::setModelUnifrom()
{
	glm::mat4 model = glm::mat4(1.0f);

	// Order :: Scale -> Rotate -> Translate; so because of matrix we have to do it in reverse order

	// 1st translate
	model = glm::translate(model, glm::vec3{});	// position

	// 2nd rotate
	model = glm::translate(model, glm::vec3{ 0.5f * glm::vec2{}, 0.0f });	// Size							// move origin of rotation to center of quad
	model = glm::rotate(model, glm::radians(float(0)), glm::vec3{});		// Rotation angle and vector	// then rotate
	model = glm::translate(model, glm::vec3{ -0.5f * glm::vec2{}, 0.0f });	// Size							// move origin back

	// 3rd scale
	model = glm::scale(model, glm::vec3{ glm::vec2{}  *glm::vec2{}, 0.0f });	// size * scale

	ShaderProgram::setUniform_fm(m_shaderProgram, "uniform_model", model);
}

void ParticleManager::setColorUnifrom()
{
	ShaderProgram::setUniform_fv(m_shaderProgram, "uniform_color", m_particleColor);
}

void ParticleManager::release()
{
	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);
	glDeleteBuffers(1, &m_ebo);
	m_vao = m_vbo = m_ebo = 0;
}