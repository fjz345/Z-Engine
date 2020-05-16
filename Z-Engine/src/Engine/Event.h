#pragma once

#include "zepch.h"
#include "Core.h"

namespace ZE
{

#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled,
		AppTick, AppUpdate, AppRender
	};

	enum EventCategory
	{
		None = 0,
		CategoryApplication		= BIT(0),
		CategoryInput			= BIT(1),
		CategoryKeyboard		= BIT(2),
		CategoryMouse			= BIT(3),
		CategoryMouseButton		= BIT(4),
	};

	class ZE_API Event
	{
	public:
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

	private:

	protected:
		bool _handled = false;
	};


	class ZE_API EventHandler
	{

	};


	// ---------- Window --------------

	class ZE_API WindowResizeEvent : public Event
	{
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: _width(width), _height(height) {}

		EVENT_CLASS_TYPE(WindowResize)
			EVENT_CLASS_CATEGORY(EventCategory::CategoryApplication)

	private:
		unsigned int _width;
		unsigned int _height;

	};

	class ZE_API WindowCloseEvent : public Event
	{
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategory::CategoryApplication)

	private:

	};


	// ---------- Key --------------

	class ZE_API KeyEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return _keycode; }

		EVENT_CLASS_CATEGORY(EventCategory::CategoryKeyboard | EventCategory::CategoryInput)

	protected:
		KeyEvent(int keycode) : _keycode(keycode) {}

		int _keycode;

	};


	class ZE_API KeyPressedEvent : public KeyEvent
	{
	public:
		KeyPressedEvent(int keycode, int repeatCount) : KeyEvent(keycode), _repeatCount(repeatCount) {}

		inline int GetRepeatCount() const { return _repeatCount; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: (" << _keycode << ')';
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)

	private:
		int _repeatCount;

	};

	class ZE_API KeyReleasedEvent : public KeyEvent
	{
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "KeyPressedEvent: (" << _keycode << ')';
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)

	private:

	};

	// ---------- MOUSE --------------

	class ZE_API MouseButtonEvent : public Event
	{
	public:
		inline int GetKeyCode() const { return _keycode; }

		EVENT_CLASS_CATEGORY(EventCategory::CategoryMouse | EventCategory::CategoryInput)

	protected:
		MouseButtonEvent(int keycode) : _keycode(keycode) {}

		int _keycode;

	};


	class ZE_API MouseMovedEvent : public Event
	{
	public:
		MouseMovedEvent(float x, float y) : _x(x), _y(y) {}

		inline float GetX() const { return _x; }
		inline float GetY() const { return _y; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: (" << _x << ", " << _y << ')';
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategory::CategoryMouse | EventCategory::CategoryInput)

	private:
		float _x;
		float _y;
	};



	class ZE_API MouseScrolledEvent : public Event
	{
	public:
		MouseScrolledEvent(float xOffset, float yOffset) : _xOffset(xOffset), _yOffset(yOffset) {}

		inline float GetXOffset() const { return _xOffset; }
		inline float GetYOffset() const { return _yOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledEvent: (" << _xOffset << ", " << _yOffset << ')';
			return ss.str();
		}

		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategory::CategoryMouse | EventCategory::CategoryInput)

	private:
		float _xOffset;
		float _yOffset;
	};



	class ZE_API MouseButtonPressedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonPressedEvent(int keycode) : MouseButtonEvent(keycode) {}

		EVENT_CLASS_TYPE(MouseButtonPressed)

	private:
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedEvent: " << _keycode;
			return ss.str();
		}
	};


	class ZE_API MouseButtonReleasedEvent : public MouseButtonEvent
	{
	public:
		MouseButtonReleasedEvent(int keycode) : MouseButtonEvent(keycode) {}

		EVENT_CLASS_TYPE(MouseButtonReleased)

	private:
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedEvent: " << _keycode;
			return ss.str();
		}
	};
}