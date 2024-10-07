#pragma once
#include"Core.h"
#include<memory>
#include"Window.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
namespace Miralis{
class MIRALIS_API Application
{
public:
	Application();
	void OnEvent(Event& e);
	void Run();
	~Application();
	bool OnWindwClose(WindowCloseEvent& e);
private:
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
};

 Application* CreateApplication();

}

