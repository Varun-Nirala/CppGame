#include "Common/constants.h"

#include <GLFW/glfw3.h>
#include "Ikeyboard.h"

#if defined(USE_GLFW_WINDOW)
	// Mouse mapping
	const int MOUSE_BUTTON_LEFT           = GLFW_MOUSE_BUTTON_LEFT;
	const int MOUSE_BUTTON_RIGHT          = GLFW_MOUSE_BUTTON_RIGHT;
	const int MOUSE_BUTTON_MIDDLE         = GLFW_MOUSE_BUTTON_MIDDLE;
	const int MOUSE_BUTTON_1              = GLFW_MOUSE_BUTTON_1;
	const int MOUSE_BUTTON_2              = GLFW_MOUSE_BUTTON_2;
	const int MOUSE_BUTTON_3              = GLFW_MOUSE_BUTTON_3;
	const int MOUSE_BUTTON_4              = GLFW_MOUSE_BUTTON_4;
	const int MOUSE_BUTTON_5              = GLFW_MOUSE_BUTTON_5;
	const int MOUSE_BUTTON_6              = GLFW_MOUSE_BUTTON_6;
	const int MOUSE_BUTTON_7              = GLFW_MOUSE_BUTTON_7;
	const int MOUSE_BUTTON_8              = GLFW_MOUSE_BUTTON_8;

	// Keyboard mapping
	const int KEY_UNKNOWN                 = GLFW_KEY_UNKNOWN;
	const int KEY_SPACE                   = GLFW_KEY_SPACE;
	const int KEY_APOSTROPHE              = GLFW_KEY_APOSTROPHE;
	const int KEY_COMMA                   = GLFW_KEY_COMMA;
	const int KEY_MINUS                   = GLFW_KEY_MINUS;
	const int KEY_PERIOD                  = GLFW_KEY_PERIOD;
	const int KEY_SLASH                   = GLFW_KEY_SLASH;
	const int KEY_0                       = GLFW_KEY_0;
	const int KEY_1                       = GLFW_KEY_1;
	const int KEY_2                       = GLFW_KEY_2;
	const int KEY_3                       = GLFW_KEY_3;
	const int KEY_4                       = GLFW_KEY_4;
	const int KEY_5                       = GLFW_KEY_5;
	const int KEY_6                       = GLFW_KEY_6;
	const int KEY_7                       = GLFW_KEY_7;
	const int KEY_8                       = GLFW_KEY_8;
	const int KEY_9                       = GLFW_KEY_9;
	const int KEY_SEMICOLON               = GLFW_KEY_SEMICOLON;
	const int KEY_EQUAL                   = GLFW_KEY_EQUAL;
	const int KEY_A                       = GLFW_KEY_A;
	const int KEY_B                       = GLFW_KEY_B;
	const int KEY_C                       = GLFW_KEY_C;
	const int KEY_D                       = GLFW_KEY_D;
	const int KEY_E                       = GLFW_KEY_E;
	const int KEY_F                       = GLFW_KEY_F;
	const int KEY_G                       = GLFW_KEY_G;
	const int KEY_H                       = GLFW_KEY_H;
	const int KEY_I                       = GLFW_KEY_I;
	const int KEY_J                       = GLFW_KEY_J;
	const int KEY_K                       = GLFW_KEY_K;
	const int KEY_L                       = GLFW_KEY_L;
	const int KEY_M                       = GLFW_KEY_M;
	const int KEY_N                       = GLFW_KEY_N;
	const int KEY_O                       = GLFW_KEY_O;
	const int KEY_P                       = GLFW_KEY_P;
	const int KEY_Q                       = GLFW_KEY_Q;
	const int KEY_R                       = GLFW_KEY_R;
	const int KEY_S                       = GLFW_KEY_S;
	const int KEY_T                       = GLFW_KEY_T;
	const int KEY_U                       = GLFW_KEY_U;
	const int KEY_V                       = GLFW_KEY_V;
	const int KEY_W                       = GLFW_KEY_W;
	const int KEY_X                       = GLFW_KEY_X;
	const int KEY_Y                       = GLFW_KEY_Y;
	const int KEY_Z                       = GLFW_KEY_Z;
	const int KEY_LEFT_BRACKET            = GLFW_KEY_LEFT_BRACKET;
	const int KEY_BACKSLASH               = GLFW_KEY_BACKSLASH;
	const int KEY_RIGHT_BRACKET           = GLFW_KEY_RIGHT_BRACKET;
	const int KEY_GRAVE_ACCENT            = GLFW_KEY_GRAVE_ACCENT;
	const int KEY_WORLD_1                 = GLFW_KEY_WORLD_1;
	const int KEY_WORLD_2                 = GLFW_KEY_WORLD_2;
	const int KEY_ESCAPE                  = GLFW_KEY_ESCAPE;
	const int KEY_ENTER                   = GLFW_KEY_ENTER;
	const int KEY_TAB                     = GLFW_KEY_TAB;
	const int KEY_BACKSPACE               = GLFW_KEY_BACKSPACE;
	const int KEY_INSERT                  = GLFW_KEY_INSERT;
	const int KEY_DELETE                  = GLFW_KEY_DELETE;
	const int KEY_RIGHT                   = GLFW_KEY_RIGHT;
	const int KEY_LEFT                    = GLFW_KEY_LEFT;
	const int KEY_DOWN                    = GLFW_KEY_DOWN;
	const int KEY_UP                      = GLFW_KEY_UP;
	const int KEY_PAGE_UP                 = GLFW_KEY_PAGE_UP;
	const int KEY_PAGE_DOWN               = GLFW_KEY_PAGE_DOWN;
	const int KEY_HOME                    = GLFW_KEY_HOME;
	const int KEY_END                     = GLFW_KEY_END;
	const int KEY_CAPS_LOCK               = GLFW_KEY_CAPS_LOCK;
	const int KEY_SCROLL_LOCK             = GLFW_KEY_SCROLL_LOCK;
	const int KEY_NUM_LOCK                = GLFW_KEY_NUM_LOCK;
	const int KEY_PRINT_SCREEN            = GLFW_KEY_PRINT_SCREEN;
	const int KEY_PAUSE                   = GLFW_KEY_PAUSE;
	const int KEY_F1                      = GLFW_KEY_F1;
	const int KEY_F2                      = GLFW_KEY_F2;
	const int KEY_F3                      = GLFW_KEY_F3;
	const int KEY_F4                      = GLFW_KEY_F4;
	const int KEY_F5                      = GLFW_KEY_F5;
	const int KEY_F6                      = GLFW_KEY_F6;
	const int KEY_F7                      = GLFW_KEY_F7;
	const int KEY_F8                      = GLFW_KEY_F8;
	const int KEY_F9                      = GLFW_KEY_F9;
	const int KEY_F10                     = GLFW_KEY_F10;
	const int KEY_F11                     = GLFW_KEY_F11;
	const int KEY_F12                     = GLFW_KEY_F12;
	const int KEY_F13                     = GLFW_KEY_F13;
	const int KEY_F14                     = GLFW_KEY_F14;
	const int KEY_F15                     = GLFW_KEY_F15;
	const int KEY_F16                     = GLFW_KEY_F16;
	const int KEY_F17                     = GLFW_KEY_F17;
	const int KEY_F18                     = GLFW_KEY_F18;
	const int KEY_F19                     = GLFW_KEY_F19;
	const int KEY_F20                     = GLFW_KEY_F20;
	const int KEY_F21                     = GLFW_KEY_F21;
	const int KEY_F22                     = GLFW_KEY_F22;
	const int KEY_F23                     = GLFW_KEY_F23;
	const int KEY_F24                     = GLFW_KEY_F24;
	const int KEY_F25                     = GLFW_KEY_F25;
	const int KEY_KP_0                    = GLFW_KEY_KP_0;
	const int KEY_KP_1                    = GLFW_KEY_KP_1;
	const int KEY_KP_2                    = GLFW_KEY_KP_2;
	const int KEY_KP_3                    = GLFW_KEY_KP_3;
	const int KEY_KP_4                    = GLFW_KEY_KP_4;
	const int KEY_KP_5                    = GLFW_KEY_KP_5;
	const int KEY_KP_6                    = GLFW_KEY_KP_6;
	const int KEY_KP_7                    = GLFW_KEY_KP_7;
	const int KEY_KP_8                    = GLFW_KEY_KP_8;
	const int KEY_KP_9                    = GLFW_KEY_KP_9;
	const int KEY_KP_DECIMAL              = GLFW_KEY_KP_DECIMAL;
	const int KEY_KP_DIVIDE               = GLFW_KEY_KP_DIVIDE;
	const int KEY_KP_MULTIPLY             = GLFW_KEY_KP_MULTIPLY;
	const int KEY_KP_SUBTRACT             = GLFW_KEY_KP_SUBTRACT;
	const int KEY_KP_ADD                  = GLFW_KEY_KP_ADD;
	const int KEY_KP_ENTER                = GLFW_KEY_KP_ENTER;
	const int KEY_KP_EQUAL                = GLFW_KEY_KP_EQUAL;
	const int KEY_LEFT_SHIFT              = GLFW_KEY_LEFT_SHIFT;
	const int KEY_LEFT_CONTROL            = GLFW_KEY_LEFT_CONTROL;
	const int KEY_LEFT_ALT                = GLFW_KEY_LEFT_ALT;
	const int KEY_LEFT_SUPER              = GLFW_KEY_LEFT_SUPER;
	const int KEY_RIGHT_SHIFT             = GLFW_KEY_RIGHT_SHIFT;
	const int KEY_RIGHT_CONTROL           = GLFW_KEY_RIGHT_CONTROL;
	const int KEY_RIGHT_ALT               = GLFW_KEY_RIGHT_ALT;
	const int KEY_RIGHT_SUPER             = GLFW_KEY_RIGHT_SUPER;
	const int KEY_MENU                    = GLFW_KEY_MENU;
	const int KEY_LAST                    = GLFW_KEY_LAST;
	const int MOD_SHIFT                   = GLFW_MOD_SHIFT;
	const int MOD_CONTROL                 = GLFW_MOD_CONTROL;
	const int MOD_ALT                     = GLFW_MOD_ALT;
	const int MOD_SUPER                   = GLFW_MOD_SUPER;
	const int MOD_CAPS_LOCK               = GLFW_MOD_CAPS_LOCK;
	const int MOD_NUM_LOCK                = GLFW_MOD_NUM_LOCK;

