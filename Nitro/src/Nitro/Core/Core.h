#pragma once

#include <memory>

#define NGINT int
#define NGUINT unsigned int
#define NGUBYTE unsigned char

#define NG_ENABLE_ASSERTS

#ifdef NG_PLATFORM_WINDOWS

#if NG_DYNAMIC_LINK
	#ifdef NG_BUILD_DLL
		#define NITRO_API __declspec(dllexport)
	#else 
		#define NITRO_API __declspec(dllimport)
	#endif
#else
	#define NITRO_API
#endif

#else 
	#error Nitro only supports Windows!!
#endif

#ifdef NG_ENABLE_ASSERTS
	#define NG_ASSERT(x, ...) { if(!(x)) { NG_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NG_CORE_ASSERT(x, ...) { if(!(x)) { NG_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NG_ASSERT(x, ...)
	#define NG_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define NG_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Nitro {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref	= std::shared_ptr<T>;
}