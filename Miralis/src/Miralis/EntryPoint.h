#ifdef MR_PLATFORM_WINDOWS
extern Miralis::Application* Miralis::CreateApplication();
int main() {
	auto* app = Miralis::CreateApplication();
	app->Run();
	delete app;
}
#endif // MR_PLATFORM_WINDOWS


#ifdef MR_PLATFORM_LUNIX
#include <cstdlib>
extern Miralis::Application* Miralis::CreateApplication();
int main() {
	unsetenv("WAYLAND_DISPLAY");
	setenv("GDK_BACKEND", "x11", 1);
	setenv("SDL_VIDEODRIVER", "x11", 1);

	auto* app = Miralis::CreateApplication();
	app->Run();
	delete app;
}
#endif // MR_PLATFORM_WINDOWS