#elif defined(USE_SDL2_WINDOW)
	// Mouse mapping
	const int MOUSE_BUTTON_LEFT           = SDL_BUTTON_LEFT;
	const int MOUSE_BUTTON_RIGHT          = SDL_BUTTON_RIGHT;
	const int MOUSE_BUTTON_MIDDLE         = SDL_BUTTON_MIDDLE;
	const int MOUSE_BUTTON_1              = SDL_BUTTON_X1;
	const int MOUSE_BUTTON_2              = SDL_BUTTON_X2;
	const int MOUSE_BUTTON_3              = -1;
	const int MOUSE_BUTTON_4              = -1;
	const int MOUSE_BUTTON_5              = -1;
	const int MOUSE_BUTTON_6              = -1;
	const int MOUSE_BUTTON_7              = -1;
	const int MOUSE_BUTTON_8              = -1;

	// Keyboard mapping
	const int KEY_UNKNOWN                 = SDLK_UNKNOWN;
	const int KEY_SPACE                   = SDLK_SPACE;
	const int KEY_APOSTROPHE              = SDLK_QUOTE;
	const int KEY_COMMA                   = SDLK_COMMA;
	const int KEY_MINUS                   = SDLK_MINUS;
	const int KEY_PERIOD                  = SDLK_PERIOD;
	const int KEY_SLASH                   = SDLK_SLASH;
	const int KEY_0                       = SDLK_0;
	const int KEY_1                       = SDLK_1;
	const int KEY_2                       = SDLK_2;
	const int KEY_3                       = SDLK_3;
	const int KEY_4                       = SDLK_4;
	const int KEY_5                       = SDLK_5;
	const int KEY_6                       = SDLK_6;
	const int KEY_7                       = SDLK_7;
	const int KEY_8                       = SDLK_8;
	const int KEY_9                       = SDLK_9;
	const int KEY_SEMICOLON               = SDLK_SEMICOLON;
	const int KEY_EQUAL                   = SDLK_EQUALS;
	const int KEY_A                       = SDLK_a;
	const int KEY_B                       = SDLK_b;
	const int KEY_C                       = SDLK_c;
	const int KEY_D                       = SDLK_d;
	const int KEY_E                       = SDLK_e;
	const int KEY_F                       = SDLK_f;
	const int KEY_G                       = SDLK_g;
	const int KEY_H                       = SDLK_h;
	const int KEY_I                       = SDLK_i;
	const int KEY_J                       = SDLK_j;
	const int KEY_K                       = SDLK_k;
	const int KEY_L                       = SDLK_l;
	const int KEY_M                       = SDLK_m;
	const int KEY_N                       = SDLK_n;
	const int KEY_O                       = SDLK_o;
	const int KEY_P                       = SDLK_p;
	const int KEY_Q                       = SDLK_q;
	const int KEY_R                       = SDLK_r;
	const int KEY_S                       = SDLK_s;
	const int KEY_T                       = SDLK_t;
	const int KEY_U                       = SDLK_u;
	const int KEY_V                       = SDLK_v;
	const int KEY_W                       = SDLK_w;
	const int KEY_X                       = SDLK_x;
	const int KEY_Y                       = SDLK_y;
	const int KEY_Z                       = SDLK_z;
	const int KEY_LEFT_BRACKET            = SDLK_LEFTBRACKET;
	const int KEY_BACKSLASH               = SDLK_BACKSLASH;
	const int KEY_RIGHT_BRACKET           = SDLK_RIGHTBRACKET;
	const int KEY_GRAVE_ACCENT            = SDLK_BACKQUOTE;
	const int KEY_WORLD_1                 = -1;
	const int KEY_WORLD_2                 = -1;
	const int KEY_ESCAPE                  = SDLK_ESCAPE;
	const int KEY_ENTER                   = SDLK_RETURN;
	const int KEY_TAB                     = SDLK_TAB;
	const int KEY_BACKSPACE               = SDLK_BACKSPACE;
	const int KEY_INSERT                  = SDLK_INSERT;
	const int KEY_DELETE                  = SDLK_DELETE;
	const int KEY_RIGHT                   = SDLK_RIGHT;
	const int KEY_LEFT                    = SDLK_LEFT;
	const int KEY_DOWN                    = SDLK_DOWN;
	const int KEY_UP                      = SDLK_UP;
	const int KEY_PAGE_UP                 = SDLK_PAGEUP;
	const int KEY_PAGE_DOWN               = SDLK_PAGEDOWN;
	const int KEY_HOME                    = SDLK_HOME;
	const int KEY_END                     = SDLK_END;
	const int KEY_CAPS_LOCK               = SDLK_CAPSLOCK;
	const int KEY_SCROLL_LOCK             = SDLK_SCROLLLOCK;
	const int KEY_NUM_LOCK                = SDLK_NUMLOCKCLEAR;
	const int KEY_PRINT_SCREEN            = SDLK_PRINTSCREEN;
	const int KEY_PAUSE                   = SDLK_PAUSE;
	const int KEY_F1                      = SDLK_F1;
	const int KEY_F2                      = SDLK_F2;
	const int KEY_F3                      = SDLK_F3;
	const int KEY_F4                      = SDLK_F4;
	const int KEY_F5                      = SDLK_F5;
	const int KEY_F6                      = SDLK_F6;
	const int KEY_F7                      = SDLK_F7;
	const int KEY_F8                      = SDLK_F8;
	const int KEY_F9                      = SDLK_F9;
	const int KEY_F10                     = SDLK_F10;
	const int KEY_F11                     = SDLK_F11;
	const int KEY_F12                     = SDLK_F12;
	const int KEY_F13                     = SDLK_F13;
	const int KEY_F14                     = SDLK_F14;
	const int KEY_F15                     = SDLK_F15;
	const int KEY_F16                     = SDLK_F16;
	const int KEY_F17                     = SDLK_F17;
	const int KEY_F18                     = SDLK_F18;
	const int KEY_F19                     = SDLK_F19;
	const int KEY_F20                     = SDLK_F20;
	const int KEY_F21                     = SDLK_F21;
	const int KEY_F22                     = SDLK_F22;
	const int KEY_F23                     = SDLK_F23;
	const int KEY_F24                     = SDLK_F24;
	const int KEY_F25                     = -1;
	const int KEY_KP_0                    = SDLK_KP_0;
	const int KEY_KP_1                    = SDLK_KP_1;
	const int KEY_KP_2                    = SDLK_KP_2;
	const int KEY_KP_3                    = SDLK_KP_3;
	const int KEY_KP_4                    = SDLK_KP_4;
	const int KEY_KP_5                    = SDLK_KP_5;
	const int KEY_KP_6                    = SDLK_KP_6;
	const int KEY_KP_7                    = SDLK_KP_7;
	const int KEY_KP_8                    = SDLK_KP_8;
	const int KEY_KP_9                    = SDLK_KP_9;
	const int KEY_KP_DECIMAL              = SDLK_KP_PERIOD;
	const int KEY_KP_DIVIDE               = SDLK_KP_DIVIDE;
	const int KEY_KP_MULTIPLY             = SDLK_KP_MULTIPLY;
	const int KEY_KP_SUBTRACT             = SDLK_KP_MINUS;
	const int KEY_KP_ADD                  = SDLK_KP_PLUS;
	const int KEY_KP_ENTER                = SDLK_KP_ENTER;
	const int KEY_KP_EQUAL                = SDLK_KP_EQUALS;
	const int KEY_LEFT_SHIFT              = SDLK_LSHIFT;
	const int KEY_LEFT_CONTROL            = SDLK_LCTRL;
	const int KEY_LEFT_ALT                = SDLK_LALT;
	const int KEY_LEFT_SUPER              = SDLK_LGUI;
	const int KEY_RIGHT_SHIFT             = SDLK_RSHIFT;
	const int KEY_RIGHT_CONTROL           = SDLK_RCTRL;
	const int KEY_RIGHT_ALT               = SDLK_RALT;
	const int KEY_RIGHT_SUPER             = SDLK_RGUI;
	const int KEY_MENU                    = SDLK_MENU;
	const int KEY_LAST                    = -1;
	const int MOD_SHIFT                   = KMOD_SHIFT;
	const int MOD_CONTROL                 = KMOD_CTRL;
	const int MOD_ALT                     = KMOD_ALT;
	const int MOD_SUPER                   = KMOD_GUI;
	const int MOD_CAPS_LOCK               = KMOD_CAPS;
	const int MOD_NUM_LOCK                = KMOD_NUM;
