#pragma once
#ifdef MR_PLATFORM_WINDOWS
extern Miralis::Application* Miralis::CreateApplication();
int main() {
	auto* app = Miralis::CreateApplication();
	app->Run();
	delete app;

}
#endif // MR_PLATFORM_WINDOWS
