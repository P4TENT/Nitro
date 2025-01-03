#pragma once

#include "Event.h"

namespace Nitro {
	class NITRO_API KeyEvent : public Event {
	protected:
		int m_KeyCode;

	protected:
		KeyEvent(int keycode)
			: m_KeyCode(keycode) {}

	public:
		inline int GetKeyCode() const { return m_KeyCode; }

		EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput)	
	};

	class NITRO_API KeyPressedEvent : public KeyEvent {
	private:
		int m_RepeatCount;
	
	public:
		KeyPressedEvent(int keycode, int repeatCount) 
			: KeyEvent(keycode), m_RepeatCount(repeatCount)
		{}

		inline int GetRepeatCount() const { return m_RepeatCount; }

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "[KEY-PRESSED-EVENT]: " << m_KeyCode << " (" << m_RepeatCount << " repeats)";
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyPressed)
	};

	class NITRO_API KeyReleasedEvent : public KeyEvent {
	public:
		KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}

		std::string ToString() const override 
		{
			std::stringstream ss;
			ss << "[KEY-RELEASED-EVENT]: " << m_KeyCode;
			return ss.str();
		}

		EVENT_CLASS_TYPE(KeyReleased)
	};
}