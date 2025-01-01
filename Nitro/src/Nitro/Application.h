#pragma once

#include "Core.h"

namespace Nitro {

	class NITRO_API Application
	{
	public:
		Application();
		virtual ~Application();
		void Run();
	}; 

	// To be defined in client
	Application* CreateApplication();

}