#endif


std::string ourKeyNamesAsMacro =
R"(#define KEY_UNKNOWN
#define KEY_SPACE
#define KEY_APOSTROPHE
#define KEY_COMMA
#define KEY_MINUS
#define KEY_PERIOD
#define KEY_SLASH
#define KEY_0
#define KEY_1
#define KEY_2
#define KEY_3
#define KEY_4
#define KEY_5
#define KEY_6
#define KEY_7
#define KEY_8
#define KEY_9
#define KEY_SEMICOLON
#define KEY_EQUAL
#define KEY_A
#define KEY_B
#define KEY_C
#define KEY_D
#define KEY_E
#define KEY_F
#define KEY_G
#define KEY_H
#define KEY_I
#define KEY_J
#define KEY_K
#define KEY_L
#define KEY_M
#define KEY_N
#define KEY_O
#define KEY_P
#define KEY_Q
#define KEY_R
#define KEY_S
#define KEY_T
#define KEY_U
#define KEY_V
#define KEY_W
#define KEY_X
#define KEY_Y
#define KEY_Z
#define KEY_LEFT_BRACKET
#define KEY_BACKSLASH
#define KEY_RIGHT_BRACKET
#define KEY_GRAVE_ACCENT
#define KEY_WORLD_1
#define KEY_WORLD_2
#define KEY_ESCAPE
#define KEY_ENTER
#define KEY_TAB
#define KEY_BACKSPACE
#define KEY_INSERT
#define KEY_DELETE
#define KEY_RIGHT
#define KEY_LEFT
#define KEY_DOWN
#define KEY_UP
#define KEY_PAGE_UP
#define KEY_PAGE_DOWN
#define KEY_HOME
#define KEY_END
#define KEY_CAPS_LOCK
#define KEY_SCROLL_LOCK
#define KEY_NUM_LOCK
#define KEY_PRINT_SCREEN
#define KEY_PAUSE
#define KEY_F1
#define KEY_F2
#define KEY_F3
#define KEY_F4
#define KEY_F5
#define KEY_F6
#define KEY_F7
#define KEY_F8
#define KEY_F9
#define KEY_F10
#define KEY_F11
#define KEY_F12
#define KEY_F13
#define KEY_F14
#define KEY_F15
#define KEY_F16
#define KEY_F17
#define KEY_F18
#define KEY_F19
#define KEY_F20
#define KEY_F21
#define KEY_F22
#define KEY_F23
#define KEY_F24
#define KEY_F25
#define KEY_KP_0
#define KEY_KP_1
#define KEY_KP_2
#define KEY_KP_3
#define KEY_KP_4
#define KEY_KP_5
#define KEY_KP_6
#define KEY_KP_7
#define KEY_KP_8
#define KEY_KP_9
#define KEY_KP_DECIMAL
#define KEY_KP_DIVIDE
#define KEY_KP_MULTIPLY
#define KEY_KP_SUBTRACT
#define KEY_KP_ADD
#define KEY_KP_ENTER
#define KEY_KP_EQUAL
#define KEY_LEFT_SHIFT
#define KEY_LEFT_CONTROL
#define KEY_LEFT_ALT
#define KEY_LEFT_SUPER
#define KEY_RIGHT_SHIFT
#define KEY_RIGHT_CONTROL
#define KEY_RIGHT_ALT
#define KEY_RIGHT_SUPER
#define KEY_MENU
#define KEY_LAST
#define MOD_SHIFT
#define MOD_CONTROL
#define MOD_ALT
#define MOD_SUPER
#define MOD_CAPS_LOCK
#define MOD_NUM_LOCK
)";


