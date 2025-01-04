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
		if (Nitro::Input::IsKeyPressed(N_KEY_TAB))
			NG_CLIENT_TRACE("Tab Key Pressed! (update)");
	}

	void OnEvent(Nitro::Event& event) override
	{

	}

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