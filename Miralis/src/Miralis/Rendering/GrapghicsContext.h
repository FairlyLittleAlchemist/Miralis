#pragma once

namespace Miralis {
	class GraphicsContext {

	public:
		virtual void ImGUINewFrame() = 0;
		virtual void Init() = 0;
		virtual void SwapBuffers()= 0;
		virtual ~GraphicsContext() = default;

	};

}