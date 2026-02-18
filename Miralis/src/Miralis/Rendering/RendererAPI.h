#pragma once
#include <glm/glm.hpp>
namespace  Miralis{
	class RendererAPI {
	public :
		enum class API
		{
			None = 0,
			Vulkan =  1,
		};
	public : 
		virtual void BeingDraw() = 0;
		virtual void EndDraw() = 0;
		virtual void SetClearColor(float r, float g, float b, float a) = 0;
		virtual void DrawIndexed(uint32_t count) = 0;

		inline static API GetAPI() { return s_API; }
	private :
		static API s_API;
	};
}