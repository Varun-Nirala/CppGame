#ifndef __ENGINE_H__
#define __ENGINE_H__

#include <GLFW\glfw3.h>

namespace nsEngine
{
	class Engine
	{
		public:
			Engine();
			Engine(int w, int h);
			~Engine();

			//Mouse Controller
			bool SetMousePositionCB(void *funPtr);
			bool SetMouseButtonCB(void *funPtr);

			bool Initialize(char *windowTitle);

			void Update();
			void BeginRender();
			void EndRender();

			int GetWidth() const;
			int GetHeight() const;

			bool IsWindowClosed();

		private:
			GLFWwindow		*m_pWindow;
			int				m_iWidth;
			int				m_iHeight;
	};
}
#endif