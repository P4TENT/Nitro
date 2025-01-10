#include "ngpch.h"
#include "Application.h"

#include "Log.h"

#include <glad/glad.h>

namespace Nitro {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
		case ShaderDataType::Bool:		return GL_BOOL;

		case ShaderDataType::Int:		return GL_INT;
		case ShaderDataType::Int2:		return GL_INT;
		case ShaderDataType::Int3:		return GL_INT;
		case ShaderDataType::Int4:		return GL_INT;

		case ShaderDataType::Float:		return GL_FLOAT;
		case ShaderDataType::Float2:	return GL_FLOAT;
		case ShaderDataType::Float3:	return GL_FLOAT;
		case ShaderDataType::Float4:	return GL_FLOAT;

		case ShaderDataType::Mat3:		return GL_FLOAT;
		case ShaderDataType::Mat4:		return GL_FLOAT;
		}

		NG_CORE_ASSERT(false, "Unknown ShaderDataType!");
	}

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

		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		m_VertexBuffer.reset(VertexBuffer::Create(verts, sizeof(verts)));

		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"}
		};

		m_VertexBuffer->SetLayout(layout);

		int index = 0;
		for (const auto& element : m_VertexBuffer->GetLayout())
		{
		glEnableVertexAttribArray(index);
		
		glVertexAttribPointer(index, 
			element.GetComponentCount(), 
			ShaderDataTypeToOpenGLBaseType(element.Type), 
			element.Normalized ? GL_TRUE : GL_FALSE, 
			layout.GetStride(), 
			(const void*)element.Offset);

		index++;
		}

		m_IndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

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
			glClearColor(0.2f, 0.2f, 0.2f, 1);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Shader->Bind();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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