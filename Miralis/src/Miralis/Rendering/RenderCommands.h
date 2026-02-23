#pragma once
#include "Miralis/Rendering/RendererAPI.h"
#include "glm/glm.hpp"
#include "cstdint"
namespace Miralis {
	class RenderCommands {
	public:
		inline static void SetClearDraw(const glm::vec4& color) {
			s_RendererAPI->SetClearColor(color.r, color.g , color.b ,color.a);
		}
		inline static void BeingDraw() {
			s_RendererAPI->BeingDraw();
		}

		inline static void EndDraw() {
			s_RendererAPI->EndDraw();
		}
		inline static void DrawIndexed(uint32_t count) {
			s_RendererAPI->DrawIndexed(count);
		}


	private:
	static	RendererAPI*  s_RendererAPI;
	};
}