#include "Miralis.h"

class Sandbox : public Miralis::Application {
public:
	Sandbox() {

	};

	~Sandbox() {

	}
};

Miralis::Application* Miralis::CreateApplication() {
	return new Sandbox();
}