std::string ourKeyNamesAsVar =
R"(extern const int KEY_UNKNOWN
extern const int KEY_SPACE
extern const int KEY_APOSTROPHE
extern const int KEY_COMMA
extern const int KEY_MINUS
extern const int KEY_PERIOD
extern const int KEY_SLASH
extern const int KEY_0
extern const int KEY_1
extern const int KEY_2
extern const int KEY_3
extern const int KEY_4
extern const int KEY_5
extern const int KEY_6
extern const int KEY_7
extern const int KEY_8
extern const int KEY_9
extern const int KEY_SEMICOLON
extern const int KEY_EQUAL
extern const int KEY_A
extern const int KEY_B
extern const int KEY_C
extern const int KEY_D
extern const int KEY_E
extern const int KEY_F
extern const int KEY_G
extern const int KEY_H
extern const int KEY_I
extern const int KEY_J
extern const int KEY_K
extern const int KEY_L
extern const int KEY_M
extern const int KEY_N
extern const int KEY_O
extern const int KEY_P
extern const int KEY_Q
extern const int KEY_R
extern const int KEY_S
extern const int KEY_T
extern const int KEY_U
extern const int KEY_V
extern const int KEY_W
extern const int KEY_X
extern const int KEY_Y
extern const int KEY_Z
extern const int KEY_LEFT_BRACKET
extern const int KEY_BACKSLASH
extern const int KEY_RIGHT_BRACKET
extern const int KEY_GRAVE_ACCENT
extern const int KEY_WORLD_1
extern const int KEY_WORLD_2
extern const int KEY_ESCAPE
extern const int KEY_ENTER
extern const int KEY_TAB
extern const int KEY_BACKSPACE
extern const int KEY_INSERT
extern const int KEY_DELETE
extern const int KEY_RIGHT
extern const int KEY_LEFT
extern const int KEY_DOWN
extern const int KEY_UP
extern const int KEY_PAGE_UP
extern const int KEY_PAGE_DOWN
extern const int KEY_HOME
extern const int KEY_END
extern const int KEY_CAPS_LOCK
extern const int KEY_SCROLL_LOCK
extern const int KEY_NUM_LOCK
extern const int KEY_PRINT_SCREEN
extern const int KEY_PAUSE
extern const int KEY_F1
extern const int KEY_F2
extern const int KEY_F3
extern const int KEY_F4
extern const int KEY_F5
extern const int KEY_F6
extern const int KEY_F7
extern const int KEY_F8
extern const int KEY_F9
extern const int KEY_F10
extern const int KEY_F11
extern const int KEY_F12
extern const int KEY_F13
extern const int KEY_F14
extern const int KEY_F15
extern const int KEY_F16
extern const int KEY_F17
extern const int KEY_F18
extern const int KEY_F19
extern const int KEY_F20
extern const int KEY_F21
extern const int KEY_F22
extern const int KEY_F23
extern const int KEY_F24
extern const int KEY_F25
extern const int KEY_KP_0
extern const int KEY_KP_1
extern const int KEY_KP_2
extern const int KEY_KP_3
extern const int KEY_KP_4
extern const int KEY_KP_5
extern const int KEY_KP_6
extern const int KEY_KP_7
extern const int KEY_KP_8
extern const int KEY_KP_9
extern const int KEY_KP_DECIMAL
extern const int KEY_KP_DIVIDE
extern const int KEY_KP_MULTIPLY
extern const int KEY_KP_SUBTRACT
extern const int KEY_KP_ADD
extern const int KEY_KP_ENTER
extern const int KEY_KP_EQUAL
extern const int KEY_LEFT_SHIFT
extern const int KEY_LEFT_CONTROL
extern const int KEY_LEFT_ALT
extern const int KEY_LEFT_SUPER
extern const int KEY_RIGHT_SHIFT
extern const int KEY_RIGHT_CONTROL
extern const int KEY_RIGHT_ALT
extern const int KEY_RIGHT_SUPER
extern const int KEY_MENU
extern const int KEY_LAST
extern const int MOD_SHIFT
extern const int MOD_CONTROL
extern const int MOD_ALT
extern const int MOD_SUPER
extern const int MOD_CAPS_LOCK
extern const int MOD_NUM_LOCK
)";


