#include <Nitro.h>

#include <imgui.h>

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

	void OnImGuiRender() override
	{
		ImGui::Begin("Test");
		ImGui::Text("Hello, World!");
		ImGui::End();
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