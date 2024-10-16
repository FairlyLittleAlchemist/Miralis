#pragma once
#include "Miralis/Layer.h"
#include"Miralis/Core.h"
#include "Miralis/Events/KeyEvent.h"
#include "Miralis/Events/ApplicationEvent.h"
#include "Miralis/Events/MouseEvent.h"
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
		bool OnMouseButtonPressed(MouseButtonPressedEvent& e);
		bool OnMouseButtonRealsed(MouseButtonRealsedssedEvent& e);
		bool OnMouseMove(MouseMovedEvent& e);
		bool OnMouseScroll(MouseScrolledEvent& e);
		bool OnKeyPressed(KeyPressedEvent& e);
		bool OnKeyRealsed(KeyReleasedEvent& e);
		//void OnKeyTyped();
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		float m_Time = 0.0f;
	};
}