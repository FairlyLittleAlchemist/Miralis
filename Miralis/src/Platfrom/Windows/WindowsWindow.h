#pragma once
#include "Miralis/Window.h"
#include "Miralis/Log.h"
#include "GLFW/glfw3.h"
	namespace Miralis {
class WindowsWindow : public Window
{
public:
	WindowsWindow(const WindowProps& props);
	
	virtual ~WindowsWindow() override;
	void OnUpdate() override;
	
	inline unsigned int  getWidth()const override { return m_Data.Width; };
	inline unsigned int  getHiegt()const  override { return m_Data.Hight; };
	void inline SetEventClassBack(const EventCallBackFn& fnc) { m_Data.EventCallBack = fnc; };
	bool  inline IsVSync() const override { return m_Data.VSync; } ;

	inline GLFWwindow* getWindow() { return m_Window; };
	void SetVSync(bool enabled) override;
private:
	virtual void Init(const WindowProps& pors);
	virtual void ShutDown();
private:
	GLFWwindow* m_Window;

	struct windowData
	{
		std::string Name;
		unsigned int Width, Hight;
		bool VSync;
		EventCallBackFn EventCallBack;
	};

	windowData m_Data;
};
}

