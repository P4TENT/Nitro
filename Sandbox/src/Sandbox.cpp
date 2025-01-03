#include <Nitro.h>

class ExampleLayer : public Nitro::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}

	void OnUpdate() override
	{
		NG_CORE_INFO("ExampleLayer::Update");
	}

	void OnEvent(Nitro::Event& event) override
	{
		NG_CORE_TRACE("{0}", event.ToString());
	}

};

class Sandbox : public Nitro::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Nitro::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Nitro::Application* Nitro::CreateApplication()
{
	return new Sandbox();
}