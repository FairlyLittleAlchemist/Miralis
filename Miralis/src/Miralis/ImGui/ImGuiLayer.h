#pragma once
#include "Miralis/Layer.h"

namespace Miralis {
	class ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttache() ;
		void OnDeAttache();
		void OnUpdate() ;
		void OnEvent(Event& event);
	private:
	};
}