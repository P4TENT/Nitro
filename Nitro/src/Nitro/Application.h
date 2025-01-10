#pragma once

#include "Core.h"

#include "Window.h"
#include "Nitro/LayerStack.h"
#include "Nitro/Events/Event.h"
#include "Nitro/Events/AppEvent.h"

#include "Nitro/ImGui/ImGuiLayer.h"

#include "Nitro/Renderer/Shader.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace Nitro {

	class Application
	{
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
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int VAO;

		std::unique_ptr<VertexBuffer> m_VertexBuffer;
		std::unique_ptr<IndexBuffer> m_IndexBuffer;

		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication();

}