#pragma once
#include<vulkan/vulkan.h>
#include "Miralis/Rendering/PipeLine.h"
#include "Platfrom/Vulkan/VulkanBuffer.h"
namespace Miralis {
	class VulkanPipeLine : public PipeLine
	{
	public :
		VulkanPipeLine(std::string& VertexPath, std::string& fragmnetPath, const std::vector<VertexLayout>& layouts);
		void Bind()const override;
		void UnBind() const override;
		~VulkanPipeLine() override;
		VkPipeline m_Pipeline;


	private:
		std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions(VertexLayout& layout, uint32_t offset);
		VkVertexInputBindingDescription getBindingDescription(VertexLayout& layout);

		std::vector<char> readFile(const std::string& filename);
		VkShaderModule createShaderModule(const std::vector<char>& code);
		VkPipelineLayout m_PipelineLayout;
	};
}


