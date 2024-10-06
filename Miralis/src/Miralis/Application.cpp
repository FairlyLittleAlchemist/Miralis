#define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_TRACE
#include "Application.h"
#include "Log.h"
#include <iostream>
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "GLFW/glfw3.h"

namespace Miralis {
	Application::Application() {
		Miralis::Log::Init();
		m_Window = std::unique_ptr<Window> (Window::Create());
		MR_LOG_CORE_WARN("Application Warn")
	};
	void Application::Run()
	{
		while (true) {
			m_Window->OnUpdate();
		}
	};
	Application::~Application() {
	};
}