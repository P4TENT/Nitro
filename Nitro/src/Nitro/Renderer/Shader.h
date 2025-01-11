#pragma once

#include <string>

#include <glm/glm.hpp>

namespace Nitro {
	class Shader
	{
	public:
		Shader(const std::string& vertexSource, const std::string& fragmentSource);
		~Shader();

		void Bind();
		void Unbind();

		void UploadUniformMat4(const std::string& name, const glm::mat4& matrix);
		void UploadUniformFloat4(const std::string& name, const glm::vec4& floats);
	
	private:
		uint32_t m_RendererID;
	};
}