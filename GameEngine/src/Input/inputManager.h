#pragma once

#include "Ikeyboard.h"
#include "Imouse.h"

class DisplayWindow;

class InputManager
{
public:
	~InputManager() { release(); }
	InputManager(bool bInitKeyboard, bool bInitMouse);

	bool init(DisplayWindow *pWindow);

	bool keyboardInitialized() const { return m_pKeyboard != nullptr; }
	bool mouseInitialized() const { return m_pMouse != nullptr; }

	const Imouse* mouse() const { return m_pMouse; }
	Imouse* mouse() { return m_pMouse; }

	const Ikeyboard* keyboard() const { return m_pKeyboard; }
	Ikeyboard* keyboard() { return m_pKeyboard; }

	void release();

	void print(const std::string& prefix = {}) const;
private:
	Imouse* createMouse(DisplayWindow* pWindow);
	Ikeyboard* createKeyboard(DisplayWindow* pWindow);

private:
	Imouse			*m_pMouse{};
	Ikeyboard		*m_pKeyboard{};
	bool			m_bInitKeyboard;
	bool			m_bInitMouse;
};