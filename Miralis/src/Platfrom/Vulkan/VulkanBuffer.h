#pragma once
#include "Miralis/Rendering/Buffers/Buffer.h"
#include <vulkan/vulkan.h>
#include <glm/glm.hpp>
#include <Platfrom/Vulkan/VulkanContext.h>
namespace Miralis {
	struct FormatInfo {
		VkFormat format;
		uint32_t componentCount;
	};


	static FormatInfo ShaderDataTypeToVkFormat(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float:   return { VK_FORMAT_R32_SFLOAT  , 1};
		case ShaderDataType::Float2:  return { VK_FORMAT_R32G32_SFLOAT, 1 };
		case ShaderDataType::Float3:  return { VK_FORMAT_R32G32B32_SFLOAT,1};
		case ShaderDataType::Float4:  return {VK_FORMAT_R32G32B32A32_SFLOAT,1 };
		case ShaderDataType::Mat3:	  return { VK_FORMAT_R32G32B32_SFLOAT,3 };
		case ShaderDataType::Mat4:    return { VK_FORMAT_R32G32B32A32_SFLOAT,4 };
		case ShaderDataType::Int:     return {VK_FORMAT_R32_SINT,1 };
		case ShaderDataType::Int2:    return {VK_FORMAT_R32G32_SINT,1 };
		case ShaderDataType::Int3:    return {VK_FORMAT_R32G32B32_SINT,1 };
		case ShaderDataType::Int4:    return {VK_FORMAT_R32G32B32A32_SINT,1 };
		case ShaderDataType::Bool:    return {VK_FORMAT_R8_UINT,1 };
		default:
			MR_CORE_ASSERT(false, "Unknown ShaderDataType for VkFormat!");
			return{ VK_FORMAT_UNDEFINED , 1 };
		}
	}

	
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usage, VkMemoryPropertyFlags properties, VkBuffer& buffer, VkDeviceMemory& bufferMemory);
	uint32_t findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties);
	void copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size);
	class VulkanVertexBuffer : public VertexBuffer {
	public:
		VulkanVertexBuffer(float* vertices, uint32_t size, VertexLayout layout);

		virtual ~VulkanVertexBuffer();
		virtual void Bind() const override ;
		virtual void UnBind() const override;
		virtual const VertexLayout& GetLayout() const override {return m_LayOut;};

	private:
		VertexLayout m_LayOut;
		VkBuffer m_Buffer;
		VkDeviceMemory m_BufferMemory;
	};
	class VulkanIndexBuffer : public IndexBuffer {
	public:
		VulkanIndexBuffer(uint32_t* indesis, uint32_t size);

		virtual ~VulkanIndexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
	private:
		VkBuffer m_Buffer;
		VkDeviceMemory m_BufferMemory;
	};

	class VulkanUniformBuffer : public UnifromBuffer {
	public:

		VulkanUniformBuffer(size_t size);
		~VulkanUniformBuffer() override;
		void UploadUnifrom(const float* data, uint32_t size)  override;
		uint32_t GetSize()  override { return m_size; }  ;
		VkBuffer getBuffer(size_t i) { return uniformBuffers[i]; };

	private:
		uint32_t m_size;
		VulkanContext* vkContext;
		std::vector<VkBuffer> uniformBuffers;
		std::vector<VkDeviceMemory> uniformBuffersMemory;
		std::vector<void*> uniformBuffersMapped;



	};


}