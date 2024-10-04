#pragma once
#include "Core.h"
#include "Miralis/Event.h"
#include <sstream>
namespace Miralis {
	class MIRALIS_API KeyEvent : public Event
	{
	public:
		KeyEvent(int keyCode) :m_KeyCode(keyCode) {};
		inline int getKeyCode() const { return m_KeyCode; };
	protected:
		EVENT_CLASS_CATEGORY(EventCategoryInput | EventCategoryKeybord);
		unsigned int m_KeyCode;
	};


	class MIRALIS_API KeyPressedEvent : public KeyEvent {
		KeyPressedEvent(int keyCode, int repeatCount):KeyEvent(keyCode),m_RepeatCount(repeatCount) {};
		inline int getRepeatCount() const { return m_RepeatCount; };
		std::string ToString() const override {
			std::stringstream  ss;
			ss << "KeyPressedEvent: " << m_KeyCode << ", " << m_RepeatCount;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyPressed)
	private:
		int m_RepeatCount;
	};


	class MIRALIS_API KeyReleasedEvent : public KeyEvent {
		KeyReleasedEvent(int keyCode) :KeyEvent(keyCode){};
		std::string ToString() const override {
			std::stringstream  ss;
			ss << "KeyReleased: " << m_KeyCode ;
			return ss.str();
		}
		EVENT_CLASS_TYPE(KeyReleased)
	
	};
}