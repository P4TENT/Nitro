#pragma once

#ifdef NG_PLATFORM_WINDOWS

extern Nitro::Application* Nitro::CreateApplication();

int main(int argc, char** argv) 
{
	Nitro::Log::Init();
	NG_CORE_WARN("Initialized Log!");
	NG_CORE_WARN("Initialized Log2!");
	NG_CLIENT_INFO("Hello! var={0}", 6);

	auto app = Nitro::CreateApplication();
	app->Run();
	delete app;
}

#endif