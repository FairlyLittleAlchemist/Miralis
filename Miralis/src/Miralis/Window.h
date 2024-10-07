#pragma once
#include "Core.h"
#include "Events/Event.h"
#include "string.h"
#include<functional>

namespace Miralis {
	struct WindowProps
	{
		std::string Name;
		unsigned int Width;
		unsigned int Hight;
	public:
		WindowProps(std::string name = "Miralis" , unsigned int width = 800 , unsigned int hight = 600 ) :Name(name), Width(width), Hight(hight) {}
	};

	class MIRALIS_API Window {
	public:
		using EventCallBackFn = std::function<void(Event&)>;
		virtual ~Window() {};
		virtual inline unsigned int  getWidth() const = 0;
		virtual inline unsigned int  getHiegt() const = 0;
		virtual void OnUpdate() =0;
		virtual void SetEventClassBack(const EventCallBackFn& fnc) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;
		static Window* Create(const WindowProps& prop = WindowProps());
	};
}