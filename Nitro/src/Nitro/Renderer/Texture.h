#pragma once

#include <string>
#include "Nitro/Core/Core.h"

namespace Nitro {

	// BASE CLASS FOR THE OTHER TEXTURE CLASSES !!! NOT FOR USE !!!
	class Texture
	{
	public:
		virtual ~Texture() = default;

		virtual void Bind(uint32_t slot = 0) const = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;
	};

	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> Create(const std::string& file_path);
	};

}