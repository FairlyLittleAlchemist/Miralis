#include "Application.h"
#include<iostream>
namespace Miralis {
	Application::Application() {

	};
	void Application::Run()
	{
		std::cout << "Hi From DLL";
		while (true);
	};
	Application::~Application() {

	};
}