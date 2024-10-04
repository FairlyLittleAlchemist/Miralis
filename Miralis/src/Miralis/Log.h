#pragma once

#include"Miralis/Core.h"
#include <spdlog/spdlog.h>
#include "spdlog/fmt/ostr.h"
// Note: Warning C4251 is safe to ignore here because s_CoreLogger and s_ClientLogger 
// are private static members and won't be accessed directly across DLL boundaries.
#pragma warning(push)
#pragma warning(disable : 4251)
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
#pragma warning(pop)
//Core Logger

#if MR_DEBUG



#define MR_LOG_CORE_INFO(__Params__) ::Miralis::Log::GetCoreLogger()->info(__Params__);

#define MR_LOG_CORE_ERROR(__Params__) ::Miralis::Log::GetCoreLogger()->error(__Params__);

#define MR_LOG_CORE_WARN(__Params__) ::Miralis::Log::GetCoreLogger()->warn(__Params__);

#define MR_LOG_CORE_CRITICAL(__Params__) ::Miralis::Log::GetCoreLogger()->critical(__Params__);

#define MR_LOG_CORE_DEBUG(__Params__) ::Miralis::Log::GetCoreLogger()->debug(__Params__);

#define MR_LOG_CORE_TRACE(__Params__) ::Miralis::Log::GetCoreLogger()->trace(__Params__);



//Clinet Logger

#define MR_LOG_CLIENT_INFO(__Params__) ::Miralis::Log::GetClientLogger()->info(__Params__);

#define MR_LOG_CLIENT_ERROR(__Params__) ::Miralis::Log::GetClientLogger()->error(__Params__);

#define MR_LOG_CLIENT_WARN(__Params__) ::Miralis::Log::GetClientLogger()->warn(__Params__);

#define MR_LOG_CLIENT_CRITICAL(__Params__) ::Miralis::Log::GetClientLogger()->critical(__Params__);

#define MR_LOG_CLIENT_DEBUG(__Params__) ::Miralis::Log::GetClientLogger()->debug(__Params__);

#define MR_LOG_CLIENT_TRACE(__Params__) ::Miralis::Log::GetClientLogger()->trace(__Params__);



#else

#define MR_LOG_CORE_ERROR(__Params__)

#define MR_LOG_CORE_WARN(__Params__) 

#define MR_LOG_CORE_CRITICAL(__Params__) 

#define MR_LOG_CORE_DEBUG(__Params__) 

#define MR_LOG_CORE_TRACE(__Params__) 



//Clinet Logger

#define MR_LOG_CLIENT_INFO(__Params__)

#define MR_LOGCLIENT_ERROR(__Params__) 

#define MR_LOGCLIENT_WARN(__Params__) 

#define MR_LOGCLIENT_CRITICAL(__Params__) 

#define MR_LOGCLIENT_DEBUG(__Params__) 

#define MR_LOGCLIENT_TRACE(__Params__) 

#endif