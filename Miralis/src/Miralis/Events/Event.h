#pragma once
#include<iostream>
#include <functional>
#include "Miralis/Core.h"
namespace Miralis{
	enum  class EventType {
		None=0,
		WindowClosed,WindowResize,WindowFoucs,WindowLostFoucs,WindowMoved,
		AppTick,AppUpdate,AppRender,
		KeyPressed,KeyReleased,
		MouseButtonPressed,MouseButtonRealsed,MouseMoved,MouseScrolled
	};
	enum EventCategory {
		None=0,
		EventCategoryApplication= BIT(0),
		EventCategoryInput= BIT(1),
		EventCategoryKeybord= BIT(2),
		EventCategoryMouse= BIT(3),
		EventCategoryMouseButton= BIT(4),
	};
	#define EVENT_CLASS_TYPE(type) static EventType GetStaticType()  {return EventType::##type ;};\
																	virtual EventType   GetEventType() const override {return GetStaticType() ;} ;\
																	virtual const char* GetName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return  category; }
	class MIRALIS_API Event{
	public:
		friend class EventDispatcher;
		virtual  EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); };
		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
		bool Handeld = false;


	};

	class EventDispatcher {

		template<typename T>
		using EventFn = std::function<bool(T&)>;


	public:
		EventDispatcher(Event& event) : m_Event(event) {}


		template<typename T>
		bool Dispatch(EventFn<T> func) {
			if (m_Event.GetEventType() == T::GetStaticType()) {
				func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;
	};



}


