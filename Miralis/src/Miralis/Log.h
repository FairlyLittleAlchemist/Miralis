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



