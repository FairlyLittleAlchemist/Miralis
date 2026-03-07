#pragma once
#define VK_USE_PLATFORM_WAYLAND_KHR

#include"Miralis/Rendering/GrapghicsContext.h"
#include"Miralis/Log.h"
#include"Miralis/Core.h"
#include <vulkan/vulkan.h>
#include <vector>
#include<iostream>
#include <optional>
#include <set>
#include <cstdint> 
#include <limits> 
#include <algorithm> 
#include "Miralis/Window.h"
#include "imgui.h"
#include "Platfrom/ImGUI/Vulkan/imgui_impl_vulkan.h"
#include "Platfrom/ImGUI/Window/imgui_impl_glfw.h"
 struct  GLFWwindow;
namespace Miralis {

	
	class VulkanContext : public GraphicsContext {
	public:


	
		VkDevice device;
		VkPhysicalDevice physicalDevice;
		VkInstance instance;
		std::vector<const char*> deviceExtensions;
		void* m_WindowHandel;
		VkQueue graphicsQueue;
		VkSurfaceKHR surface;
		VkQueue presentQueue;
		VkPipeline graphicsPipeline;
		VkCommandPool commandPool;
		std::vector<VkCommandBuffer> commandBuffers;

		VkSwapchainKHR swapChain;
		std::vector<VkImage> swapChainImages;
		std::vector<VkImageView> swapChainImageViews;
		VkPipelineLayout pipelineLayout;

		std::vector<VkSemaphore> imageAvailableSemaphores;
		std::vector<VkSemaphore> renderFinishedSemaphores;
		std::vector<VkFence> inFlightFences;
		VkRenderPass renderPass;
		VkFormat swapChainImageFormat;
		VkExtent2D swapChainExtent;
		std::vector<VkFramebuffer> swapChainFramebuffers;
		WindowProps* m_props;
		int MAX_FRAMES_IN_FLIGHT = 3;
		uint32_t currentFrame = 0;
		ImGui_ImplVulkanH_Window g_MainWindowData;
		void recreateSwapChain();
		uint32_t imageIndex;
		VkDescriptorPool descriptorPool;


	public :
		
		VulkanContext(  WindowProps* props, GLFWwindow* Window);
		~VulkanContext();
		virtual void Init() override;
		virtual void SwapBuffers() override;
		void ImGUINewFrame() override;

	private:
	#ifdef MR_DEBUG

		VkDebugUtilsMessengerEXT debugMessenger;

		std::vector<const char*> validationLayers = {
			 "VK_LAYER_KHRONOS_validation"

		};
		bool checkValidationLayerSupport() {
			uint32_t layerCount;
			vkEnumerateInstanceLayerProperties(&layerCount, nullptr);

			std::vector<VkLayerProperties> availableLayers(layerCount);
			vkEnumerateInstanceLayerProperties(&layerCount, availableLayers.data());

			for (const char* layerName : validationLayers) {
				bool layerFound = false;

				for (const auto& layerProperties : availableLayers) {
					if (strcmp(layerName, layerProperties.layerName) == 0) {
						layerFound = true;
						break;
					}
				}

				if (!layerFound) {
					return false;
				}
			}

			return true;
		}



		VkResult CreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugUtilsMessengerEXT* pDebugMessenger) {
			auto func = (PFN_vkCreateDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugUtilsMessengerEXT");
			if (func != nullptr) {
				return func(instance, pCreateInfo, pAllocator, pDebugMessenger);
			}
			else {
				return VK_ERROR_EXTENSION_NOT_PRESENT;
			}
		}

		void DestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT debugMessenger, const VkAllocationCallbacks* pAllocator) {
			auto func = (PFN_vkDestroyDebugUtilsMessengerEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugUtilsMessengerEXT");
			if (func != nullptr) {
				func(instance, debugMessenger, pAllocator);
			}
		}
		void populateDebugMessengerCreateInfo(VkDebugUtilsMessengerCreateInfoEXT& createInfo) {
			createInfo = {};
			createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_UTILS_MESSENGER_CREATE_INFO_EXT;
			createInfo.messageSeverity =  VK_DEBUG_UTILS_MESSAGE_SEVERITY_WARNING_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_SEVERITY_ERROR_BIT_EXT;
			createInfo.messageType =  VK_DEBUG_UTILS_MESSAGE_TYPE_VALIDATION_BIT_EXT | VK_DEBUG_UTILS_MESSAGE_TYPE_PERFORMANCE_BIT_EXT;
			createInfo.pfnUserCallback = debugCallback;
		}


		void setupDebugMessenger() {

			VkDebugUtilsMessengerCreateInfoEXT createInfo;
			populateDebugMessengerCreateInfo(createInfo);

			if (CreateDebugUtilsMessengerEXT(instance, &createInfo, nullptr, &debugMessenger) != VK_SUCCESS) {
				throw std::runtime_error("failed to set up debug messenger!");
			}
		}
		static VKAPI_ATTR VkBool32 VKAPI_CALL debugCallback(VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageType, const VkDebugUtilsMessengerCallbackDataEXT* pCallbackData, void* pUserData) {
			MR_LOG_CORE_DEBUG("validation layer {0}", pCallbackData->pMessage);
			return VK_FALSE;
		}
	#endif 
	



	private:
		GLFWwindow* m_Window;
		void initIMGUI();
		struct QueueFamilyIndices {
			std::optional<uint32_t> graphicsFamily;
			std::optional<uint32_t> presentFamily;
			bool isComplete() {
				return graphicsFamily.has_value() && presentFamily.has_value();
			}
		};
		struct SwapChainSupportDetails {
			VkSurfaceCapabilitiesKHR capabilities;
			std::vector<VkSurfaceFormatKHR> formats;
			std::vector<VkPresentModeKHR> presentModes;
		};
		bool checkDeviceExtensionSupport(VkPhysicalDevice device);
		void createInstance();
		void pickPhysicalDevice();
		void createSurface();
		SwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);
		bool isDeviceSuitable(VkPhysicalDevice device);
		QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
		void createLogicalDevice();
		VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
		VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR>& availablePresentModes);
		VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
		void createSwapChain();
		void createImageViews();
		void DestroyImageViews();
		std::vector<char> readFile(const std::string& filename);
		VkShaderModule createShaderModule(const std::vector<char>& code);
		VkDescriptorPool g_DescriptorPool;
		uint32_t imageCount; 
		ImDrawData* draw_data;
		ImGuiIO* io;
		VkMemoryRequirements memRequirements;

		VkBuffer vertexBuffer;
		VkDeviceMemory vertexBufferMemory;
		VkBuffer indexBuffer;
		VkDeviceMemory indexBufferMemory;
		void createRenderPass();
		void createFramebuffers();
		void createCommandPool();
		void DestroyFramebuffer();
		void createCommandBuffers();
		void createSyncObjects();
		void createDescriptorPool();
		void DestroySyncObjects();
		void cleanupSwapChain();
		void IMGUIcreateDescriptorPool();
		uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
		void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
		void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	};
}