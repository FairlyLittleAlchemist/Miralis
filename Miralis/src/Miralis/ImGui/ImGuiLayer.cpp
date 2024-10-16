#include "imgui.h"
#include "ImGuiLayer.h"
#include"Platfrom/Vulkan/ImGuiVulkanRenderer.h"
#include"Platfrom/Vulkan/ImGuiVulkanInit.h"
#include"Miralis/Application.h"
namespace Miralis {
	ImGuiLayer::ImGuiLayer(): Layer("GUI Lyaer")
	{
	}
	ImGuiLayer::~ImGuiLayer()
	{
	}
	void ImGuiLayer::OnAttache()
	{
        ImVector<const char*> extensions;
        uint32_t extensions_count = 0;
        const char** glfw_extensions = glfwGetRequiredInstanceExtensions(&extensions_count);
        for (uint32_t i = 0; i < extensions_count; i++)
            extensions.push_back(glfw_extensions[i]);
        SetupVulkan(extensions);
        Application& app = Application::Get();
        auto& window = dynamic_cast<Miralis::WindowsWindow&>(app.getWindow());

        // Create Window Surface
        VkSurfaceKHR surface;
        VkResult err = glfwCreateWindowSurface(g_Instance, getWindow(window), g_Allocator, &surface);
        check_vk_result(err);
        
        // Create Framebuffers
        int w, h;
        glfwGetFramebufferSize(getWindow(window), &w, &h);
        ImGui_ImplVulkanH_Window* wd = &g_MainWindowData;
        SetupVulkanWindow(wd, surface, w, h);

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |=ImGuiBackendFlags_HasMouseCursors ;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
        


        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        ImGui_ImplVulkan_InitInfo init_info = {};
        init_info.Instance = g_Instance;
        init_info.PhysicalDevice = g_PhysicalDevice;
        init_info.Device = g_Device;
        init_info.QueueFamily = g_QueueFamily;
        init_info.Queue = g_Queue;
        init_info.PipelineCache = g_PipelineCache;
        init_info.DescriptorPool = g_DescriptorPool;
        init_info.RenderPass = wd->RenderPass;
        init_info.Subpass = 0;
        init_info.MinImageCount = g_MinImageCount;
        init_info.ImageCount = wd->ImageCount;
        init_info.MSAASamples = VK_SAMPLE_COUNT_1_BIT;
        init_info.Allocator = g_Allocator;
        init_info.CheckVkResultFn = check_vk_result;
        ImGui_ImplVulkan_Init(&init_info);

        MR_LOG_CLIENT_TRACE("Render Start");
	}
	void ImGuiLayer::OnDeAttache()
	{

 
	}
	void ImGuiLayer::OnUpdate()
	{


     
        ImGuiIO& io = ImGui::GetIO();
        Application& app = Application::Get();
        auto& window = dynamic_cast<Miralis::WindowsWindow&>(app.getWindow());
        io.DisplaySize = ImVec2(window.getWidth() , window.getHiegt());
        float time = (float)glfwGetTime();
        io.DeltaTime = m_Time > 0.0 ? (time - m_Time) : (1.0f / 120.0f);
        m_Time = time;
        ImGui_ImplVulkan_NewFrame();
        ImGui::NewFrame();
     
        static bool show = true;
        ImGui::ShowDemoWindow(&show);
        ImGui::Render();

        ImGui_ImplVulkanH_Window* wd = &g_MainWindowData;
        ImDrawData* draw_data = ImGui::GetDrawData();
        FrameRender(wd, draw_data);
        FramePresent(wd);
	}

    void ImGuiLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::OnMouseButtonPressed, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseButtonRealsedssedEvent>(std::bind(&ImGuiLayer::OnMouseButtonRealsed, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::OnMouseMove, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&ImGuiLayer::OnMouseScroll, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyPressedEvent>(std::bind(&ImGuiLayer::OnKeyPressed, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&ImGuiLayer::OnKeyRealsed, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&ImGuiLayer::OnWindowResize, this, std::placeholders::_1));


    }

    bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.getMouseButton()] = true;
        return false;
    }

    bool ImGuiLayer::OnMouseButtonRealsed(MouseButtonRealsedssedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[e.getMouseButton()] = false;
        return false;
    }

    bool ImGuiLayer::OnMouseMove(MouseMovedEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(e.GetX(), e.GetY());

        return false;
    }

    bool ImGuiLayer::OnMouseScroll(MouseScrolledEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += e.GetXOffest();
        io.MouseWheel += e.GetYOffest();
        return false;
    }

    bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& e)
    {
        MR_LOG_CORE_INFO("KeyPressed {0}", e.ToString())
       ImGuiIO& io = ImGui::GetIO();
       io.KeysDown[e.getKeyCode()] = true;

        return false;
    }

    bool ImGuiLayer::OnKeyRealsed(KeyReleasedEvent& e)
    {
        MR_LOG_CORE_INFO("KeyRealsed {0}", e.ToString())

        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[e.getKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(e.getWidth(), e.getHight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        ImGui_ImplVulkan_SetMinImageCount(g_MinImageCount);
        ImGui_ImplVulkanH_CreateOrResizeWindow(g_Instance, g_PhysicalDevice, g_Device, &g_MainWindowData, g_QueueFamily, g_Allocator, e.getWidth(), e.getHight(), g_MinImageCount);
        g_MainWindowData.FrameIndex = 0;
        g_SwapChainRebuild = false;
        return false;
    }

}