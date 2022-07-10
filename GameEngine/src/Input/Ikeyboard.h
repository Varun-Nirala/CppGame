#pragma once

#include <functional>
#include <algorithm>
#include <vector>

struct KeyButton
{
	struct Action
	{
		bool		up{ true };
		bool		down{ false };
		bool		held{ false };
	};

	int			keycode{};
	int			scancode{};
	int			mods{};

	Action		action;
};

class DisplayWindow;

class Ikeyboard
{
	using OnKeyInput_CB = std::function<void(const KeyButton&)>;

public:
	virtual ~Ikeyboard() = default;

	Ikeyboard(DisplayWindow* pWindow)
		: m_pWindow(pWindow)
	{}

	virtual void registerCallbacks() {};

	void registerOnKeyInputCB(OnKeyInput_CB cb)
	{
		m_keyInputCallbacks.push_back(cb);
	}

	void newKeyEvent(KeyButton keybutton)
	{
		std::for_each(m_keyInputCallbacks.begin(), m_keyInputCallbacks.end(), [&keybutton](OnKeyInput_CB& func) -> void
			{
				func(keybutton);
			});
	}

protected:
	std::vector<OnKeyInput_CB>		m_keyInputCallbacks;
	DisplayWindow					*m_pWindow{};
};

extern const int KEY_UNKNOWN;
extern const int KEY_SPACE;
extern const int KEY_APOSTROPHE;
extern const int KEY_COMMA;
extern const int KEY_MINUS;
extern const int KEY_PERIOD;
extern const int KEY_SLASH;
extern const int KEY_0;
extern const int KEY_1;
extern const int KEY_2;
extern const int KEY_3;
extern const int KEY_4;
extern const int KEY_5;
extern const int KEY_6;
extern const int KEY_7;
extern const int KEY_8;
extern const int KEY_9;
extern const int KEY_SEMICOLON;
extern const int KEY_EQUAL;
extern const int KEY_A;
extern const int KEY_B;
extern const int KEY_C;
extern const int KEY_D;
extern const int KEY_E;
extern const int KEY_F;
extern const int KEY_G;
extern const int KEY_H;
extern const int KEY_I;
extern const int KEY_J;
extern const int KEY_K;
extern const int KEY_L;
extern const int KEY_M;
extern const int KEY_N;
extern const int KEY_O;
extern const int KEY_P;
extern const int KEY_Q;
extern const int KEY_R;
extern const int KEY_S;
extern const int KEY_T;
extern const int KEY_U;
extern const int KEY_V;
extern const int KEY_W;
extern const int KEY_X;
extern const int KEY_Y;
extern const int KEY_Z;
extern const int KEY_LEFT_BRACKET;
extern const int KEY_BACKSLASH;
extern const int KEY_RIGHT_BRACKET;
extern const int KEY_GRAVE_ACCENT;
extern const int KEY_WORLD_1;
extern const int KEY_WORLD_2;
extern const int KEY_ESCAPE;
extern const int KEY_ENTER;
extern const int KEY_TAB;
extern const int KEY_BACKSPACE;
extern const int KEY_INSERT;
extern const int KEY_DELETE;
extern const int KEY_RIGHT;
extern const int KEY_LEFT;
extern const int KEY_DOWN;
extern const int KEY_UP;
extern const int KEY_PAGE_UP;
extern const int KEY_PAGE_DOWN;
extern const int KEY_HOME;
extern const int KEY_END;
extern const int KEY_CAPS_LOCK;
extern const int KEY_SCROLL_LOCK;
extern const int KEY_NUM_LOCK;
extern const int KEY_PRINT_SCREEN;
extern const int KEY_PAUSE;
extern const int KEY_F1;
extern const int KEY_F2;
extern const int KEY_F3;
extern const int KEY_F4;
extern const int KEY_F5;
extern const int KEY_F6;
extern const int KEY_F7;
extern const int KEY_F8;
extern const int KEY_F9;
extern const int KEY_F10;
extern const int KEY_F11;
extern const int KEY_F12;
extern const int KEY_F13;
extern const int KEY_F14;
extern const int KEY_F15;
extern const int KEY_F16;
extern const int KEY_F17;
extern const int KEY_F18;
extern const int KEY_F19;
extern const int KEY_F20;
extern const int KEY_F21;
extern const int KEY_F22;
extern const int KEY_F23;
extern const int KEY_F24;
extern const int KEY_F25;
extern const int KEY_KP_0;
extern const int KEY_KP_1;
extern const int KEY_KP_2;
extern const int KEY_KP_3;
extern const int KEY_KP_4;
extern const int KEY_KP_5;
extern const int KEY_KP_6;
extern const int KEY_KP_7;
extern const int KEY_KP_8;
extern const int KEY_KP_9;
extern const int KEY_KP_DECIMAL;
extern const int KEY_KP_DIVIDE;
extern const int KEY_KP_MULTIPLY;
extern const int KEY_KP_SUBTRACT;
extern const int KEY_KP_ADD;
extern const int KEY_KP_ENTER;
extern const int KEY_KP_EQUAL;
extern const int KEY_LEFT_SHIFT;
extern const int KEY_LEFT_CONTROL;
extern const int KEY_LEFT_ALT;
extern const int KEY_LEFT_SUPER;
extern const int KEY_RIGHT_SHIFT;
extern const int KEY_RIGHT_CONTROL;
extern const int KEY_RIGHT_ALT;
extern const int KEY_RIGHT_SUPER;
extern const int KEY_MENU;
extern const int KEY_LAST;
extern const int MOD_SHIFT;
extern const int MOD_CONTROL;
extern const int MOD_ALT;
extern const int MOD_SUPER;
extern const int MOD_CAPS_LOCK;
extern const int MOD_NUM_LOCK;

