#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <GLFW\glfw3.h>
#include <string>

namespace nsGraphics
{
	class Texture
	{
		public:
			Texture();
			Texture(int _id);
			Texture(std::string &path);

			int GetWidth() const;
			int GetHeight() const;
			int GetID() const;

		private:
			bool LoadTextureParams();

		private:
			int m_iID;
			int m_iWidth;
			int m_iHeight;
	};
}
#endif