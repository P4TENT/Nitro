#include "ngpch.h"

#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Nitro {
	Shader* Shader::Create(const std::string& vertexSource, const std::string& fragmentSource)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NG_CORE_ASSERT(false, "Nitro::Shader::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return new OpenGLShader(vertexSource, fragmentSource);

		}

		NG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}