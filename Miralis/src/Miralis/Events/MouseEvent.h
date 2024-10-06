#pragma once
#include"Miralis/Core.h"
#include"Miralis/Events/Event.h"
#include<sstream>
namespace Miralis {
	class MIRALIS_API MouseMovedEvent : public Event {
		MouseMovedEvent(float x, float y) : m_MouseX(x), m_MouseY(y) { ; };
		inline float GetX() const { return m_MouseX; };
		inline float GetY() const { return m_MouseY; };
		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedEvent: " << m_MouseX << ", " << m_MouseY;
			return ss.str();
		}
		EVENT_CLASS_TYPE(MouseMoved)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_MouseX;
		float m_MouseY;
	};
	class MIRALIS_API MouseScrolledEvent : public Event {
		MouseScrolledEvent(float offSetX, float offSetY):m_OffsetX(offSetX), m_OffsetY(offSetY) { ; };
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_OffsetX;
		float m_OffsetY;
	};


	class MIRALIS_API MouseButtonEvent : public Event {
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

	protected:
		MouseButtonEvent(int button) : m_Button(button) { ; };
		int m_Button;
	};


	class MIRALIS_API MouseButtonPressedEvent : public MouseButtonEvent {
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) { ; };
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MIRALIS_API MouseButtonRealsedssedEvent : public MouseButtonEvent {
		MouseButtonRealsedssedEvent(int button) : MouseButtonEvent(button) { ; };
		EVENT_CLASS_TYPE(MouseButtonRealsed)
	};


}