#include <Nitro.h>

class Sandbox : public Nitro::Application {
public:
	Sandbox() 
	{
	}
	~Sandbox() 
	{
	}
};

Nitro::Application* Nitro::CreateApplication()
{
	return new Sandbox();
}