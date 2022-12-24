#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <vector>
#include <array>

class SpriteRenderer;
class Texture;

#define MAX_TEXTURES 8

class RenderBatch
{
public:
	~RenderBatch();
	explicit RenderBatch(GLint maxBatchSize);

	void start();

	void addSprite(SpriteRenderer* pSpriteRenderer);
	void loadVertexProperties(GLint index);

	bool hasRoom() const { return m_bHasRoom; }

	bool hasTextureRoom() const { return m_textures.size() < MAX_TEXTURES; }

	bool hasTexture(Texture* pTexture) const;

	void render();

private:
	void generateIndices();
	void loadElementIndices(GLint index);

	bool createShaderAndBuffer();

	void createProgram(GLuint& id);
	void createVertexArray(GLuint& id);
	void createBuffer(GLuint& id);

	void destroyProgram(GLuint& id);
	void destroyVertexArray(GLuint& id);
	void destroyBuffer(GLuint& id);

	void attachProgram();
	void bindVAO();
	void bindVBO();
	void bindEBO();

	void detachProgram();
	void unBindVAO();
	void unBindVBO();
	void unBindEBO();

private:
	const size_t					m_POS_SIZE{ 2 };
	const size_t					m_COLOR_SIZE{ 4 };
	const size_t					m_TEX_COORDS_SIZE{ 2 };
	const size_t					m_TEX_ID_SIZE{ 1 };

	const size_t					m_POS_OFFSET{ 0 };
	const size_t					m_COLOR_OFFSET{ m_POS_OFFSET + m_POS_SIZE * sizeof(GLfloat) };
	const size_t					m_TEX_COORDS_OFFSET{ m_COLOR_OFFSET + m_COLOR_SIZE * sizeof(GLfloat) };
	const size_t					m_TEX_ID_OFFSET{ m_TEX_COORDS_OFFSET + m_TEX_COORDS_SIZE * sizeof(GLfloat) };
	const size_t					m_VERTEX_SIZE{ 9 };		// 2 pos and 4 colors 2 tex coords 1 tex id
	const size_t					m_VERTEX_SIZE_BYTES{ m_VERTEX_SIZE * sizeof(GLfloat) };

	std::vector<SpriteRenderer*>	m_sprites;
	GLint							m_numOfSprites{};
	bool							m_bHasRoom{ true };

	std::vector<Texture*>			m_textures;
	std::array<GLint, 8>			m_texSlots{ 0, 1, 2, 3, 4, 5, 6, 7 };

	const GLint						m_maxBatchSize{};

	std::vector<GLfloat>			m_vertices;
	std::vector<GLuint>				m_indices;
	GLuint							m_vaoID{};
	GLuint							m_vboID{};
	GLuint							m_eboID{};
	GLuint							m_shaderID{};
};