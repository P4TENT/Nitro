#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Nitro {
	class Log
	{
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	};
}

// CORE LOG MACROS
#define NG_CORE_FATAL(...)      ::Nitro::Log::GetCoreLogger()->critical(__VA_ARGS__)
#define NG_CORE_ERROR(...)      ::Nitro::Log::GetCoreLogger()->error(__VA_ARGS__)
#define NG_CORE_WARN(...)       ::Nitro::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define NG_CORE_INFO(...)       ::Nitro::Log::GetCoreLogger()->info(__VA_ARGS__)
#define NG_CORE_TRACE(...)      ::Nitro::Log::GetCoreLogger()->trace(__VA_ARGS__)

// CLIENT LOG MACROS
#define NG_CLIENT_FATAL(...)    ::Nitro::Log::GetClientLogger()->critical(__VA_ARGS__)
#define NG_CLIENT_ERROR(...)    ::Nitro::Log::GetClientLogger()->error(__VA_ARGS__)
#define NG_CLIENT_WARN(...)     ::Nitro::Log::GetClientLogger()->warn(__VA_ARGS__)
#define NG_CLIENT_INFO(...)     ::Nitro::Log::GetClientLogger()->info(__VA_ARGS__)
#define NG_CLIENT_TRACE(...)    ::Nitro::Log::GetClientLogger()->trace(__VA_ARGS__)