/*
#define KEY_UNKNOWN           GLFW_KEY_UNKNOWN
#define KEY_SPACE             GLFW_KEY_SPACE
#define KEY_APOSTROPHE        GLFW_KEY_APOSTROPHE
#define KEY_COMMA             GLFW_KEY_COMMA
#define KEY_MINUS             GLFW_KEY_MINUS
#define KEY_PERIOD            GLFW_KEY_PERIOD
#define KEY_SLASH             GLFW_KEY_SLASH
#define KEY_0                 GLFW_KEY_0
#define KEY_1                 GLFW_KEY_1
#define KEY_2                 GLFW_KEY_2
#define KEY_3                 GLFW_KEY_3
#define KEY_4                 GLFW_KEY_4
#define KEY_5                 GLFW_KEY_5
#define KEY_6                 GLFW_KEY_6
#define KEY_7                 GLFW_KEY_7
#define KEY_8                 GLFW_KEY_8
#define KEY_9                 GLFW_KEY_9
#define KEY_SEMICOLON         GLFW_KEY_SEMICOLON
#define KEY_EQUAL             GLFW_KEY_EQUAL
#define KEY_A                 GLFW_KEY_A
#define KEY_B                 GLFW_KEY_B
#define KEY_C                 GLFW_KEY_C
#define KEY_D                 GLFW_KEY_D
#define KEY_E                 GLFW_KEY_E
#define KEY_F                 GLFW_KEY_F
#define KEY_G                 GLFW_KEY_G
#define KEY_H                 GLFW_KEY_H
#define KEY_I                 GLFW_KEY_I
#define KEY_J                 GLFW_KEY_J
#define KEY_K                 GLFW_KEY_K
#define KEY_L                 GLFW_KEY_L
#define KEY_M                 GLFW_KEY_M
#define KEY_N                 GLFW_KEY_N
#define KEY_O                 GLFW_KEY_O
#define KEY_P                 GLFW_KEY_P
#define KEY_Q                 GLFW_KEY_Q
#define KEY_R                 GLFW_KEY_R
#define KEY_S                 GLFW_KEY_S
#define KEY_T                 GLFW_KEY_T
#define KEY_U                 GLFW_KEY_U
#define KEY_V                 GLFW_KEY_V
#define KEY_W                 GLFW_KEY_W
#define KEY_X                 GLFW_KEY_X
#define KEY_Y                 GLFW_KEY_Y
#define KEY_Z                 GLFW_KEY_Z
#define KEY_LEFT_BRACKET      GLFW_KEY_LEFT_BRACKET
#define KEY_BACKSLASH         GLFW_KEY_BACKSLASH
#define KEY_RIGHT_BRACKET     GLFW_KEY_RIGHT_BRACKET
#define KEY_GRAVE_ACCENT      GLFW_KEY_GRAVE_ACCENT
#define KEY_WORLD_1           GLFW_KEY_WORLD_1
#define KEY_WORLD_2           GLFW_KEY_WORLD_2
#define KEY_ESCAPE            GLFW_KEY_ESCAPE
#define KEY_ENTER             GLFW_KEY_ENTER
#define KEY_TAB               GLFW_KEY_TAB
#define KEY_BACKSPACE         GLFW_KEY_BACKSPACE
#define KEY_INSERT            GLFW_KEY_INSERT
#define KEY_DELETE            GLFW_KEY_DELETE
#define KEY_RIGHT             GLFW_KEY_RIGHT
#define KEY_LEFT              GLFW_KEY_LEFT
#define KEY_DOWN              GLFW_KEY_DOWN
#define KEY_UP                GLFW_KEY_UP
#define KEY_PAGE_UP           GLFW_KEY_PAGE_UP
#define KEY_PAGE_DOWN         GLFW_KEY_PAGE_DOWN
#define KEY_HOME              GLFW_KEY_HOME
#define KEY_END               GLFW_KEY_END
#define KEY_CAPS_LOCK         GLFW_KEY_CAPS_LOCK
#define KEY_SCROLL_LOCK       GLFW_KEY_SCROLL_LOCK
#define KEY_NUM_LOCK          GLFW_KEY_NUM_LOCK
#define KEY_PRINT_SCREEN      GLFW_KEY_PRINT_SCREEN
#define KEY_PAUSE             GLFW_KEY_PAUSE
#define KEY_F1                GLFW_KEY_F1
#define KEY_F2                GLFW_KEY_F2
#define KEY_F3                GLFW_KEY_F3
#define KEY_F4                GLFW_KEY_F4
#define KEY_F5                GLFW_KEY_F5
#define KEY_F6                GLFW_KEY_F6
#define KEY_F7                GLFW_KEY_F7
#define KEY_F8                GLFW_KEY_F8
#define KEY_F9                GLFW_KEY_F9
#define KEY_F10               GLFW_KEY_F10
#define KEY_F11               GLFW_KEY_F11
#define KEY_F12               GLFW_KEY_F12
#define KEY_F13               GLFW_KEY_F13
#define KEY_F14               GLFW_KEY_F14
#define KEY_F15               GLFW_KEY_F15
#define KEY_F16               GLFW_KEY_F16
#define KEY_F17               GLFW_KEY_F17
#define KEY_F18               GLFW_KEY_F18
#define KEY_F19               GLFW_KEY_F19
#define KEY_F20               GLFW_KEY_F20
#define KEY_F21               GLFW_KEY_F21
#define KEY_F22               GLFW_KEY_F22
#define KEY_F23               GLFW_KEY_F23
#define KEY_F24               GLFW_KEY_F24
#define KEY_F25               GLFW_KEY_F25
#define KEY_KP_0              GLFW_KEY_KP_0
#define KEY_KP_1              GLFW_KEY_KP_1
#define KEY_KP_2              GLFW_KEY_KP_2
#define KEY_KP_3              GLFW_KEY_KP_3
#define KEY_KP_4              GLFW_KEY_KP_4
#define KEY_KP_5              GLFW_KEY_KP_5
#define KEY_KP_6              GLFW_KEY_KP_6
#define KEY_KP_7              GLFW_KEY_KP_7
#define KEY_KP_8              GLFW_KEY_KP_8
#define KEY_KP_9              GLFW_KEY_KP_9
#define KEY_KP_DECIMAL        GLFW_KEY_KP_DECIMAL
#define KEY_KP_DIVIDE         GLFW_KEY_KP_DIVIDE
#define KEY_KP_MULTIPLY       GLFW_KEY_KP_MULTIPLY
#define KEY_KP_SUBTRACT       GLFW_KEY_KP_SUBTRACT
#define KEY_KP_ADD            GLFW_KEY_KP_ADD
#define KEY_KP_ENTER          GLFW_KEY_KP_ENTER
#define KEY_KP_EQUAL          GLFW_KEY_KP_EQUAL
#define KEY_LEFT_SHIFT        GLFW_KEY_LEFT_SHIFT
#define KEY_LEFT_CONTROL      GLFW_KEY_LEFT_CONTROL
#define KEY_LEFT_ALT          GLFW_KEY_LEFT_ALT
#define KEY_LEFT_SUPER        GLFW_KEY_LEFT_SUPER
#define KEY_RIGHT_SHIFT       GLFW_KEY_RIGHT_SHIFT
#define KEY_RIGHT_CONTROL     GLFW_KEY_RIGHT_CONTROL
#define KEY_RIGHT_ALT         GLFW_KEY_RIGHT_ALT
#define KEY_RIGHT_SUPER       GLFW_KEY_RIGHT_SUPER
#define KEY_MENU              GLFW_KEY_MENU
#define KEY_LAST              GLFW_KEY_LAST
#define MOD_SHIFT             GLFW_MOD_SHIFT
#define MOD_CONTROL           GLFW_MOD_CONTROL
#define MOD_ALT               GLFW_MOD_ALT
#define MOD_SUPER             GLFW_MOD_SUPER
#define MOD_CAPS_LOCK         GLFW_MOD_CAPS_LOCK
#define MOD_NUM_LOCK          GLFW_MOD_NUM_LOCK





#define KEY_UNKNOWN           SDLK_UNKNOWN
#define KEY_SPACE             SDLK_SPACE
#define KEY_APOSTROPHE        SDLK_QUOTE
#define KEY_COMMA             SDLK_COMMA
#define KEY_MINUS             SDLK_MINUS
#define KEY_PERIOD            SDLK_PERIOD
#define KEY_SLASH             SDLK_SLASH
#define KEY_0                 SDLK_0
#define KEY_1                 SDLK_1
#define KEY_2                 SDLK_2
#define KEY_3                 SDLK_3
#define KEY_4                 SDLK_4
#define KEY_5                 SDLK_5
#define KEY_6                 SDLK_6
#define KEY_7                 SDLK_7
#define KEY_8                 SDLK_8
#define KEY_9                 SDLK_9
#define KEY_SEMICOLON         SDLK_SEMICOLON
#define KEY_EQUAL             SDLK_EQUALS
#define KEY_A                 SDLK_a
#define KEY_B                 SDLK_b
#define KEY_C                 SDLK_c
#define KEY_D                 SDLK_d
#define KEY_E                 SDLK_e
#define KEY_F                 SDLK_f
#define KEY_G                 SDLK_g
#define KEY_H                 SDLK_h
#define KEY_I                 SDLK_i
#define KEY_J                 SDLK_j
#define KEY_K                 SDLK_k
#define KEY_L                 SDLK_l
#define KEY_M                 SDLK_m
#define KEY_N                 SDLK_n
#define KEY_O                 SDLK_o
#define KEY_P                 SDLK_p
#define KEY_Q                 SDLK_q
#define KEY_R                 SDLK_r
#define KEY_S                 SDLK_s
#define KEY_T                 SDLK_t
#define KEY_U                 SDLK_u
#define KEY_V                 SDLK_v
#define KEY_W                 SDLK_w
#define KEY_X                 SDLK_x
#define KEY_Y                 SDLK_y
#define KEY_Z                 SDLK_z
#define KEY_LEFT_BRACKET      SDLK_LEFTBRACKET
#define KEY_BACKSLASH         SDLK_BACKSLASH
#define KEY_RIGHT_BRACKET     SDLK_RIGHTBRACKET
#define KEY_GRAVE_ACCENT      SDLK_BACKQUOTE
#define KEY_WORLD_1           [EMPTY]
#define KEY_WORLD_2           [EMPTY]
#define KEY_ESCAPE            SDLK_ESCAPE
#define KEY_ENTER             SDLK_RETURN
#define KEY_TAB               SDLK_TAB
#define KEY_BACKSPACE         SDLK_BACKSPACE
#define KEY_INSERT            SDLK_INSERT
#define KEY_DELETE            SDLK_DELETE
#define KEY_RIGHT             SDLK_RIGHT
#define KEY_LEFT              SDLK_LEFT
#define KEY_DOWN              SDLK_DOWN
#define KEY_UP                SDLK_UP
#define KEY_PAGE_UP           SDLK_PAGEUP
#define KEY_PAGE_DOWN         SDLK_PAGEDOWN
#define KEY_HOME              SDLK_HOME
#define KEY_END               SDLK_END
#define KEY_CAPS_LOCK         SDLK_CAPSLOCK
#define KEY_SCROLL_LOCK       SDLK_SCROLLLOCK
#define KEY_NUM_LOCK          SDLK_NUMLOCKCLEAR
#define KEY_PRINT_SCREEN      SDLK_PRINTSCREEN
#define KEY_PAUSE             SDLK_PAUSE
#define KEY_F1                SDLK_F1
#define KEY_F2                SDLK_F2
#define KEY_F3                SDLK_F3
#define KEY_F4                SDLK_F4
#define KEY_F5                SDLK_F5
#define KEY_F6                SDLK_F6
#define KEY_F7                SDLK_F7
#define KEY_F8                SDLK_F8
#define KEY_F9                SDLK_F9
#define KEY_F10               SDLK_F10
#define KEY_F11               SDLK_F11
#define KEY_F12               SDLK_F12
#define KEY_F13               SDLK_F13
#define KEY_F14               SDLK_F14
#define KEY_F15               SDLK_F15
#define KEY_F16               SDLK_F16
#define KEY_F17               SDLK_F17
#define KEY_F18               SDLK_F18
#define KEY_F19               SDLK_F19
#define KEY_F20               SDLK_F20
#define KEY_F21               SDLK_F21
#define KEY_F22               SDLK_F22
#define KEY_F23               SDLK_F23
#define KEY_F24               SDLK_F24
#define KEY_F25               [EMPTY]
#define KEY_KP_0              SDLK_KP_0
#define KEY_KP_1              SDLK_KP_1
#define KEY_KP_2              SDLK_KP_2
#define KEY_KP_3              SDLK_KP_3
#define KEY_KP_4              SDLK_KP_4
#define KEY_KP_5              SDLK_KP_5
#define KEY_KP_6              SDLK_KP_6
#define KEY_KP_7              SDLK_KP_7
#define KEY_KP_8              SDLK_KP_8
#define KEY_KP_9              SDLK_KP_9
#define KEY_KP_DECIMAL        SDLK_KP_PERIOD
#define KEY_KP_DIVIDE         SDLK_KP_DIVIDE
#define KEY_KP_MULTIPLY       SDLK_KP_MULTIPLY
#define KEY_KP_SUBTRACT       SDLK_KP_MINUS
#define KEY_KP_ADD            SDLK_KP_PLUS
#define KEY_KP_ENTER          SDLK_KP_ENTER
#define KEY_KP_EQUAL          SDLK_KP_EQUALS
#define KEY_LEFT_SHIFT        SDLK_LSHIFT
#define KEY_LEFT_CONTROL      SDLK_LCTRL
#define KEY_LEFT_ALT          SDLK_LALT
#define KEY_LEFT_SUPER        SDLK_LGUI
#define KEY_RIGHT_SHIFT       SDLK_RSHIFT
#define KEY_RIGHT_CONTROL     SDLK_RCTRL
#define KEY_RIGHT_ALT         SDLK_RALT
#define KEY_RIGHT_SUPER       SDLK_RGUI
#define KEY_MENU              SDLK_MENU
#define KEY_LAST              [EMPTY]
#define MOD_SHIFT             KMOD_SHIFT
#define MOD_CONTROL           KMOD_CTRL
#define MOD_ALT               KMOD_ALT
#define MOD_SUPER             KMOD_GUI
#define MOD_CAPS_LOCK         KMOD_CAPS
#define MOD_NUM_LOCK          KMOD_NUM
*/