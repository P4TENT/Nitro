#pragma once

#include "RendererCommand.h"

#include "OrthographicCamera.h"
#include "Shader.h"

namespace Nitro {

	class Renderer 
	{
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray, const std::shared_ptr<Shader>& shader);

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}