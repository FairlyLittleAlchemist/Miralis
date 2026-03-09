#include "VulkanPipeLine.h"
#include "Platfrom/Vulkan/VulkanContext.h"
namespace Miralis {


	std::vector<VkVertexInputAttributeDescription> VulkanPipeLine::getAttributeDescriptions(VertexLayout & layout, uint32_t offset)
	{
		std::vector<VkVertexInputAttributeDescription> attributeDescriptions{};
		for (auto element : layout) {
			for (uint32_t i = 0; i < ShaderDataTypeToVkFormat(element.Type).componentCount; i++) {
				VkVertexInputAttributeDescription desc{};
				desc.binding = layout.GetBinding();
				desc.format = ShaderDataTypeToVkFormat(element.Type).format;
				desc.location = attributeDescriptions.size()+ offset;
				desc.offset = element.Offset + i * sizeof(float) * ShaderDataTypeToVkFormat(element.Type).componentCount;
				attributeDescriptions.push_back(desc);
			};

		}

		return attributeDescriptions;
	}

	VkVertexInputBindingDescription VulkanPipeLine::getBindingDescription(VertexLayout& layout)
	{
		VkVertexInputBindingDescription bindingDescription{};
		bindingDescription.binding = layout.GetBinding();
		bindingDescription.stride = layout.GetStride();
		bindingDescription.inputRate = VK_VERTEX_INPUT_RATE_VERTEX;
		return bindingDescription;
	}
	
	Miralis::VulkanPipeLine::VulkanPipeLine( const std::string& VertexPath, const std::string& fragmnetPath, const std::vector<VertexLayout>& layouts , const std::vector<ResourceSet*>& resource)
	{
		VulkanContext* m_Context = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		std::vector<VkVertexInputBindingDescription> bindingDescriptions;
		std::vector<VkVertexInputAttributeDescription> allAttributeDescriptions;
		uint32_t offset = 0;
		for (VertexLayout layout : layouts) {
			VkVertexInputBindingDescription bindingDesc = getBindingDescription(layout);
			bindingDescriptions.push_back(bindingDesc);
			std::vector<VkVertexInputAttributeDescription> layoutAttributes = getAttributeDescriptions(layout, offset);
			allAttributeDescriptions.insert(allAttributeDescriptions.end(),
				layoutAttributes.begin(),
				layoutAttributes.end());
			offset += layoutAttributes.size();

		}


		auto vertShaderCode = readFile(VertexPath);
		auto fragShaderCode = readFile(fragmnetPath);


		VkShaderModule vertShaderModule = createShaderModule(vertShaderCode);
		VkShaderModule fragShaderModule = createShaderModule(fragShaderCode);

		VkPipelineShaderStageCreateInfo vertShaderStageInfo{};
		vertShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		vertShaderStageInfo.stage = VK_SHADER_STAGE_VERTEX_BIT;
		vertShaderStageInfo.module = vertShaderModule;
		vertShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo fragShaderStageInfo{};
		fragShaderStageInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
		fragShaderStageInfo.stage = VK_SHADER_STAGE_FRAGMENT_BIT;
		fragShaderStageInfo.module = fragShaderModule;
		fragShaderStageInfo.pName = "main";

		VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };
    VkPipelineVertexInputStateCreateInfo vertexInputInfo{};
    vertexInputInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    vertexInputInfo.vertexBindingDescriptionCount = static_cast<uint32_t>(bindingDescriptions.size());
    vertexInputInfo.vertexAttributeDescriptionCount = static_cast<uint32_t>(allAttributeDescriptions.size());
    vertexInputInfo.pVertexBindingDescriptions = bindingDescriptions.data();
    vertexInputInfo.pVertexAttributeDescriptions = allAttributeDescriptions.data();


		VkPipelineInputAssemblyStateCreateInfo inputAssembly{};
		inputAssembly.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
		inputAssembly.topology = VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
		inputAssembly.primitiveRestartEnable = VK_FALSE;

		VkPipelineViewportStateCreateInfo viewportState{};
		viewportState.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
		viewportState.viewportCount = 1;
		viewportState.scissorCount = 1;

		VkPipelineRasterizationStateCreateInfo rasterizer{};
		rasterizer.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
		rasterizer.depthClampEnable = VK_FALSE;
		rasterizer.rasterizerDiscardEnable = VK_FALSE;
		rasterizer.polygonMode = VK_POLYGON_MODE_FILL;
		rasterizer.lineWidth = 1.0f;
		rasterizer.cullMode = VK_CULL_MODE_BACK_BIT;
		rasterizer.frontFace = VK_FRONT_FACE_COUNTER_CLOCKWISE;
		rasterizer.depthBiasEnable = VK_FALSE;



