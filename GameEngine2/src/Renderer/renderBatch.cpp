#include <glad/glad.h>

#include "Renderer/renderBatch.h"

#include "Components/spriteRenderer.h"

#include "Display/displayWindow.h"
#include "shaderProgram.h"

#include "transform.h"
#include "gameObject.h"

#include "scene.h"

#include "texture.h"

#include "Common/logger.h"

RenderBatch::~RenderBatch()
{
	destroyBuffer(m_vboID);
	destroyBuffer(m_eboID);
	destroyVertexArray(m_vaoID);
	destroyProgram(m_shaderID);

	for (size_t i = 0, size = m_sprites.size(); i < size; ++i)
	{
		delete m_sprites[i];
	}

	for (size_t i = 0, size = m_textures.size(); i < size; ++i)
	{
		delete m_textures[i];
	}

	m_sprites.clear();
	m_numOfSprites = 0;
	m_vertices.clear();
}

RenderBatch::RenderBatch(GLint maxBatchSize)
	: m_maxBatchSize(maxBatchSize)
{
	m_sprites.resize(m_maxBatchSize);

	m_vertices.resize(m_maxBatchSize * 4 * m_VERTEX_SIZE);

	// 6 indices per quad (3 per triangle
	m_indices.resize(m_maxBatchSize * 6);

	m_numOfSprites = 0;
	m_bHasRoom = true;
}

void RenderBatch::start()
{
	createShaderAndBuffer();

	bindVAO();
	bindVBO();

	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), m_vertices.data(), GL_DYNAMIC_DRAW);

	bindEBO();
	generateIndices();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), m_indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, (GLint)m_POS_SIZE, GL_FLOAT, GL_FALSE, (GLsizei)m_VERTEX_SIZE_BYTES, (void *)(m_POS_OFFSET));
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, (GLint)m_COLOR_SIZE, GL_FLOAT, GL_FALSE, (GLsizei)m_VERTEX_SIZE_BYTES, (void *)(m_COLOR_OFFSET));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, (GLint)m_TEX_COORDS_SIZE, GL_FLOAT, GL_FALSE, (GLsizei)m_VERTEX_SIZE_BYTES, (void*)(m_TEX_COORDS_OFFSET));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, (GLint)m_TEX_ID_SIZE, GL_FLOAT, GL_FALSE, (GLsizei)m_VERTEX_SIZE_BYTES, (void*)(m_TEX_ID_OFFSET));
	glEnableVertexAttribArray(3);
}

void RenderBatch::addSprite(SpriteRenderer* pSpriteRenderer)
{
	m_sprites[m_numOfSprites] = pSpriteRenderer;

	if (pSpriteRenderer->getTexture())
	{
		bool bAlreadyThere = false;
		for (size_t i = 0; i < m_textures.size(); ++i)
		{
			if (m_textures[i] == pSpriteRenderer->getTexture())
			{
				bAlreadyThere = true;
				break;
			}
		}

		if (!bAlreadyThere)
		{
			m_textures.push_back(pSpriteRenderer->getTexture());
		}
	}

	loadVertexProperties(m_numOfSprites++);

	if (m_numOfSprites >= m_maxBatchSize)
	{
		m_bHasRoom = false;
	}
}

void RenderBatch::loadVertexProperties(GLint index)
{
	SpriteRenderer* pSprite = m_sprites[index];

	// find offst within array (4 vertices per sprite)
	size_t offset = index * 4 * m_VERTEX_SIZE;

	const glm::vec4& color = pSprite->getColor();
	const std::vector<glm::vec2>& texCoords = pSprite->getTexCoords();

	GLuint texID = 0;

	if (pSprite->getTexture())
	{
		for (size_t i = 0; i < m_textures.size(); ++i)
		{
			if (m_textures[i] == pSprite->getTexture())
			{
				texID = (GLuint)i + 1;
				break;
			}
		}
	}

	// add vertex with the appropriate properties

	GLfloat xAdd{ 1.0f };
	GLfloat yAdd{ 1.0f };

	for (size_t i = 0; i < 4; ++i)
	{
		if (i == 1)
		{
			yAdd = 0.0f;
		}
		else if (i == 2)
		{
			xAdd = 0.0f;
		}
		else if (i == 3)
		{
			yAdd = 1.0f;
		}

		// Load position first
		Transform& t = pSprite->getGameObject()->getTransform();

		m_vertices[offset + 0] = t.getPosition().x + (xAdd * t.getScale().x);
		m_vertices[offset + 1] = t.getPosition().y + (yAdd * t.getScale().y);

		// Load color
		m_vertices[offset + 2] = color.r;
		m_vertices[offset + 3] = color.g;
		m_vertices[offset + 4] = color.b;
		m_vertices[offset + 5] = color.a;

		// Load texture coordinates
		m_vertices[offset + 6] = texCoords[i].x;
		m_vertices[offset + 7] = texCoords[i].y;

		// Load texture id
		m_vertices[offset + 8] = (GLfloat)texID;

		offset += m_VERTEX_SIZE;
	}
}