void keyMappingHelper_GLFW()
{
	std::string str =
R"(#define GLFW_KEY_UNKNOWN            GLFW_KEY_UNKNOWN
#define GLFW_KEY_SPACE              32
#define GLFW_KEY_APOSTROPHE         39
#define GLFW_KEY_COMMA              44
#define GLFW_KEY_MINUS              45
#define GLFW_KEY_PERIOD             46
#define GLFW_KEY_SLASH              47
#define GLFW_KEY_0                  48
#define GLFW_KEY_1                  49
#define GLFW_KEY_2                  50
#define GLFW_KEY_3                  51
#define GLFW_KEY_4                  52
#define GLFW_KEY_5                  53
#define GLFW_KEY_6                  54
#define GLFW_KEY_7                  55
#define GLFW_KEY_8                  56
#define GLFW_KEY_9                  57
#define GLFW_KEY_SEMICOLON          59
#define GLFW_KEY_EQUAL              61
#define GLFW_KEY_A                  65
#define GLFW_KEY_B                  66
#define GLFW_KEY_C                  67
#define GLFW_KEY_D                  68
#define GLFW_KEY_E                  69
#define GLFW_KEY_F                  70
#define GLFW_KEY_G                  71
#define GLFW_KEY_H                  72
#define GLFW_KEY_I                  73
#define GLFW_KEY_J                  74
#define GLFW_KEY_K                  75
#define GLFW_KEY_L                  76
#define GLFW_KEY_M                  77
#define GLFW_KEY_N                  78
#define GLFW_KEY_O                  79
#define GLFW_KEY_P                  80
#define GLFW_KEY_Q                  81
#define GLFW_KEY_R                  82
#define GLFW_KEY_S                  83
#define GLFW_KEY_T                  84
#define GLFW_KEY_U                  85
#define GLFW_KEY_V                  86
#define GLFW_KEY_W                  87
#define GLFW_KEY_X                  88
#define GLFW_KEY_Y                  89
#define GLFW_KEY_Z                  90
#define GLFW_KEY_LEFT_BRACKET       91
#define GLFW_KEY_BACKSLASH          92
#define GLFW_KEY_RIGHT_BRACKET      93
#define GLFW_KEY_GRAVE_ACCENT       96
#define GLFW_KEY_WORLD_1            161
#define GLFW_KEY_WORLD_2            162
#define GLFW_KEY_ESCAPE             256
#define GLFW_KEY_ENTER              257
#define GLFW_KEY_TAB                258
#define GLFW_KEY_BACKSPACE          259
#define GLFW_KEY_INSERT             260
#define GLFW_KEY_DELETE             261
#define GLFW_KEY_RIGHT              262
#define GLFW_KEY_LEFT               263
#define GLFW_KEY_DOWN               264
#define GLFW_KEY_UP                 265
#define GLFW_KEY_PAGE_UP            266
#define GLFW_KEY_PAGE_DOWN          267
#define GLFW_KEY_HOME               268
#define GLFW_KEY_END                269
#define GLFW_KEY_CAPS_LOCK          280
#define GLFW_KEY_SCROLL_LOCK        281
#define GLFW_KEY_NUM_LOCK           282
#define GLFW_KEY_PRINT_SCREEN       283
#define GLFW_KEY_PAUSE              284
#define GLFW_KEY_F1                 290
#define GLFW_KEY_F2                 291
#define GLFW_KEY_F3                 292
#define GLFW_KEY_F4                 293
#define GLFW_KEY_F5                 294
#define GLFW_KEY_F6                 295
#define GLFW_KEY_F7                 296
#define GLFW_KEY_F8                 297
#define GLFW_KEY_F9                 298
#define GLFW_KEY_F10                299
#define GLFW_KEY_F11                300
#define GLFW_KEY_F12                301
#define GLFW_KEY_F13                302
#define GLFW_KEY_F14                303
#define GLFW_KEY_F15                304
#define GLFW_KEY_F16                305
#define GLFW_KEY_F17                306
#define GLFW_KEY_F18                307
#define GLFW_KEY_F19                308
#define GLFW_KEY_F20                309
#define GLFW_KEY_F21                310
#define GLFW_KEY_F22                311
#define GLFW_KEY_F23                312
#define GLFW_KEY_F24                313
#define GLFW_KEY_F25                314
#define GLFW_KEY_KP_0               320
#define GLFW_KEY_KP_1               321
#define GLFW_KEY_KP_2               322
#define GLFW_KEY_KP_3               323
#define GLFW_KEY_KP_4               324
#define GLFW_KEY_KP_5               325
#define GLFW_KEY_KP_6               326
#define GLFW_KEY_KP_7               327
#define GLFW_KEY_KP_8               328
#define GLFW_KEY_KP_9               329
#define GLFW_KEY_KP_DECIMAL         330
#define GLFW_KEY_KP_DIVIDE          331
#define GLFW_KEY_KP_MULTIPLY        332
#define GLFW_KEY_KP_SUBTRACT        333
#define GLFW_KEY_KP_ADD             334
#define GLFW_KEY_KP_ENTER           335
#define GLFW_KEY_KP_EQUAL           336
#define GLFW_KEY_LEFT_SHIFT         340
#define GLFW_KEY_LEFT_CONTROL       341
#define GLFW_KEY_LEFT_ALT           342
#define GLFW_KEY_LEFT_SUPER         343
#define GLFW_KEY_RIGHT_SHIFT        344
#define GLFW_KEY_RIGHT_CONTROL      345
#define GLFW_KEY_RIGHT_ALT          346
#define GLFW_KEY_RIGHT_SUPER        347
#define GLFW_KEY_MENU               348
#define GLFW_KEY_LAST               GLFW_KEY_MENU
#define GLFW_MOD_SHIFT           0x0001
#define GLFW_MOD_CONTROL         0x0002
#define GLFW_MOD_ALT             0x0004
#define GLFW_MOD_SUPER           0x0008
#define GLFW_MOD_CAPS_LOCK       0x0010
#define GLFW_MOD_NUM_LOCK        0x0020
)";

	std::vector<std::string> glfwKeys;
	size_t offset = 0;
	while (true)
	{
		size_t pos = str.find('\n', offset);
		if (pos == std::string::npos)
		{
			break;
		}
		std::string line = str.substr(offset, pos - offset);

		offset = pos + 1;
		const std::string prefix = "#define ";
		if (!line.empty())
		{
			line.erase(0, prefix.size());
			line.erase(line.find(' '));
			glfwKeys.push_back(line);
		}
	}

	std::vector<std::string> ourKeys;
	offset = 0;
	while (true)
	{
		size_t pos = ourKeyNamesAsVar.find('\n', offset);
		if (pos == std::string::npos)
		{
			break;
		}
		std::string line = ourKeyNamesAsVar.substr(offset, pos - offset);
		offset = pos + 1;
		if (!line.empty())
		{
			ourKeys.push_back(line);
		}
	}

	std::string name;
	for (size_t i = 0, size = ourKeys.size(); i < size; ++i)
	{
		name = ourKeys[i];
		name.insert(name.end(), 45 - name.size(), ' ');
		name += "= ";
		name += glfwKeys[i];
		name.push_back(';');

		name.erase(0, 7);
		printf("%s\n", name.c_str());
	}
	printf("\n");
}

