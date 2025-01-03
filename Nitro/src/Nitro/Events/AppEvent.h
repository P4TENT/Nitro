#pragma once

#include "Event.h"

namespace Nitro {

	class NITRO_API WindowResizeEvent : public Event {
	private:
		NGUINT m_width, m_height;
	public:
		WindowResizeEvent(NGUINT width, NGUINT height)
			: m_width(width), m_height(height) {}

		inline NGUINT GetWidth() const { return m_width; }
		inline NGUINT GetHeight() const { return m_height; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "[WINDOW-RESIZE-EVENT]: " << m_width << ", " << m_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class NITRO_API WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class NITRO_API AppTickEvent : public Event {
	public:
		AppTickEvent() {}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class NITRO_API AppUpdateEvent : public Event {
	public:
		AppUpdateEvent() {}

		EVENT_CLASS_TYPE(AppUpdate)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class NITRO_API AppRenderEvent : public Event
	{
	public:
		AppRenderEvent() {}
		
		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}