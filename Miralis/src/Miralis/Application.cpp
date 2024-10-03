#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "Application.h"
#include "Log.h"
#include <iostream>
namespace Miralis {
	Application::Application() {
		Miralis::Log::Init();
		Miralis::Log::GetCoreLogger()->warn("This is wwarinig {}", 20);
	};
	void Application::Run()
	{
	};
	Application::~Application() {
	};
}