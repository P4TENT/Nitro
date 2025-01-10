#include "ngpch.h"

#include "VertexArray.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace Nitro {
	VertexArray* VertexArray::Create()
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NG_CORE_ASSERT(false, "'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return new OpenGLVertexArray();

		}

		NG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}