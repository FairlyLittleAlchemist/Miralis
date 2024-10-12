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
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

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
	}
	void ImGuiLayer::OnDeAttache()
	{
	}
	void ImGuiLayer::OnUpdate()
	{
	}
	void ImGuiLayer::OnEvent(Event& event)
	{
	}
}