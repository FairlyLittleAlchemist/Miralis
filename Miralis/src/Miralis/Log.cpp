#include "Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"
namespace Miralis {
	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_ClientLogger;

	void Log::Init() {
		//TODO Make this Use THE SPD_LOG Macro
		//spdlog::set_pattern("[%H:%M:%S.%e] [Level:%l] [%s:%#][%!] %n: %v%$");

		spdlog::set_pattern("[%H:%M:%S.%e] [TheardId:%t]  %n : %v%$");
		s_CoreLogger = spdlog::stdout_color_mt("Core Logging");
		s_CoreLogger->set_level(spdlog::level::trace);

		s_ClientLogger = spdlog::stdout_color_mt("Application Logging");
		s_ClientLogger->set_level(spdlog::level::trace);
	}
}