#pragma once

#include <string>

namespace Nitro {
	class Shader
	{
	public:
		virtual ~Shader() = default;

		virtual void Bind() = 0;
		virtual void Unbind() = 0;

		static Shader* Create(const std::string& vertexSource, const std::string& fragmentSource);
	};
}