void keyMappingHelper_SDL2()
{
	std::string str =
		R"(SDLK_UNKNOWN = 0,
SDLK_SPACE = ' ',
SDLK_QUOTE = '\'',
SDLK_COMMA = ',',
SDLK_MINUS = '-',
SDLK_PERIOD = '.',
SDLK_SLASH = '/',
SDLK_0 = '0',
SDLK_1 = '1',
SDLK_2 = '2',
SDLK_3 = '3',
SDLK_4 = '4',
SDLK_5 = '5',
SDLK_6 = '6',
SDLK_7 = '7',
SDLK_8 = '8',
SDLK_9 = '9',
SDLK_SEMICOLON = ';',
SDLK_EQUALS = '=',
SDLK_a = 'a',
SDLK_b = 'b',
SDLK_c = 'c',
SDLK_d = 'd',
SDLK_e = 'e',
SDLK_f = 'f',
SDLK_g = 'g',
SDLK_h = 'h',
SDLK_i = 'i',
SDLK_j = 'j',
SDLK_k = 'k',
SDLK_l = 'l',
SDLK_m = 'm',
SDLK_n = 'n',
SDLK_o = 'o',
SDLK_p = 'p',
SDLK_q = 'q',
SDLK_r = 'r',
SDLK_s = 's',
SDLK_t = 't',
SDLK_u = 'u',
SDLK_v = 'v',
SDLK_w = 'w',
SDLK_x = 'x',
SDLK_y = 'y',
SDLK_z = 'z',
SDLK_LEFTBRACKET = '[',
SDLK_BACKSLASH = '\\',
SDLK_RIGHTBRACKET = ']',
SDLK_BACKQUOTE = '`',
[EMPTY]
[EMPTY]
SDLK_ESCAPE = '\x1B',
SDLK_RETURN = '\r',
SDLK_TAB = '\t',
SDLK_BACKSPACE = '\b',
SDLK_INSERT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_INSERT),
SDLK_DELETE = '\x7F',
SDLK_RIGHT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RIGHT),
SDLK_LEFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LEFT),
SDLK_DOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_DOWN),
SDLK_UP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_UP),
SDLK_PAGEUP = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEUP),
SDLK_PAGEDOWN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAGEDOWN),
SDLK_HOME = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_HOME),
SDLK_END = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_END),
SDLK_CAPSLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_CAPSLOCK),
SDLK_SCROLLLOCK = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_SCROLLLOCK),
SDLK_NUMLOCKCLEAR = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_NUMLOCKCLEAR),
SDLK_PRINTSCREEN = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PRINTSCREEN),
SDLK_PAUSE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_PAUSE),
SDLK_F1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F1),
SDLK_F2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F2),
SDLK_F3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F3),
SDLK_F4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F4),
SDLK_F5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F5),
SDLK_F6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F6),
SDLK_F7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F7),
SDLK_F8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F8),
SDLK_F9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F9),
SDLK_F10 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F10),
SDLK_F11 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F11),
SDLK_F12 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F12),
SDLK_F13 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F13),
SDLK_F14 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F14),
SDLK_F15 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F15),
SDLK_F16 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F16),
SDLK_F17 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F17),
SDLK_F18 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F18),
SDLK_F19 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F19),
SDLK_F20 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F20),
SDLK_F21 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F21),
SDLK_F22 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F22),
SDLK_F23 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F23),
SDLK_F24 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_F24),
[EMPTY]
SDLK_KP_0 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_0),
SDLK_KP_1 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_1),
SDLK_KP_2 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_2),
SDLK_KP_3 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_3),
SDLK_KP_4 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_4),
SDLK_KP_5 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_5),
SDLK_KP_6 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_6),
SDLK_KP_7 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_7),
SDLK_KP_8 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_8),
SDLK_KP_9 = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_9),
SDLK_KP_PERIOD = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PERIOD),
SDLK_KP_DIVIDE = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_DIVIDE),
SDLK_KP_MULTIPLY = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MULTIPLY),
SDLK_KP_MINUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_MINUS),
SDLK_KP_PLUS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_PLUS),
SDLK_KP_ENTER = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_ENTER),
SDLK_KP_EQUALS = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_KP_EQUALS),
SDLK_LSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LSHIFT),
SDLK_LCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LCTRL),
SDLK_LALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LALT),
SDLK_LGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_LGUI),
SDLK_RSHIFT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RSHIFT),
SDLK_RCTRL = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RCTRL),
SDLK_RALT = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RALT),
SDLK_RGUI = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_RGUI),
SDLK_MENU = SDL_SCANCODE_TO_KEYCODE(SDL_SCANCODE_MENU),
[EMPTY]
KMOD_SHIFT = KMOD_LSHIFT | KMOD_RSHIFT,
KMOD_CTRL = KMOD_LCTRL | KMOD_RCTRL,
KMOD_ALT = KMOD_LALT | KMOD_RALT,
KMOD_GUI = KMOD_LGUI | KMOD_RGUI,
KMOD_CAPS = 0x2000,
KMOD_NUM = 0x1000,
)";

	std::vector<std::string> sdlKeys;
	size_t offset = 0;
	while (true)
	{
		size_t pos = str.find('\n', offset);
		if (pos == std::string::npos)
		{
			break;
		}
		std::string line = str.substr(offset, pos - offset);

		offset = pos + 1;
		if (!line.empty())
		{
			if (line != "[EMPTY]")
			{
				line.erase(line.find(' '));
			}
			sdlKeys.push_back(line);
		}
	}

	std::vector<std::string> ourKeys;
	offset = 0;
	while (true)
	{
		size_t pos = ourKeyNamesAsVar.find('\n', offset);
		if (pos == std::string::npos)
		{
			break;
		}
		std::string line = ourKeyNamesAsVar.substr(offset, pos - offset);
		offset = pos + 1;
		if (!line.empty())
		{
			ourKeys.push_back(line);
		}
	}

	std::string name;
	for (size_t i = 0, size = ourKeys.size(); i < size; ++i)
	{
		name = ourKeys[i];
		name.insert(name.end(), 45 - name.size(), ' ');
		name += "= ";
		name += sdlKeys[i];
		name.push_back(';');

		name.erase(0, 7);

		printf("%s\n", name.c_str());
	}
	printf("\n");
}