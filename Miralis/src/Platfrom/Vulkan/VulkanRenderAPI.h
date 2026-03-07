#pragma once
#include "Miralis/Rendering/RendererAPI.h"
namespace Miralis {
	class VulkanRendererAPI : public RendererAPI {
		virtual void SetClearColor(float r, float g, float b, float a) override;
		virtual void DrawIndexed(uint32_t count) override;
		virtual void BeingDraw() override;
		virtual void EndDraw() override;
		virtual ~VulkanRendererAPI() = default;  // add this
	};
}