#include "text.h"
#include "Common/constants.h"
#include "Common/logger.h"
#include "shaderProgram.h"
#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

bool TextDisplay::prepareShader(const std::string& vertexShaderFile, const std::string& fragmentShaderFile)
{
	m_shaderProgram = ShaderProgram::createShader();
	if (!ShaderProgram::attachShader(vertexShaderFile, SHADER_TYPE::VERT, m_shaderProgram))
	{
		ns_Util::Logger::LOG_ERROR("Vertex Shader compilation failed.");
		return false;
	}

	if (!ShaderProgram::attachShader(fragmentShaderFile, SHADER_TYPE::FRAG, m_shaderProgram))
	{
		ns_Util::Logger::LOG_ERROR("Fragment Shader compilation failed.");
		return false;
	}

	if (!ShaderProgram::linkShader(m_shaderProgram))
	{
		ns_Util::Logger::LOG_ERROR("Shader linking failed.");
		return false;
	}
	return true;
}

bool TextDisplay::loadFont(const std::string& filepath, const int fontSize)
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft))
	{
		std::cout << "Error: FREETYPE: Could not init FreeType Library." << std::endl;
		return false;
	}

	FT_Face face;
	if (FT_New_Face(ft, filepath.c_str(), 0, &face))
	{
		std::cout << "Error: FREETYPE: Could not load font." << std::endl;
		return false;
	}

	FT_Set_Pixel_Sizes(face, 0, fontSize);

	if (FT_Load_Char(face, 'X', FT_LOAD_RENDER))
	{
		std::cout << "Error: FREETYPE: Could not load Glyph." << std::endl;
		FT_Done_Face(face);
		FT_Done_FreeType(ft);
		return false;
	}

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);	//Disable byte-alignment restriction

	for (GLubyte c = 0; c < 128; ++c)
	{
		// Load Character
		if (FT_Load_Char(face, c, FT_LOAD_RENDER))
		{
			std::cout << "Error: FREETYPE: Could not load Glyph. Char :" << char(c) << std::endl;
			FT_Done_Face(face);
			FT_Done_FreeType(ft);
			return false;
		}

		// Generate Texture
		GLuint texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RED,
			face->glyph->bitmap.width,
			face->glyph->bitmap.rows,
			0,
			GL_RED,
			GL_UNSIGNED_BYTE,
			face->glyph->bitmap.buffer);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


		// now store character for later use
		GlyphChar glyphChar = {
			texture,
			glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
			glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
			face->glyph->advance.x
		};
		m_charMap[c] = glyphChar;
	}
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	FT_Done_Face(face);
	FT_Done_FreeType(ft);

	glGenVertexArrays(1, &m_vao);
	glGenBuffers(1, &m_vbo);

	glBindVertexArray(m_vao);
	glBindBuffer(GL_ARRAY_BUFFER, m_vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);	// The 2D quad requires 6 vertices of 4 floats each

	glEnableVertexAttribArray(0);

	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

    return true;
}

void TextDisplay::addTextToRender(const std::string& text, GLfloat posX, GLfloat posY, GLfloat scale, const glm::vec4& color)
{
	m_text.push_back(TextDesc{ text, posX, posY, scale, color });
}

void TextDisplay::setTextToRender(const std::string& text, GLfloat posX, GLfloat posY, GLfloat scale, const glm::vec4& color)
{
	m_text.clear();
	addTextToRender(text, posX, posY, scale, color);
}

void TextDisplay::render()
{
	ShaderProgram::activate(m_shaderProgram);
	glm::mat4 projection = glm::mat4{ 1.0f };
	projection = glm::ortho(0.0f, (GLfloat)WIDTH, (GLfloat)HEIGHT, 0.0f, -1.0f, 1.0f);
	ShaderProgram::setUniform_fm(m_shaderProgram, "projection", projection);
	for (size_t i = 0; i < m_text.size(); ++i)
	{
		ShaderProgram::setUniform_fv(m_shaderProgram, "textColor", m_text[i].color);
		glActiveTexture(GL_TEXTURE0);
		glBindVertexArray(m_vao);

		for (char ch : m_text[i].text)
		{
			GlyphChar& gCh = m_charMap[ch];

			GLfloat posX = m_text[i].posX + gCh.bearing.x * m_text[i].scale;
			GLfloat posY = m_text[i].posY - (gCh.size.y - gCh.bearing.y) * m_text[i].scale;

			GLfloat w = gCh.size.x * m_text[i].scale;
			GLfloat h = gCh.size.y * m_text[i].scale;

			// Update VBO for each character
			GLfloat vertices[6][4] = {
				{ posX,     posY + h, 0.0f, 0.0f},
				{ posX,     posY    , 0.0f, 1.0f},
				{ posX + w, posY,     1.0f, 1.0f},

				{ posX,     posY + h, 0.0f, 0.0f},
				{ posX + w, posY,     1.0f, 1.0f},
				{ posX + w, posY + h, 1.0f, 0.0f},
			};

			glBindTexture(GL_TEXTURE_2D, gCh.textureID);

			glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			glDrawArrays(GL_TRIANGLES, 0, 6);

			// Advance cursors for next glyph (note that advance is number of 1/64 pixels)
			m_text[i].posX += (gCh.advance >> 6) * m_text[i].scale;	// bitshift by 6 to get value in pixels (2^6 = 64)
		}
		glBindVertexArray(0);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
	m_text.clear();
}

void TextDisplay::release()
{
	for (auto& p : m_charMap)
	{
		glDeleteTextures(1, &p.second.textureID);
	}
	m_charMap.clear();

	glDeleteVertexArrays(1, &m_vao);
	glDeleteBuffers(1, &m_vbo);

	m_vao = m_vbo = 0;
}
