#include "Miralis.h"
#include <Miralis/Log.h>

class Sandbox : public Miralis::Application {
public:
	Sandbox() {
		MR_LOG_CLIENT_TRACE("APp Start")

		PushLayer(new Miralis::ImGuiLayer());

	};
	~Sandbox() {
	}
};

Miralis::Application* Miralis::CreateApplication() {


	return new Sandbox();

}

