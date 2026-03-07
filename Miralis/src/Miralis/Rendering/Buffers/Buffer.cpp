#include "../Renderer.h"
#include"Buffer.h"
#include "Platfrom/Vulkan/VulkanBuffer.h"
namespace Miralis {
	IndexBuffer* IndexBuffer::Create(uint32_t* indesis, uint32_t size)
	{

		switch (Rendere::GetAPI()) {
		case RendererAPI::API::Vulkan: return new VulkanIndexBuffer(indesis, size);
		}
		MR_CORE_ASSERT(false, "0-0 Api Not yet supported or Invalid");
		;
	}

		
	 VertexBuffer* Miralis::VertexBuffer::Create(float* vertices, uint32_t size, VertexLayout layout)
	{
		 switch (Rendere::GetAPI()) {
		 case RendererAPI::API::Vulkan: return new VulkanVertexBuffer(vertices, size, layout);
		 }
		 MR_CORE_ASSERT(false, "0-0 Api Not yet supported or Invalid");
	 }

	 ResourceSet* Miralis::ResourceSet::Create(const ResourceSetDescription& description) {
		 switch (Rendere::GetAPI()) {
		 case RendererAPI::API::Vulkan :return new VulkanResourceSet(description);
		 }
	 }

	 UnifromBuffer* UnifromBuffer::Create(uint32_t size)
	 {
		 switch (Rendere::GetAPI()) {
		 case RendererAPI::API::Vulkan: return new VulkanUniformBuffer(size);
		 }
		 MR_CORE_ASSERT(false, "0-0 Api Not yet supported or Invalid");
	 }




}