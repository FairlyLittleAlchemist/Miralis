#pragma once
#include "Core.h"
#include "Miralis/Events/Event.h"
#include <sstream>
namespace  Miralis{
class MIRALIS_API WindowResizeEvent : public Event
{
public:
	WindowResizeEvent(int width, int hight) :m_Width(width), m_Height(hight) {};
	inline  unsigned int getWidth() const { return m_Width; };
	inline  unsigned int getHight() const { return m_Height; };
	std::string ToString() const override {
		std::stringstream  ss;
		ss << "WindowResizeEvent: " << m_Width << ", " << m_Height;
		return ss.str();
	}
	EVENT_CLASS_TYPE(WindowResize)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
private:
	unsigned int m_Width, m_Height;
};


class MIRALIS_API WindowCloseEvent : public Event
{
public:
	WindowCloseEvent(){};

	EVENT_CLASS_TYPE(WindowClosed)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};

class MIRALIS_API AppUpdateEvent : public Event
{
public:
	AppUpdateEvent() {};

	EVENT_CLASS_TYPE(AppUpdate)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};


class MIRALIS_API AppTickEvent : public Event
{
public:
	AppTickEvent() {};
	EVENT_CLASS_TYPE(AppTick)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};


class MIRALIS_API AppRenderEvent : public Event
{
public:
	AppRenderEvent() {};
	EVENT_CLASS_TYPE(AppRender)
	EVENT_CLASS_CATEGORY(EventCategoryApplication)
};
}

