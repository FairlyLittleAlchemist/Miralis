#include "LayerStack.h"
namespace Miralis {

	LayerStack::LayerStack()
	{
		m_LayerInsert = m_Layers.begin();
	}


	void LayerStack::pushLayer(Layer* layer)
	{
		m_Layers.emplace(m_LayerInsert, layer);
	}
	void LayerStack::popLayer(Layer* layer)
	{
		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end()) {
			m_Layers.erase(it);
			m_LayerInsert--;
		}
	}

	void LayerStack::pushOverLay(Layer* layer)
	{

		m_Layers.emplace_back(layer);
	}

	void LayerStack::popOverLay(Layer* layer)
	{

		auto it = std::find(m_Layers.begin(), m_Layers.end(), layer);
		if (it != m_Layers.end())
			m_Layers.erase(it);
	}


}