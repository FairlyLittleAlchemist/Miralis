#include "WindowsWindow.h"
#include "Miralis/Events/Event.h"
#include "Miralis/Events/ApplicationEvent.h"
#include "Miralis/Events/KeyEvent.h"
#include "Miralis/Events/MouseEvent.h"
namespace Miralis{
static bool s_GLFWInilized = false;
Window* Window::Create(const WindowProps& props) {

		return new WindowsWindow(props);
}

static void GlfwErrorCallBack(int error_code, const char* description) {
	MR_LOG_CORE_ERROR("Code:{0} Description:{1}", error_code , description)
};

WindowsWindow::WindowsWindow(const WindowProps& props){
	Init(props);
}

WindowsWindow::~WindowsWindow(){
	ShutDown();
}

void WindowsWindow::OnUpdate(){
	glfwPollEvents();
	
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
		s_GLFWInilized = true;
		glfwSetErrorCallback(GlfwErrorCallBack);
	}
	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	m_Window = glfwCreateWindow((int)props.Width, (int)props.Hight, m_Data.Name.c_str(), nullptr, nullptr);
	glfwSetWindowUserPointer(m_Window, &m_Data);


	glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
		{
			windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
			MouseMovedEvent event((float)xPos, (float)yPos);
			data.EventCallBack(event);
		});

	glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window) {
		windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
		WindowCloseEvent event;
		data.EventCallBack(event);
		});
	glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods) {
		windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
		switch (action)
		{
		case GLFW_PRESS: {
			MouseButtonPressedEvent event(button);
			data.EventCallBack(event);
			break;
		}case GLFW_RELEASE: {
			MouseButtonRealsedssedEvent event(button);
			data.EventCallBack(event);
			break;
		}
		}
		});

	glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height) {
		windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
		WindowResizeEvent event(width, height);
		data.EventCallBack(event);
		});

	glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode) {
		windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
		KeyTypedEvent event(keycode);
		data.EventCallBack(event);
		});
	glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xoffset, double yoffset) {

		windowData& data = *(windowData*)glfwGetWindowUserPointer(window);
		MouseScrolledEvent event((float)xoffset, (float)yoffset);
		data.EventCallBack(event);
		});

	glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		windowData& data = *(windowData*)glfwGetWindowUserPointer(window);

		switch (action)
		{
		case GLFW_PRESS: {
			KeyPressedEvent event(key,0);
			data.EventCallBack(event);
			break;
		}case GLFW_REPEAT: {
			KeyPressedEvent event(key,1);
			data.EventCallBack(event);
			break;
		}case GLFW_RELEASE: {
			KeyReleasedEvent event(key);
			data.EventCallBack(event);
			break;
		}
		}
		});
}

void WindowsWindow::ShutDown(){
	glfwDestroyWindow(m_Window);
}
}