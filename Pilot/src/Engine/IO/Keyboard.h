#ifndef __KEYBOARD_H__
#define __KEYBOARD_H__

#include <GLFW\glfw3.h>

namespace nsEngine
{
	class Keyboard
	{
		// DELETED Funtion
		Keyboard(const Keyboard &) = delete;
		Keyboard(const Keyboard &&) = delete;
		Keyboard& operator=(const Keyboard &) = delete;

		public:
			static Keyboard* getInstance();

			static void KeyboardCB(GLFWwindow *pWindow, int key, int scanCode, int action, int mods);

			bool SetCustomKeyboardCB(void *funPtr);	// To setup custom callback for keyboard

			bool KeyDown(int key);
			bool KeyUp(int key);
			bool Key(int key);

		private:
			Keyboard() = default;

			static Keyboard		*m_pInstance;
			static bool			m_keysDown[GLFW_KEY_LAST];	// Key is down
			static bool			m_keysUp[GLFW_KEY_LAST];	// Key is released
			static bool			m_keys[GLFW_KEY_LAST];		// Key state

			// Function pointer
			static void(*FP_KeyboardCB)(GLFWwindow *, int, int, int, int);
	};
}

#endif //__KEYBOARD_H__