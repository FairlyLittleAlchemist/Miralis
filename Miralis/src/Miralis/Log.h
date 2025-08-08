#pragma once

#include"Miralis/Core.h"
#include <spdlog/spdlog.h>
#include <spdlog/fmt/fmt.h>
#include <spdlog/fmt/ostr.h>

namespace Miralis {
	class MIRALIS_API Log
	{
	public: 
		static void Init();
		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

#if MR_DEBUG
#define MR_LOG_CORE_INFO(...) ::Miralis::Log::GetCoreLogger()->info(__VA_ARGS__);
#define MR_LOG_CORE_ERROR(...) ::Miralis::Log::GetCoreLogger()->error(__VA_ARGS__);
#define MR_LOG_CORE_WARN(...) ::Miralis::Log::GetCoreLogger()->warn(__VA_ARGS__);
#define MR_LOG_CORE_CRITICAL(...) ::Miralis::Log::GetCoreLogger()->critical(__VA_ARGS__);
#define MR_LOG_CORE_DEBUG(...) ::Miralis::Log::GetCoreLogger()->debug(__VA_ARGS__);
#define MR_LOG_CORE_TRACE(...) ::Miralis::Log::GetCoreLogger()->trace(__VA_ARGS__);

#define MR_LOG_CLIENT_INFO(...) ::Miralis::Log::GetClientLogger()->info(__VA_ARGS__);
#define MR_LOG_CLIENT_ERROR(...) ::Miralis::Log::GetClientLogger()->error(__VA_ARGS__);
#define MR_LOG_CLIENT_WARN(...) ::Miralis::Log::GetClientLogger()->warn(__VA_ARGS__);
#define MR_LOG_CLIENT_CRITICAL(...) ::Miralis::Log::GetClientLogger()->critical(__VA_ARGS__);
#define MR_LOG_CLIENT_DEBUG(...) ::Miralis::Log::GetClientLogger()->debug(__VA_ARGS__);
#define MR_LOG_CLIENT_TRACE(...) ::Miralis::Log::GetClientLogger()->trace(__VA_ARGS__);
#else


#define MR_LOG_CORE_INFO(...)
#define MR_LOG_CORE_ERROR(...)
#define MR_LOG_CORE_WARN(...) 
#define MR_LOG_CORE_CRITICAL(...) 
#define MR_LOG_CORE_DEBUG(...) 
#define MR_LOG_CORE_TRACE(...) 

#define MR_LOG_CLIENT_INFO(...)
#define MR_LOG_CLIENT_ERROR(...) 
#define MR_LOG_CLIENT_WARN(...) 
#define MR_LOG_CLIENT_CRITICAL(...) 
#define MR_LOG_CLIENT_DEBUG(...) 
#define MR_LOG_CLIENT_TRACE(...) 
#endif