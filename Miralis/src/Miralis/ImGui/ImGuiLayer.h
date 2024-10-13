#pragma once
#include "Miralis/Layer.h"
#include"Miralis/Core.h"
namespace Miralis {
	class MIRALIS_API ImGuiLayer : public Layer {
	public:
		ImGuiLayer();
		~ImGuiLayer();
		void OnAttache() ;
		void OnDeAttache();
		void OnUpdate() ;
		void OnEvent(Event& event);
	private:
		float m_Time = 0.0f;
	};
}