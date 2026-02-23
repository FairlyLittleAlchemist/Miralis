#include "VulkanBuffer.h"
#include "Miralis/Window.h"
#include "Platfrom/Vulkan/VulkanContext.h"
#include <vector>

namespace Miralis {


	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory)
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		VkBufferCreateInfo bufferInfo{};
		bufferInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
		bufferInfo.size = size;
		bufferInfo.usage = usage;
		bufferInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;

		MR_CORE_ASSERT(vkCreateBuffer(vkContext->device, &bufferInfo, nullptr, &buffer) == VK_SUCCESS, "Could not create create Buffer");
		VkMemoryRequirements memRequirements;
		vkGetBufferMemoryRequirements(vkContext->device, buffer, &memRequirements);

		VkMemoryAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
		allocInfo.allocationSize = memRequirements.size;
		allocInfo.memoryTypeIndex = findMemoryType(memRequirements.memoryTypeBits, properties);

		MR_CORE_ASSERT(vkAllocateMemory(vkContext->device, &allocInfo, nullptr, &bufferMemory) == VK_SUCCESS, "Could not Allocate Buffer");

		vkBindBufferMemory(vkContext->device, buffer, bufferMemory, 0);

	}
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		VkPhysicalDeviceMemoryProperties memProperties;
		vkGetPhysicalDeviceMemoryProperties(vkContext->physicalDevice, &memProperties);
		for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
			if ((typeFilter & (1 << i)) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
				return i;
			}
		}
		return 0;
	}
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		VkCommandBufferAllocateInfo allocInfo{};
		allocInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
		allocInfo.level = VK_COMMAND_BUFFER_LEVEL_PRIMARY;
		allocInfo.commandPool = vkContext->commandPool;
		allocInfo.commandBufferCount = 1;

		VkCommandBuffer commandBuffer;
		vkAllocateCommandBuffers(vkContext->device, &allocInfo, &commandBuffer);
		VkCommandBufferBeginInfo beginInfo{};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;

		vkBeginCommandBuffer(commandBuffer, &beginInfo);
		VkBufferCopy copyRegion{};
			copyRegion.srcOffset = 0; // Optional
			copyRegion.dstOffset = 0; // Optional
		copyRegion.size = size;
		vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);
		vkEndCommandBuffer(commandBuffer);
		VkSubmitInfo submitInfo{};
		submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &commandBuffer;

		vkQueueSubmit(vkContext->graphicsQueue, 1, &submitInfo, VK_NULL_HANDLE);
		vkQueueWaitIdle(vkContext->graphicsQueue);
		vkFreeCommandBuffers(vkContext->device, vkContext->commandPool, 1, &commandBuffer);

	}






	Miralis::VulkanVertexBuffer::VulkanVertexBuffer(float* vertices, uint32_t size, VertexLayout layout)
	{
		m_LayOut = layout;
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());
		VkDeviceSize bufferSize = sizeof(vertices[0]) * size;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(vkContext->device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, vertices, (size_t)bufferSize);
		vkUnmapMemory(vkContext->device, stagingBufferMemory);

		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_Buffer, m_BufferMemory);

		copyBuffer(stagingBuffer, m_Buffer, bufferSize);

	}

	VulkanVertexBuffer::~VulkanVertexBuffer()
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		vkDestroyBuffer(vkContext->device, m_Buffer, nullptr);
		vkFreeMemory(vkContext->device, m_BufferMemory, nullptr);
	}



	VulkanIndexBuffer::VulkanIndexBuffer(uint32_t* indesis, uint32_t size)
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		VkDeviceSize bufferSize = sizeof(indesis[0]) * size;

		VkBuffer stagingBuffer;
		VkDeviceMemory stagingBufferMemory;
		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

		void* data;
		vkMapMemory(vkContext->device, stagingBufferMemory, 0, bufferSize, 0, &data);
		memcpy(data, indesis, (size_t)bufferSize);
		vkUnmapMemory(vkContext->device, stagingBufferMemory);

		createBuffer(bufferSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, m_Buffer, m_BufferMemory);

		copyBuffer(stagingBuffer, m_Buffer, bufferSize);

		vkDestroyBuffer(vkContext->device, stagingBuffer, nullptr);
		vkFreeMemory(vkContext->device, stagingBufferMemory, nullptr);
	}

	void VulkanVertexBuffer::Bind() const
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		VkBuffer vertexBuffers[] = { m_Buffer };
		VkDeviceSize offsets[] = { 0 };
		vkCmdBindVertexBuffers(vkContext->commandBuffers[vkContext->currentFrame],this->GetLayout().GetBinding(), 1, vertexBuffers, offsets);

	}
	void VulkanVertexBuffer::UnBind() const
	{
	}



	VulkanIndexBuffer::~VulkanIndexBuffer()
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		vkDestroyBuffer(vkContext->device, m_Buffer, nullptr);
		vkFreeMemory(vkContext->device, m_BufferMemory, nullptr);

	}

	void VulkanIndexBuffer::Bind() const
	{
		VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());
		vkCmdBindIndexBuffer(vkContext->commandBuffers[vkContext->currentFrame], m_Buffer, 0, VK_INDEX_TYPE_UINT16);
	}
	void VulkanIndexBuffer::UnBind() const
	{
	}



	

	VulkanUniformBuffer::VulkanUniformBuffer(size_t size) :vkContext(static_cast<VulkanContext*>(Miralis::Window::m_Context.get())) {
		m_size = size;
		VkDeviceSize bufferSize = sizeof(float) * size;
		void Upload(const float* data, size_t size);

		uniformBuffers.resize(vkContext->MAX_FRAMES_IN_FLIGHT);
		uniformBuffersMemory.resize(vkContext->MAX_FRAMES_IN_FLIGHT);
		uniformBuffersMapped.resize(vkContext->MAX_FRAMES_IN_FLIGHT);
		for (size_t i = 0; i < vkContext->MAX_FRAMES_IN_FLIGHT; i++) {
			createBuffer(bufferSize, VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, uniformBuffers[i], uniformBuffersMemory[i]);

			vkMapMemory(vkContext->device, uniformBuffersMemory[i], 0, bufferSize, 0, &uniformBuffersMapped[i]);
		}

	}

	 void VulkanUniformBuffer::UploadUnifrom(const float* data, uint32_t size)  {
		memcpy(uniformBuffersMapped[vkContext->currentFrame], data, sizeof(float) * size);
	}

	
	 VulkanUniformBuffer::~VulkanUniformBuffer() {

		for (size_t i = 0; i < vkContext->MAX_FRAMES_IN_FLIGHT; i++) {
			vkDestroyBuffer(vkContext->device, uniformBuffers[i], nullptr);
			vkFreeMemory(vkContext->device, uniformBuffersMemory[i], nullptr);
		}
	};



	 VkDescriptorType ResourceTypeToVkType(ResourceDescription& r) {
		 switch (r.getType()) {
		 case ResourceType::UnifromBuffer: return VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER; 
		 }
		 MR_CORE_ASSERT(false , "Stop being lazy and implemnt this ")
	 }


	 VkDescriptorSetLayout VulkanResourceSet::CompileResourceSetDescription(const ResourceSetDescription& resourceSet)
	 {
		 VulkanContext* vkContext = static_cast<VulkanContext*>(Miralis::Window::m_Context.get());

		 std::vector<VkDescriptorSetLayoutBinding> LayoutBindings;
		 LayoutBindings.reserve(resourceSet.size());
		 uint32_t index = 0;
		 for (ResourceDescription r : resourceSet) {
			 VkDescriptorSetLayoutBinding LayoutBinding;

			 LayoutBinding.binding = index++;
			 LayoutBinding.descriptorType =ResourceTypeToVkType(r);
			 LayoutBinding.descriptorCount = r.GetCount();
			 LayoutBinding.stageFlags = VK_SHADER_STAGE_VERTEX_BIT;
			 LayoutBindings.push_back(LayoutBinding);
		 }
		 
		 VkDescriptorSetLayout descriptorSetLayout;

		 VkDescriptorSetLayoutCreateInfo layoutInfo{};
		 layoutInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
		 layoutInfo.bindingCount = LayoutBindings.size();
		 layoutInfo.pBindings = LayoutBindings.data();


		 MR_CORE_ASSERT(vkCreateDescriptorSetLayout(vkContext->device, &layoutInfo, nullptr, &descriptorSetLayout) == VK_SUCCESS, "Could not Allocate Buffer");

		 return descriptorSetLayout;
	 }

}
