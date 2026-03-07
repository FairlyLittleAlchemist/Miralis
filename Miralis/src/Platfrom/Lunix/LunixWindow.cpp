#include "LunixWindow.h"

#include "Miralis/Events/Event.h"
#include "Miralis/Events/ApplicationEvent.h"
#include "Miralis/Events/KeyEvent.h"
#include "Miralis/Events/MouseEvent.h"
#include "Platfrom/Vulkan/VulkanContext.h"
#include <memory>
namespace Miralis{
std::unique_ptr<Miralis::GraphicsContext> Miralis::Window::m_Context;
static bool s_GLFWInilized = false;
Window* Window::Create(const WindowProps& props) {

		return new LunixWindow(props);
}

static void GlfwErrorCallBack(int error_code, const char* description) {
	MR_LOG_CORE_ERROR("Code:{0} Description:{1}", error_code , description)
};

LunixWindow::LunixWindow(const WindowProps& props){


	Init(props);
}

LunixWindow::~LunixWindow(){
	
	ShutDown();
}

void LunixWindow::OnUpdate(){
	glfwPollEvents();
}

void LunixWindow::NewFrame()
{
	m_Context->ImGUINewFrame();
}

void LunixWindow::SetVSync(bool enabled){
	if (enabled)
	{
		glfwSwapInterval(1);
	}
	else {
		glfwSwapInterval(0);
	}
	m_Data.VSync = enabled;
}

void LunixWindow::Init(const WindowProps& props){
	glfwInitHint(GLFW_PLATFORM, GLFW_PLATFORM_X11);

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
	int fbWidth, fbHeight;

	int platform = glfwGetPlatform();
	if (platform == GLFW_PLATFORM_X11) {
		MR_LOG_CORE_DEBUG("x11");
	}

	if (platform == GLFW_PLATFORM_WAYLAND) {
		MR_LOG_CORE_DEBUG("Wayland");
	}



	glfwGetFramebufferSize(m_Window, &fbWidth, &fbHeight);
	m_Data.Width = fbWidth;
	m_Data.Hight = fbHeight;
	m_Props = props;
	m_Props.Width = fbWidth;
	m_Props.Hight = fbHeight;
	m_Context = std::make_unique<VulkanContext>(&m_Props, m_Window);
	const char* session = getenv("XDG_SESSION_TYPE");
	MR_LOG_CORE_INFO("Session type: {0}", session ? session : "unknown");
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
		VulkanContext* ctx = static_cast<VulkanContext*>(Window::m_Context.get());
		ctx->m_props->Width = width;   // update props!
		ctx->m_props->Hight = height;

		ctx->recreateSwapChain();

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

	void LunixWindow::ShutDown(){
		glfwDestroyWindow(m_Window);
	}
}