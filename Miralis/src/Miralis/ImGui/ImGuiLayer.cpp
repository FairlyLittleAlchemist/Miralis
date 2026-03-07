        #include <imgui.h>
        #include<GLFW/glfw3.h>
        #include "ImGuiLayer.h"
        #include"Miralis/Application.h"
        namespace Miralis {

	        ImGuiLayer::ImGuiLayer(): Layer("GUI Lyaer")
	        {
	        }
	        ImGuiLayer::~ImGuiLayer()
	        {
	        }
	        void ImGuiLayer::OnAttache()
	        {
                ImGuiIO& io = ImGui::GetIO();
                io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
                io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;
	        }
	        void ImGuiLayer::OnDeAttache()
	        {
	        }
	        void ImGuiLayer::OnUpdate()
	        {
                ImGui::NewFrame();
                ImGui::ShowDemoWindow(&show_demo_window);
                // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
                {
                    static float f = 0.0f;
                    static int counter = 0;

                    ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

                    ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
                    ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

                    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

                    if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
                        counter++;
                    ImGui::SameLine();
                    ImGui::Text("counter = %d", counter);

                    ImGui::End();
                }

                ImGui::Render();
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
                dispatcher.Dispatch<KeyTypedEvent>(std::bind(&ImGuiLayer::OnKeyTyped, this, std::placeholders::_1));
            }

            bool ImGuiLayer::OnMouseButtonPressed(MouseButtonPressedEvent& e)
	        {
	            ImGuiIO& io = ImGui::GetIO();
	            io.AddMouseButtonEvent(e.getMouseButton(), true);
	            return io.WantCaptureMouse;  // block event if ImGui wants it
	        }

            bool ImGuiLayer::OnMouseButtonRealsed(MouseButtonRealsedssedEvent& e)
	        {
	            ImGuiIO& io = ImGui::GetIO();
	            io.AddMouseButtonEvent(e.getMouseButton(), false);
	            return io.WantCaptureMouse;
	        }

            bool ImGuiLayer::OnMouseMove(MouseMovedEvent& e)
	        {
	            ImGuiIO& io = ImGui::GetIO();

	            io.AddMousePosEvent(e.GetX(), e.GetY());
	            return false;  // never block mouse move
	        }

            bool ImGuiLayer::OnMouseScroll(MouseScrolledEvent& e)
	        {
	            ImGuiIO& io = ImGui::GetIO();
	            io.AddMouseWheelEvent(e.GetXOffest(), e.GetYOffest());
	            return io.WantCaptureMouse;
	        }

            bool ImGuiLayer::OnKeyPressed(KeyPressedEvent& e)
	        {
	            ImGuiIO& io = ImGui::GetIO();
	        	if (e.getKeyCode()== 343) {
	        		return false;
	        	}

	            io.AddKeyEvent((ImGuiKey)e.getKeyCode(), true);
	            return io.WantCaptureKeyboard;
	        }

            bool ImGuiLayer::OnKeyRealsed(KeyReleasedEvent& e)
	        {
	            ImGuiIO& io = ImGui::GetIO();
	        	if (e.getKeyCode()== 343) {
	        		return false;
	        	}
	            io.AddKeyEvent((ImGuiKey)e.getKeyCode(), false);
	            return io.WantCaptureKeyboard;
	        }

            bool ImGuiLayer::OnKeyTyped(KeyTypedEvent& e)
	        {
	            ImGuiIO& io = ImGui::GetIO();
	            io.AddInputCharacter(e.getKeyCode());
	            return io.WantCaptureKeyboard;
	        }
        }