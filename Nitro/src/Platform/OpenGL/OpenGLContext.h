#pragma once

#include "Nitro/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Nitro {
	class OpenGLContext : public GraphicsContext
	{
	private:
		GLFWwindow* m_WindowHandle;

	public:
		OpenGLContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void SwapBuffers() override;
	};
}