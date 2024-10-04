#include "Miralis.h"
#include <Miralis/Log.h>
class Sandbox : public Miralis::Application {
public:
	Sandbox() {
		MR_LOG_CLIENT_INFO("SandBox Log")
	};
	~Sandbox() {
	}
};

Miralis::Application* Miralis::CreateApplication() {
	return new Sandbox();
}

