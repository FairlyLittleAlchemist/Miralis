#include "Application.h"
#include "Log.h"
#include <iostream>


namespace Miralis {
	Application::Application() {
		Miralis::Log::Init();
		m_Window = std::unique_ptr<Window> (Window::Create());
		m_Window->SetEventClassBack(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	};
	void Application::Run()
	{
		while (m_Running) {
			m_Window->OnUpdate();
		}
	};
	Application::~Application() {
	}
	bool Application::OnWindwClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}
	;


	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindwClose, this, std::placeholders::_1));

	}
}