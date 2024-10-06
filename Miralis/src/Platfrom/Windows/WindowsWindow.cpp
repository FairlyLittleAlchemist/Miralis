#include "WindowsWindow.h"

namespace Miralis{
	static bool s_GLFWInilized = false;
	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

WindowsWindow::WindowsWindow(const WindowProps& props){
	Init(props);
}

WindowsWindow::~WindowsWindow(){
	ShutDown();
}

void WindowsWindow::OnUpdate(){
	glfwPollEvents();
	glfwSwapBuffers(m_Window);
}

void WindowsWindow::SetVSync(bool enabled){
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else {
		glfwSwapInterval(0);
	}
	m_Data.VSync = enabled;
}

void WindowsWindow::Init(const WindowProps& props){
	m_Data.Name = props.Name;
	m_Data.Hight = props.Hight;
	m_Data.Width = props.Width;
	if (!s_GLFWInilized) {
		int succses = glfwInit();
		MR_CORE_ASSERT(succses, "Shit whent wrong");
		s_GLFWInilized = true;
	}

	m_Window = glfwCreateWindow((int)props.Width, (int)props.Hight, m_Data.Name.c_str(), nullptr, nullptr);
	glfwMakeContextCurrent(m_Window);
	glfwSetWindowUserPointer(m_Window, &m_Data);
}

void WindowsWindow::ShutDown(){
	glfwDestroyWindow(m_Window);
}
}