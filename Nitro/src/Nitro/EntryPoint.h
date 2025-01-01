#pragma once

#ifdef NG_PLATFORM_WINDOWS

extern Nitro::Application* Nitro::CreateApplication();

int main(int argc, char** argv) 
{
	auto app = Nitro::CreateApplication();
	app->Run();
	delete app;
}

#endif