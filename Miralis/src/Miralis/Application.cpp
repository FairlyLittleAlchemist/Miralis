#include "Application.h"
#include "Log.h"
#include <iostream>
#include<iostream>

namespace Miralis {
	Application* Application::s_Instance = nullptr;
	Application::Application() {
		s_Instance = this;
		Miralis::Log::Init();
		m_Window = std::unique_ptr<Window> (Window::Create());
		m_Window->SetEventClassBack(std::bind(&Application::OnEvent, this, std::placeholders::_1));
	};
	void Application::Run()
	{
		while(m_Running){
		for (Layer* layer : m_LayerStack) {
			layer->OnUpdate();
		}
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
	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.pushLayer(layer);
		layer->OnAttache();
	}
	void Application::PopLayer(Layer* layer)
	{
		m_LayerStack.popLayer(layer);

	}
	;


	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindwClose, this, std::placeholders::_1));
		MR_LOG_CORE_INFO(e.ToString())
			for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
				(*--it)->OnEvent(e);
				if (e.Handeld) {
					break;
				}
			}
	}
}