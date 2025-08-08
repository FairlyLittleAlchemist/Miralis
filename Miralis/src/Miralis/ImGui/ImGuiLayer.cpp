#include "ImGuiLayer.h"

#include"Miralis/Application.h"
#include "imgui.h"

namespace Miralis {




	ImGuiLayer::ImGuiLayer(): Layer("GUI Lyaer")
	{
	}
	ImGuiLayer::~ImGuiLayer()
	{
	}
	void ImGuiLayer::OnAttache()
	{
	}
	void ImGuiLayer::OnDeAttache()
	{

 
	}
	void ImGuiLayer::OnUpdate()
	{

      
	}

    void ImGuiLayer::OnEvent(Event& event)
    {
        EventDispatcher dispatcher(event);
        dispatcher.Dispatch<MouseButtonPressedEvent>(std::bind(&ImGuiLayer::OnMouseButtonPressed, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseButtonRealsedssedEvent>(std::bind(&ImGuiLayer::OnMouseButtonRealsed, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseMovedEvent>(std::bind(&ImGuiLayer::OnMouseMove, this, std::placeholders::_1));
        dispatcher.Dispatch<MouseScrolledEvent>(std::bind(&ImGuiLayer::OnMouseScroll, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyPressedEvent>(std::bind(&ImGuiLayer::OnKeyPressed, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyReleasedEvent>(std::bind(&ImGuiLayer::OnKeyRealsed, this, std::placeholders::_1));
        dispatcher.Dispatch<WindowResizeEvent>(std::bind(&ImGuiLayer::OnWindowResize, this, std::placeholders::_1));
        dispatcher.Dispatch<KeyTypedEvent>(std::bind(&ImGuiLayer::OnKeyTyped, this, std::placeholders::_1));


    }

    bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
    {
        return false;
       
    }

    bool ImGuiLayer::OnMouseButtonRealsed(MouseButtonRealsedssedEvent& e)
    {
        return false;
       
    }

    bool ImGuiLayer::OnMouseMove(MouseMovedEvent& e)
    {
        return false;
    }

    bool ImGuiLayer::OnMouseScroll(MouseScrolledEvent& e)
    {
        return false;
    }

    bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& e)
    {
     
        return false;
    }

    bool ImGuiLayer::OnKeyRealsed(KeyReleasedEvent& e)
    {
        return false;
        
    }

    bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& e)
    {
       
        return false;
    }

    bool ImGuiLayer::OnWindowResize(WindowResizeEvent& e)
    {
        return false;
    }

  
}