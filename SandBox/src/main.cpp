#include "Miralis.h"

#include <iostream>
class Sandbox : public Miralis::Application {
public:
	Sandbox() {

	};

	~Sandbox() {

	}
};

Miralis::Application* Miralis::CreateApplication() {
	std::cout << "Hellow";
	return new Sandbox();
}

