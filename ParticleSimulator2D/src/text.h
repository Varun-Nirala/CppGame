#pragma once

#include <string>
#include <map>
#include <vector>
#include <glad/glad.h>

#define GLM_FORCE_SILENT_WARNINGS       // to silent warnings
#include <glm/glm.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

class TextDisplay
{
	struct GlyphChar
	{
		GLuint			textureID{};		// Glyph texture ID
		glm::ivec2		size{};				// Size 
		glm::ivec2		bearing;			// Offset from baseline to left/top of Glyph
		FT_Pos			advance{};			// Offset to advance to next Glyph
	};

	struct TextDesc
	{
		std::string		text;
		GLfloat			posX;
		GLfloat			posY;
		GLfloat			scale;
		glm::vec4		color;

		TextDesc(const std::string& text, GLfloat posX, GLfloat posY, GLfloat scale, const glm::vec4& color)
		{
			this->text = text;
			this->posX = posX;
			this->posY = posY;
			this->scale = scale;
			this->color = color;
		}
	};
public:
	~TextDisplay() { release(); }
	TextDisplay() = default;

	bool prepareShader(const std::string &vertexShaderFile = R"(./resources/Shaders/text.vert)", const std::string& fragmentShaderFile = R"(./resources/Shaders/text.frag)");
	bool loadFont(const std::string& filepath = R"(./resources/Fonts/Arial/arial.ttf)", const int fontSize = 20);

	void addTextToRender(const std::string &text, GLfloat posX, GLfloat posY, GLfloat scale, const glm::vec4 &color);
	void setTextToRender(const std::string& text, GLfloat posX, GLfloat posY, GLfloat scale, const glm::vec4 &color);

	void render();
private:
	void release();

public:
	std::map<char, GlyphChar>		m_charMap;
	GLuint							m_vao{};
	GLuint							m_vbo{};
	GLuint							m_shaderProgram{};

	std::vector<TextDesc>			m_text;
};