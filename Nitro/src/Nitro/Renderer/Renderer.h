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

		static void Init();

		static void Submit(const Ref<VertexArray>& vertexArray, const Ref<Shader>& shader, const glm::mat4& transform = glm::mat4(1.f));

		inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

	private:
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};

}