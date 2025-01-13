#include "ngpch.h"

#include "Platform/OpenGL/OpenGLBuffer.h"
#include "Renderer.h"

namespace Nitro {

	VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NG_CORE_ASSERT(false, "Nitro::VertexBuffer::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return new OpenGLVertexBuffer(vertices, size);

		}

		NG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}

	IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count)
	{
		switch (Renderer::GetAPI())
		{
		case RenderAPI::API::None:			NG_CORE_ASSERT(false, "Nitro::IndexBuffer::Create(): 'RenderAPI::None' is currently not supported!");
		case RenderAPI::API::OpenGL:		return new OpenGLIndexBuffer(indices, count);

		}

		NG_CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}