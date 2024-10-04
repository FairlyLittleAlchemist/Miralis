#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "Application.h"
#include "Log.h"
#include <iostream>
#include "Event.h"
#include "ApplicationEvent.h"


namespace Miralis {
	Application::Application() {
		Miralis::Log::Init();
		MR_LOG_CORE_WARN("Application Warn")
	};
	void Application::Run()
	{
	};
	Application::~Application() {
	};
}