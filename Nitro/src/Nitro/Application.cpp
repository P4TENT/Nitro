#include "ngpch.h"
#include "Application.h"

#include "Log.h"

#include "Renderer/Renderer.h"

namespace Nitro {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		NG_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);

		//----ONLY-FOR-TEST-------------------
		float verts[3 * 3] = {
			-0.5f, -0.5f, 0.f,
			 0.5f, -0.5f, 0.f,
			 0.0f,  0.5f, 0.f
		};
		uint32_t indices[3] = { 0, 1, 2 };

		m_VertexBuffer.reset(VertexBuffer::Create(verts, sizeof(verts)));
		m_VertexArray.reset(VertexArray::Create());

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"}
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSource = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;

out vec3 v_Position;

void main()
{
	gl_Position = vec4(a_Position - 0.5, 1.0);
	v_Position = a_Position;
}
)";

		std::string fragmentSource = R"(
#version 330 core

layout(location = 0) out vec4 color;

in vec3 v_Position;

void main()
{
	color = vec4(v_Position * 0.5 + 0.3, 1.0);
}
)";

		m_Shader.reset(new Shader(vertexSource, fragmentSource));
		 
		//----ONLY-FOR-TEST-------------------
	}

	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); )
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}

	void Application::Run()
	{
		while (m_Running)
		{
			//glClearColor(0.2f, 0.2f, 0.2f, 1);
			//glClear(GL_COLOR_BUFFER_BIT);

			RendererCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
			RendererCommand::Clear();

			Renderer::BeginScene();

			m_Shader->Bind();
			Renderer::Submit(m_VertexArray);

			Renderer::EndScene();

			//m_Shader->Bind();
			//m_VertexArray->Bind();
			//glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_ImGuiLayer->Begin();
			for (Layer* layer : m_LayerStack)
				layer->OnImGuiRender();
			m_ImGuiLayer->End();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}