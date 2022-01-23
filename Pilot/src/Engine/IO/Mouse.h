#ifndef __MOUSE_H__
#define __MOUSE_H__

#include <GLFW\glfw3.h>

namespace nsEngine
{
#define MAX_BUTTON	3		// Only supporting 3 button of mouse namely left, right and middle

	class Mouse
	{
		// DELETED Funtion
		Mouse(const Mouse &) = delete;
		Mouse(const Mouse &&) = delete;
		Mouse& operator=(const Mouse &) = delete;

		public:
			static Mouse* getInstance();

			// To be called whenever mouse position move in the OpenGL window
			static void MousePositionCB(GLFWwindow *pWindow, double x, double y);

			// To be called whenever mouse button state is changed like pressed in the OpenGL window
			static void MouseButtonCB(GLFWwindow *pWindow, int button, int action, int mods);

			bool SetCustomMousePositionCB(void *funPtr);		// To setup custom callback
			bool SetCustomMouseButtonCB(void *funPtr);			// To setup custom callback

			bool ButtonDown(int button);
			bool ButtonUp(int button);
			bool Button(int button);

			double GetPosX();
			double GetPosY();

		private:
			Mouse() = default;

			static Mouse			*m_pInstance;

			static bool		m_button[MAX_BUTTON];			// click of button
			static bool		m_buttonUp[MAX_BUTTON];			// releasing of button after
			static bool		m_buttonDown[MAX_BUTTON];		// pressing of button after 

			static double	m_dPosX;
			static double	m_dPosY;

			// Function pointers
			static void(*FP_MousePositionCB)(GLFWwindow *, double, double);
			static void(*FP_MouseButtonCB)(GLFWwindow *, int, int, int);
	};
}
#endif