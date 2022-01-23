#include "Texture.h"
#include <soil.h>
#include <iostream>

using namespace nsGraphics;
using namespace std;

Texture::Texture()
	: m_iID(-1)
	, m_iWidth(-1)
	, m_iHeight(-1)
{}

Texture::Texture(int _id)
	: m_iID(_id)
{
	if (!LoadTextureParams())
	{
		cout << __LINE__ << " ::Error: Loading texture with ID = " << m_iID << endl;
	}
}

Texture::Texture(string &path)
{
	m_iID = SOIL_load_OGL_texture(path.c_str(), SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MULTIPLY_ALPHA | SOIL_FLAG_INVERT_Y);

	if (!LoadTextureParams())
	{
		cout << __LINE__ << " ::Error: Loading texture with ID = " << m_iID << endl;
	}
}

int Texture::GetHeight() const
{
	return m_iHeight;
}

int Texture::GetWidth() const
{
	return m_iWidth;
}

int Texture::GetID() const
{
	return m_iID;
}

bool Texture::LoadTextureParams()
{
	if (m_iID > 0)
	{
		int mipLevel = 0;
		glBindTexture(GL_TEXTURE_2D, m_iID);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_WIDTH, &m_iWidth);
		glGetTexLevelParameteriv(GL_TEXTURE_2D, mipLevel, GL_TEXTURE_HEIGHT, &m_iHeight);
		return true;
	}
	return false;
}