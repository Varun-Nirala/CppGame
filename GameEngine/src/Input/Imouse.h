#pragma once

#include <functional>
#include <algorithm>
#include <vector>

/* In case required for nameless union/struct used in MouseButton
#pragma warning(push)
#pragma warning(disable: 4201)
*/

struct MouseButton
{
	struct Action
	{
		bool		up{ true };
		bool		down{ false };
		bool		held{ false };
	};

	struct Button
	{
		bool		left{ false };
		bool		middle{ false };
		bool		right{ false };
		int			id{};
	};

	uint8_t		clicks{};
	int			mods{};
	double		x{};
	double		y{};

	Action		action;
	Button		button;
};

class DisplayWindow;

class Imouse
{
	using OnMouseButton_CB	= std::function<void(const MouseButton&)>;
	using OnMouseMove_CB	= std::function<void(double, double, double, double)>;
	using OnWheelScroll_CB = std::function<void(double, double)>;

public:
	virtual ~Imouse() = default;

	Imouse(DisplayWindow *pWindow)
		: m_pWindow(pWindow)
	{
	}

	virtual void registerCallbacks() {};

	void registerOnMouseButtonCB(OnMouseButton_CB cb)
	{
		m_buttonCallbacks.push_back(cb);
	}

	void registerOnMouseMoveCB(OnMouseMove_CB cb)
	{
		m_moveCallbacks.push_back(cb);
	}

	void registerOnWheelScrollCB(OnWheelScroll_CB cb)
	{
		m_scrollCallbacks.push_back(cb);
	}

	void newButtonEvent(MouseButton mousebutton)
	{
		std::for_each(m_buttonCallbacks.begin(), m_buttonCallbacks.end(), [&mousebutton](OnMouseButton_CB& func) -> void
			{
				func(mousebutton);
			});
	}

	void newMoveEvent(double x, double y)
	{
		if (m_bFirstMouseMove)
		{
			m_lastX = x;
			m_lastY = y;
			m_bFirstMouseMove = false;
		}

		double offsetX = x - m_lastX;
		double offsetY = m_lastY - y;

		m_lastX = x;
		m_lastY = y;

		std::for_each(m_moveCallbacks.begin(), m_moveCallbacks.end(), [x, y, offsetX, offsetY](OnMouseMove_CB& func) -> void
			{
				func(x, y, offsetX, offsetY);
			});
	}

	void newScrollEvent(double offsetX, double offsetY)
	{
		std::for_each(m_scrollCallbacks.begin(), m_scrollCallbacks.end(), [offsetX, offsetY](OnWheelScroll_CB& func) -> void
			{
				func(offsetX, offsetY);
			});
	}

protected:
	double							m_posX{};
	double							m_posY{};
	double							m_lastX{};
	double							m_lastY{};

	bool							m_bFirstMouseMove{ true };

	std::vector<OnMouseButton_CB>	m_buttonCallbacks;
	std::vector<OnMouseMove_CB>		m_moveCallbacks;
	std::vector<OnWheelScroll_CB>	m_scrollCallbacks;

	DisplayWindow					*m_pWindow{};
};

extern const int MOUSE_BUTTON_LEFT;
extern const int MOUSE_BUTTON_RIGHT;
extern const int MOUSE_BUTTON_MIDDLE;
extern const int MOUSE_BUTTON_0;
extern const int MOUSE_BUTTON_1;
extern const int MOUSE_BUTTON_2;
extern const int MOUSE_BUTTON_3;
extern const int MOUSE_BUTTON_4;
extern const int MOUSE_BUTTON_5;
extern const int MOUSE_BUTTON_6;
extern const int MOUSE_BUTTON_7;
extern const int MOUSE_BUTTON_8;