#pragma once

#include "Nitro/Renderer/RenderAPI.h"

namespace Nitro {

	class OpenGLRendererAPI : public RenderAPI
	{
	public:
		virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) override;
	};
}