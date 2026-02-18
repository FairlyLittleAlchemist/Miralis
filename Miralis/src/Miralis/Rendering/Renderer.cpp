#include "Renderer.h"
#include "RenderCommands.h"
namespace Miralis {
	void Rendere::BegineScene()
	{
	}

	void Rendere::EndScene()
	{
	}

	void Miralis::Rendere::Sbumit(uint32_t count)
	{
		RenderCommands::DrawIndexed(count);
	}
}

