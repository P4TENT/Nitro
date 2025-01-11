#pragma once

#include "Nitro/Renderer/Shader.h"
#include <glm/glm.hpp>

namespace Nitro {
	class OpenGLShader : public Shader
	{
	public:
		OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
		virtual ~OpenGLShader() override;

		virtual void Bind() override;
		virtual void Unbind() override;

		void UploadUniformMat4	(const std::string& name, const glm::mat4&	matrix);
		void UploadUniformMat3	(const std::string& name, const glm::mat3&	matrix);
		void UploadUniformFloat4(const std::string& name, const glm::vec4&	value);
		void UploadUniformFloat3(const std::string& name, const glm::vec3&	value);
		void UploadUniformFloat2(const std::string& name, const glm::vec2&	value);
		void UploadUniformFloat	(const std::string& name, const float		value);
		void UploadUniformInt	(const std::string& name,		int			value);

	private:
		uint32_t m_RendererID;
	};
}