		VkPipelineMultisampleStateCreateInfo multisampling{};
		multisampling.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
		multisampling.sampleShadingEnable = VK_FALSE;
		multisampling.rasterizationSamples = VK_SAMPLE_COUNT_1_BIT;

		VkPipelineColorBlendAttachmentState colorBlendAttachment{};
		colorBlendAttachment.colorWriteMask = VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT;
		colorBlendAttachment.blendEnable = VK_FALSE;

		VkPipelineColorBlendStateCreateInfo colorBlending{};
		colorBlending.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
		colorBlending.logicOpEnable = VK_FALSE;
		colorBlending.logicOp = VK_LOGIC_OP_COPY;
		colorBlending.attachmentCount = 1;
		colorBlending.pAttachments = &colorBlendAttachment;
		colorBlending.blendConstants[0] = 0.0f;
		colorBlending.blendConstants[1] = 0.0f;
		colorBlending.blendConstants[2] = 0.0f;
		colorBlending.blendConstants[3] = 0.0f;

		std::vector<VkDynamicState> dynamicStates = {
			VK_DYNAMIC_STATE_VIEWPORT,
			VK_DYNAMIC_STATE_SCISSOR
		};
		VkPipelineDynamicStateCreateInfo dynamicState{};
		dynamicState.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
		dynamicState.dynamicStateCount = static_cast<uint32_t>(dynamicStates.size());
		dynamicState.pDynamicStates = dynamicStates.data();

		VkPipelineLayoutCreateInfo pipelineLayoutInfo{};


		pipelineLayoutInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
		pipelineLayoutInfo.setLayoutCount = resource.size();
		std::vector<VkDescriptorSetLayout> Dlayouts;
		for (ResourceSet* res : resource) {
			Dlayouts.push_back(static_cast<VulkanResourceSet*>(res)->getLayout());
		}
		pipelineLayoutInfo.pSetLayouts = Dlayouts.data();



		pipelineLayoutInfo.pushConstantRangeCount = 0;


		MR_CORE_ASSERT(((vkCreatePipelineLayout(m_Context->device, &pipelineLayoutInfo, nullptr, &m_PipelineLayout) == VK_SUCCESS)), "Could not create pipline layout");
		VkGraphicsPipelineCreateInfo pipelineInfo{};
		pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
		pipelineInfo.stageCount = 2;
		pipelineInfo.pStages = shaderStages;
		pipelineInfo.pVertexInputState = &vertexInputInfo;
		pipelineInfo.pInputAssemblyState = &inputAssembly;
		pipelineInfo.pViewportState = &viewportState;
		pipelineInfo.pRasterizationState = &rasterizer;
		pipelineInfo.pMultisampleState = &multisampling;
		pipelineInfo.pDepthStencilState = nullptr;
		pipelineInfo.pColorBlendState = &colorBlending;
		pipelineInfo.pDynamicState = &dynamicState;
		pipelineInfo.layout = m_PipelineLayout;
		pipelineInfo.renderPass = m_Context->renderPass;
		pipelineInfo.subpass = 0;
		pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;
		pipelineInfo.basePipelineIndex = -1;
		MR_CORE_ASSERT(((vkCreateGraphicsPipelines(m_Context->device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &m_Pipeline) == VK_SUCCESS)), "Coud not create pipline");
		vkDestroyShaderModule(m_Context->device, fragShaderModule, nullptr);
		vkDestroyShaderModule(m_Context->device, vertShaderModule, nullptr);
	}
	void  VulkanPipeLine::Bind() const
	{
		VulkanContext* m_Context = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		vkCmdBindPipeline(m_Context->commandBuffers[m_Context->currentFrame], VK_PIPELINE_BIND_POINT_GRAPHICS, m_Pipeline);

	}

	void VulkanPipeLine::UnBind() const
	{
	}

	VulkanPipeLine::~VulkanPipeLine()
	{
	}



	std::vector<char> VulkanPipeLine::readFile(const std::string& filename)
	{
		std::ifstream file(filename, std::ios::ate | std::ios::binary);
		MR_CORE_ASSERT(file.is_open(), "File Not Exist");
		size_t fileSize = (size_t)file.tellg();
		std::vector<char> buffer(fileSize);
		file.seekg(0);
		file.read(buffer.data(), fileSize);
		file.close();
		return buffer;
	}

	VkShaderModule VulkanPipeLine::createShaderModule(const std::vector<char>& code)
	{
		VulkanContext* m_Context = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		VkShaderModuleCreateInfo createInfo{};
		createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
		createInfo.codeSize = code.size();
		createInfo.pCode = reinterpret_cast<const uint32_t*>(code.data());
		VkShaderModule shaderModule;
		MR_CORE_ASSERT((vkCreateShaderModule(m_Context->device, &createInfo, nullptr, &shaderModule) == VK_SUCCESS), "VulkanPipeLine modual not created");
		return shaderModule;
	}
}