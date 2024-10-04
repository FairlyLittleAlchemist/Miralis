#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "Application.h"
#include "Log.h"
#include <iostream>
namespace Miralis {
	Application::Application() {
		Miralis::Log::Init();
		MR_LOG_CLIENT_INFO("Hellow");
	};
	void Application::Run()
	{
	};
	Application::~Application() {
	};
}