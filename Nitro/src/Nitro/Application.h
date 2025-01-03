#pragma once

#include "Core.h"
#include "LayerStack.h"
#include "Events/Event.h"
#include "Events/AppEvent.h"
#include "Window.h"

namespace Nitro {

	class NITRO_API Application
	{
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	public:
		Application();
		virtual ~Application();
		
		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline Window& GetWindow() { return *m_Window; }
		inline static Application& Get() { return *s_Instance; }

	private:
		LayerStack m_LayerStack;
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;	
		static Application* s_Instance;
	}; 

	// To be defined in client
	Application* CreateApplication();

}