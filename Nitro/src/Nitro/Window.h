#pragma once

#include "ngpch.h"

#include "Core.h"
#include "Events/Event.h"

namespace Nitro {
	struct WindowProps {
		std::string Title;
		NGUINT Width;
		NGUINT Height;

		WindowProps(const std::string& title = "Nitrogen Engine", NGUINT width = 1280, NGUINT height = 720)
			: Title(title), Width(width), Height(height) {}
	};
	
	class Window 
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>;

		virtual ~Window() {}

		virtual void OnUpdate() = 0;

		virtual NGUINT GetWidth() const = 0;
		virtual NGUINT GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		virtual void* GetNativeWindow() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}