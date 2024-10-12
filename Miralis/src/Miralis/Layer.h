#pragma once
#include"Core.h"
#include <string>
#include"Events/Event.h"
namespace Miralis{
class MIRALIS_API Layer
{
public:
	Layer(const  std::string& debugName);
	virtual ~Layer();
	virtual void OnAttache() {};
	virtual void OnDeAttache() {};
	virtual void OnUpdate() {};
	virtual void OnEvent(Event& event) {};
	inline const std::string& GetName() { return m_DebugName; };
private:
	std::string m_DebugName;
};
}

