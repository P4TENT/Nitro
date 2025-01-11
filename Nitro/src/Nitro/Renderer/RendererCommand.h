#pragma once

#include "VertexArray.h"
#include "RenderAPI.h"

namespace Nitro {
	enum class RendererAPI
	{
		None = 0, OpenGL = 1
	};

	class RendererCommand	
	{
	public:

		inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}
			
		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) 
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static RenderAPI* s_RendererAPI;
	};

}