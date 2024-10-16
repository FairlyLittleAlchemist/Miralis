#pragma once
#include"Miralis/Core.h"
#include"Miralis/Events/Event.h"
#include<sstream>
namespace Miralis {
	class MIRALIS_API MouseMovedEvent : public Event {
	public:
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
	public:
		MouseScrolledEvent(float offSetX, float offSetY):m_OffsetX(offSetX), m_OffsetY(offSetY) { ; };
		std::string ToString() const override {
			std::stringstream  ss;
			ss << "MouseScrolledEvent: " << m_OffsetX << ", " << m_OffsetY;
			return ss.str();
		}
		inline float GetXOffest() { return m_OffsetX; };
		inline float GetYOffest() { return m_OffsetY; };
		EVENT_CLASS_TYPE(MouseScrolled)
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
	private:
		float m_OffsetX;
		float m_OffsetY;
	};


	class MIRALIS_API MouseButtonEvent : public Event {
	public:
		EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
		inline int	getMouseButton() { return m_Button; };
	protected:
		MouseButtonEvent(int button) : m_Button(button) { ; };
		int m_Button;
	};


	class MIRALIS_API MouseButtonPressedEvent : public MouseButtonEvent {
	public:
		std::string ToString() const override {
			std::stringstream  ss;
			ss << "MouseButtonPressedEvent: " << m_Button;
			return ss.str();
		}
		MouseButtonPressedEvent(int button) : MouseButtonEvent(button) { ; };
		EVENT_CLASS_TYPE(MouseButtonPressed)
	};

	class MIRALIS_API MouseButtonRealsedssedEvent : public MouseButtonEvent {
	public:
		std::string ToString() const override {
			std::stringstream  ss;
			ss << "MouseButtonRealsedssedEvent:" << m_Button;
			return ss.str();
		}
		MouseButtonRealsedssedEvent(int button) : MouseButtonEvent(button) { ; };
		EVENT_CLASS_TYPE(MouseButtonRealsed)
	};


}