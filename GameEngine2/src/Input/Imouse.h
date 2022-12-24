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
	{}

	virtual void registerCallbacks() {};

	void endFrame()
	{
		m_scrollX = m_scrollY = 0.0;
		m_mouseEvents.clear();
	}

	void clear()
	{
		m_posX = m_posY = m_lastX = m_lastY = m_scrollX = m_scrollY = 0.0;
		m_bMouseDrag = false;
		m_bMouseButtonDown = 0;
		m_mouseEvents.clear();
	}

	bool isMouseButtonPressed(int button)
	{
		for (size_t i = 0, size = m_mouseEvents.size(); i < size; ++i)
		{
			if (m_mouseEvents[i].button.id == button && m_mouseEvents[i].action.down)
			{
				return true;
			}
		}
		return false;
	}

	double getX() const { return m_posX; }
	double getY() const { return m_posY; }

	double getScrollX() const { return m_scrollX; }
	double getScrollY() const { return m_scrollY; }

	bool isDragging() const { return m_bMouseDrag; }

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
		if (mousebutton.action.down)
		{
			++m_bMouseButtonDown;
		}
		else if (mousebutton.action.up)
		{
			--m_bMouseButtonDown;
			m_bMouseDrag = false;
		}

		m_mouseEvents.push_back(mousebutton);

		std::for_each(m_buttonCallbacks.begin(), m_buttonCallbacks.end(), [&mousebutton](OnMouseButton_CB& func) -> void
			{
				func(mousebutton);
			});
	}

	void newMoveEvent(double x, double y)
	{
		if (m_bMouseButtonDown > 0)
		{
			m_bMouseDrag = true;
		}

		double offsetX = x - m_lastX;
		double offsetY = m_lastY - y;

		m_lastX = m_posX;
		m_lastY = m_posY;

		m_posX = x;
		m_posY = y;

		std::for_each(m_moveCallbacks.begin(), m_moveCallbacks.end(), [x, y, offsetX, offsetY](OnMouseMove_CB& func) -> void
			{
				func(x, y, offsetX, offsetY);
			});
	}

	void newScrollEvent(double offsetX, double offsetY)
	{
		m_scrollX = offsetX;
		m_scrollY = offsetY;

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
	double							m_scrollX{};
	double							m_scrollY{};

	bool							m_bMouseDrag{ false };

	int								m_bMouseButtonDown{};

	std::vector<OnMouseButton_CB>	m_buttonCallbacks;
	std::vector<OnMouseMove_CB>		m_moveCallbacks;
	std::vector<OnWheelScroll_CB>	m_scrollCallbacks;

	DisplayWindow					*m_pWindow{};

	std::vector<MouseButton>		m_mouseEvents;
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