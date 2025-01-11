#include <Nitro.h>

#include "Platform/OpenGL/OpenGLShader.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <imgui.h>

class ExampleLayer : public Nitro::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(glm::vec3(0.f))
	{
		m_VertexArray.reset(Nitro::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
		};

		Nitro::Ref<Nitro::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Nitro::VertexBuffer::Create(vertices, sizeof(vertices)));
		Nitro::BufferLayout layout = {
			{ Nitro::ShaderDataType::Float3, "a_Position" },
			{ Nitro::ShaderDataType::Float4, "a_Color" }
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		uint32_t indices[3] = { 0, 1, 2 };
		Nitro::Ref<Nitro::IndexBuffer> indexBuffer;
		indexBuffer.reset(Nitro::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Nitro::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		Nitro::Ref<Nitro::VertexBuffer> squareVB;
		squareVB.reset(Nitro::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
		squareVB->SetLayout({
			{ Nitro::ShaderDataType::Float3, "a_Position" }
			});
		m_SquareVA->AddVertexBuffer(squareVB);

		uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		Nitro::Ref<Nitro::IndexBuffer> squareIB;
		squareIB.reset(Nitro::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);

		std::string vertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(Nitro::Shader::Create(vertexSrc, fragmentSrc));

		std::string ColorShaderVertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);	
			}
		)";

		std::string ColorShaderFragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";

		m_ColorShader.reset(Nitro::Shader::Create(ColorShaderVertexSrc, ColorShaderFragmentSrc));
	}

	void OnUpdate(Nitro::Timestep deltaT) override
	{
		if (Nitro::Input::IsKeyPressed(N_KEY_A))
			m_CameraPosition.x -= m_CameraMoveSpeed * deltaT;
		else if (Nitro::Input::IsKeyPressed(N_KEY_D))
			m_CameraPosition.x += m_CameraMoveSpeed * deltaT;

		if (Nitro::Input::IsKeyPressed(N_KEY_W))
			m_CameraPosition.y += m_CameraMoveSpeed * deltaT;
		else if (Nitro::Input::IsKeyPressed(N_KEY_S))
			m_CameraPosition.y -= m_CameraMoveSpeed * deltaT;

		if (Nitro::Input::IsKeyPressed(N_KEY_Q))
			m_CameraRotation += m_CameraRotationSpeed * deltaT;
		if (Nitro::Input::IsKeyPressed(N_KEY_E))
			m_CameraRotation -= m_CameraRotationSpeed * deltaT;

		Nitro::RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Nitro::RendererCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Nitro::Renderer::BeginScene(m_Camera);

		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));

		std::dynamic_pointer_cast<Nitro::OpenGLShader>(m_ColorShader)->Bind();
		std::dynamic_pointer_cast<Nitro::OpenGLShader>(m_ColorShader)->UploadUniformFloat4("u_Color", m_SquareColor);

		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				Nitro::Renderer::Submit(m_SquareVA, m_ColorShader, transform);
			}
		}

		Nitro::Renderer::Submit(m_VertexArray, m_Shader);

		Nitro::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{
		// Color Test With ImGui!
		ImGui::Begin("Test Settings");
		ImGui::ColorEdit4("Square Color: ", glm::value_ptr(m_SquareColor));
		ImGui::End();

	}

	void OnEvent(Nitro::Event& event) override
	{
	}

private:
	Nitro::Ref<Nitro::Shader> m_Shader;
	Nitro::Ref<Nitro::VertexArray> m_VertexArray;

	Nitro::Ref<Nitro::Shader> m_ColorShader;
	Nitro::Ref<Nitro::VertexArray> m_SquareVA;

	Nitro::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraMoveSpeed = 5.0f;

	float m_CameraRotation = 0.0f;
	float m_CameraRotationSpeed = 180.0f;

	glm::vec4 m_SquareColor = { 0.2f, 0.3f, 0.8f, 1.f };
};

class Sandbox : public Nitro::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Nitro::Application* Nitro::CreateApplication()
{
	return new Sandbox();
}