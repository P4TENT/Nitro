#include "ngpch.h"

#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Nitro {

	OpenGLContext::OpenGLContext(GLFWwindow* windowHandle)
		: m_WindowHandle(windowHandle)
	{
		NG_CORE_ASSERT(windowHandle, "Nitro::OpenGLContext::OpenGLContext(): Window handle is null!!")
	}
	
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		NG_CORE_ASSERT(status, "Nitro::OpenGLContext::Init(): Failed to initialize Glad!");
	}
	
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}