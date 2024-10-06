#pragma once
#include"Core.h"
#include<memory>
#include"Window.h"
namespace Miralis{
class MIRALIS_API Application
{
public:
	Application();

	void Run();
	~Application();
private:
	std::unique_ptr<Window> m_Window;
};

 Application* CreateApplication();

}

