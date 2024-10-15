#include "Miralis.h"
#include <Miralis/Log.h>

class Sandbox : public Miralis::Application {
public:
	Sandbox() {
		PushLayer(new Miralis::ImGuiLayer());
	};
	~Sandbox() {
	}
};

Miralis::Application* Miralis::CreateApplication() {


	return new Sandbox();
}

