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
	inline  Window& getWindow() { return *m_Window; };
	inline static Application& Get() { return *s_Instance; };
	
private:
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
	static Application* s_Instance;

};

 Application* CreateApplication();

}

