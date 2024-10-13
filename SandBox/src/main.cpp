#include "Miralis.h"
#include <Miralis/Log.h>

class ExmpleLayer : public Miralis::Layer {
public:
	ExmpleLayer() :Layer("Exmple Layer") {

	}
	void OnUpdate() override {
		MR_LOG_CLIENT_INFO("Layer Update");
	}


	void OnEvent(Miralis::Event& event) override {
		MR_LOG_CLIENT_TRACE("{0}", event.ToString());
	}
};

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