bool RenderBatch::hasTexture(Texture* pTexture) const
{
	return std::find(m_textures.begin(), m_textures.end(), pTexture) != m_textures.end();
}

void RenderBatch::render()
{
	bindVBO();

	glBufferSubData(GL_ARRAY_BUFFER, 0, m_vertices.size() * sizeof(GLfloat), m_vertices.data());

	attachProgram();

	ShaderProgram::setUniform_fm(m_shaderID, "uProjection", DisplayWindow::getInstance().getScene()->getCamera().getProjectionMatrix());
	ShaderProgram::setUniform_fm(m_shaderID, "uView", DisplayWindow::getInstance().getScene()->getCamera().getViewMatrix());

	for (size_t i = 0; i < m_textures.size(); ++i)
	{
		glActiveTexture(GL_TEXTURE0 + (GLenum)i + 1);
		m_textures[i]->bind();
	}

	ShaderProgram::setUniform_1iv(m_shaderID, "uTextures", (GLsizei)m_texSlots.size(), m_texSlots.data());

	bindVAO();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glDrawElements(GL_TRIANGLES, m_numOfSprites * 6, GL_UNSIGNED_INT, (void *)0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
	glDisableVertexAttribArray(3);
	
	unBindVBO();
	unBindVAO();

	for (size_t i = 0; i < m_textures.size(); ++i)
	{
		m_textures[i]->unBind();
	}

	detachProgram();
}

void RenderBatch::generateIndices()
{
	m_indices.resize(m_maxBatchSize * 6);
	for (GLint i = 0; i < m_maxBatchSize; ++i)
	{
		loadElementIndices(i);
	}
}

void RenderBatch::loadElementIndices(GLint index)
{
	int offsetArrayIndex = 6 * index;
	int offset = 4 * index;

	// Quad_1 : 3, 2, 0, 0, 2, 1				Quad_2 : 7, 6, 4, 4, 6, 5
	// Traingle 1
	m_indices[offsetArrayIndex + 0] = offset + 3;
	m_indices[offsetArrayIndex + 1] = offset + 2;
	m_indices[offsetArrayIndex + 2] = offset + 0;

	// Traingle 2
	m_indices[offsetArrayIndex + 3] = offset + 0;
	m_indices[offsetArrayIndex + 4] = offset + 2;
	m_indices[offsetArrayIndex + 5] = offset + 1;
}

bool RenderBatch::createShaderAndBuffer()
{
	createProgram(m_shaderID);

	if (!ShaderProgram::attachShader(R"(.\resources\Shaders\default.vert)", SHADER_TYPE::VERT, m_shaderID))
	{
		ns_Util::Logger::LOG_ERROR("unable to compile vertex shader!\n");
		assert(false);
		return false;
	}

	if (!ShaderProgram::attachShader(R"(.\resources\Shaders\default.frag)", SHADER_TYPE::FRAG, m_shaderID))
	{
		ns_Util::Logger::LOG_ERROR("unable to compile fragment shader!\n");
		assert(false);
		return false;
	}

	if (!ShaderProgram::linkShader(m_shaderID))
	{
		ns_Util::Logger::LOG_ERROR("unable to link shaders!\n");
		assert(false);
		return false;
	}

	createVertexArray(m_vaoID);
	createBuffer(m_vboID);
	createBuffer(m_eboID);

	return true;
}

void RenderBatch::createProgram(GLuint& id)
{
	if (id)
	{
		destroyProgram(id);
	}
	id = ShaderProgram::createShader();
}

void RenderBatch::createVertexArray(GLuint& id)
{
	if (id)
	{
		destroyVertexArray(id);
	}
	glGenVertexArrays(1, &id);
}

void RenderBatch::createBuffer(GLuint& id)
{
	if (id)
	{
		destroyBuffer(id);
	}
	glGenBuffers(1, &id);
}

void RenderBatch::destroyProgram(GLuint& id)
{
	ShaderProgram::destroyShader(id);
}

void RenderBatch::destroyVertexArray(GLuint& id)
{
	glDeleteVertexArrays(1, &id);
	id = 0;
}

void RenderBatch::destroyBuffer(GLuint& id)
{
	glDeleteBuffers(1, &id);
	id = 0;
}

void RenderBatch::attachProgram()
{
	ShaderProgram::activate(m_shaderID);
}

void RenderBatch::bindVAO()
{
	glBindVertexArray(m_vaoID);
}

void RenderBatch::bindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
}

void RenderBatch::bindEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_eboID);
}

void RenderBatch::detachProgram()
{
	ShaderProgram::deactivate();
}

void RenderBatch::unBindVAO()
{
	glBindVertexArray(0);
}

void RenderBatch::unBindVBO()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void RenderBatch::unBindEBO()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}