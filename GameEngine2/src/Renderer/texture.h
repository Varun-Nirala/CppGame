#pragma once

#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

#include <stb_image.h>

#include <string>

#include "Common/logger.h"

class Texture
{
public:
	~Texture();
	Texture(const std::string& filepath);

	void bind() const { glBindTexture(GL_TEXTURE_2D, m_textureID); }
	void unBind() const { glBindTexture(GL_TEXTURE_2D, 0); }

	GLint getWidth() const { return m_width; }
	GLint getHeight() const { return m_height; }

private:
	std::string			m_filepath;
	GLuint				m_textureID{};
	GLint				m_width{};
	GLint				m_height{};
};