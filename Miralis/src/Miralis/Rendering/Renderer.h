#pragma once

#include"Miralis/Rendering/RendererAPI.h"

namespace Miralis {
	class Rendere {
	public:
		static void BegineScene();
		static void EndScene();
		static void Sbumit(uint32_t count);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};
}
