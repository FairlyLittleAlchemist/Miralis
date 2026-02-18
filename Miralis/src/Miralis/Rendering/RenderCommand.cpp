#pragma once

#include"RenderCommands.h" 
#include "Platfrom/Vulkan/VulkanRenderAPI.h"
namespace Miralis {
	RendererAPI* RenderCommands::s_RendererAPI = new VulkanRendererAPI;
}