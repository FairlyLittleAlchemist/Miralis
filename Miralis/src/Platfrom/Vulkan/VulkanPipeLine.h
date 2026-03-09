#pragma once
#include<vulkan/vulkan.h>
#include "Platfrom/Vulkan/VulkanBuffer.h"

#include "Miralis/Rendering/PipeLine.h"
namespace Miralis {
	class VulkanPipeLine : public PipeLine
	{
	public :
		VulkanPipeLine(const std::string& VertexPath, const std::string& fragmnetPath, const std::vector<VertexLayout>& layouts , const std::vector<ResourceSet*>& resource);
		void Bind()const override;
		void UnBind() const override;
		~VulkanPipeLine() override;
		VkPipeline m_Pipeline;
		VkPipelineLayout getLayout(){return m_PipelineLayout ;} ;

	private:
		std::vector<VkVertexInputAttributeDescription> getAttributeDescriptions(VertexLayout& layout, uint32_t offset);
		VkVertexInputBindingDescription getBindingDescription(VertexLayout& layout);

		std::vector<char> readFile(const std::string& filename);
		VkShaderModule createShaderModule(const std::vector<char>& code);
		VkPipelineLayout m_PipelineLayout;
	};
}


