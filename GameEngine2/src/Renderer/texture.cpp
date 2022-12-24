#include "texture.h"

Texture::~Texture()
{
	if (m_textureID)
	{
		glDeleteTextures(1, &m_textureID);
		m_textureID = 0;
	}
}

Texture::Texture(const std::string& filepath)
	: m_filepath(filepath)
{
	glGenTextures(1, &m_textureID);

	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	unsigned char* imgData{};
	
	int numOfChannels{};

	stbi_set_flip_vertically_on_load(true);

	imgData = stbi_load(m_filepath.c_str(), &m_width, &m_height, &numOfChannels, 0);

	if (!imgData)
	{
		ns_Util::Logger::LOG_ERROR("Failed to load image : ", m_filepath, '\n');
		assert(false);
		return;
	}

	if (numOfChannels == 4)
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGBA,
			m_width,
			m_height,
			0,
			GL_RGBA,
			GL_UNSIGNED_BYTE,
			imgData
		);
	}
	else if (numOfChannels == 3)
	{
		glTexImage2D(
			GL_TEXTURE_2D,
			0,
			GL_RGB,
			m_width,
			m_height,
			0,
			GL_RGB,
			GL_UNSIGNED_BYTE,
			imgData
		);
	}
	else
	{
		ns_Util::Logger::LOG_ERROR("Unkown number of channels!\n");
		assert(false);
	}

	stbi_image_free(imgData);
}