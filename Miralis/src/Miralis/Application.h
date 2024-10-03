#pragma once
#include"Core.h"

namespace Miralis{
class MIRALIS_API Application
{
public:
	Application();

	void Run();
	~Application();
};

 Application* CreateApplication();

}

