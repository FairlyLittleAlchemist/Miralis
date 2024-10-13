#pragma once
#include"Core.h"
#include<memory>
#include"Window.h"
#include"Miralis/LayerStack.h"
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
	void PushLayer(Layer* layer);
	void PopLayer(Layer* layer);
private:
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
	static Application* s_Instance;
	LayerStack m_LayerStack;

};

 Application* CreateApplication();

}

