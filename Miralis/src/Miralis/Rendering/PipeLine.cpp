#include "PipeLine.h"
#include "Renderer.h"
#include "Platfrom/Vulkan/VulkanPipeLine.h"
namespace Miralis{
	 PipeLine* Miralis::PipeLine::Create( const std::string& VertexPath, const std::string& fragmnetPath, const std::vector<VertexLayout>& layouts , const std::vector<ResourceSet*>& resource)
	{
		 switch (Rendere::GetAPI()) {
		 case RendererAPI::API::Vulkan: return new VulkanPipeLine(VertexPath, fragmnetPath, layouts , resource );
 		 }
		 MR_CORE_ASSERT(false, "0-0 Api Not yet supported or Invalid");
	}
}
