#include <Nitro.h>

#include <imgui.h>

class ExampleLayer : public Nitro::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPos(glm::vec3(0.f))
	{
		float verts[3 * 3] = {
			-0.5f, -0.5f, 0.f,
			 0.5f, -0.5f, 0.f,
			 0.0f,  0.5f, 0.f
		};
		uint32_t indices[3] = { 0, 1, 2 };

		m_VertexBuffer.reset(Nitro::VertexBuffer::Create(verts, sizeof(verts)));
		m_VertexArray.reset(Nitro::VertexArray::Create());

		Nitro::BufferLayout layout = {
			{Nitro::ShaderDataType::Float3, "a_Position"}
		};

		m_VertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(m_VertexBuffer);

		m_IndexBuffer.reset(Nitro::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(m_IndexBuffer);

		std::string vertexSource = R"(
#version 330 core

layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;

out vec3 v_Position;

void main()
{
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
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

		m_Shader.reset(new Nitro::Shader(vertexSource, fragmentSource));
	}

	void OnUpdate() override
	{
		if (Nitro::Input::IsKeyPressed(N_KEY_A))
			m_CameraPos.x -= 0.05f;
		if (Nitro::Input::IsKeyPressed(N_KEY_D))
			m_CameraPos.x += 0.05f;
		if (Nitro::Input::IsKeyPressed(N_KEY_S))
			m_CameraPos.y -= 0.05f;
		if (Nitro::Input::IsKeyPressed(N_KEY_W))
			m_CameraPos.y += 0.05f;

		Nitro::RendererCommand::SetClearColor({ 0.2f, 0.2f, 0.2f, 1 });
		Nitro::RendererCommand::Clear();

		m_Camera.SetPosition(m_CameraPos);

		Nitro::Renderer::BeginScene(m_Camera);

		Nitro::Renderer::Submit(m_VertexArray, m_Shader);

		Nitro::Renderer::EndScene();
	}

	void OnImGuiRender() override
	{

	}

	void OnEvent(Nitro::Event& event) override
	{
	}

private:
	std::shared_ptr<Nitro::VertexBuffer> m_VertexBuffer;
	std::shared_ptr<Nitro::IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Nitro::VertexArray> m_VertexArray;
	std::shared_ptr<Nitro::Shader> m_Shader;

	Nitro::OrthographicCamera m_Camera;

	glm::vec3 m_CameraPos;

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