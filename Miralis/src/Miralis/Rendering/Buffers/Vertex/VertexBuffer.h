#pragma once
#include <cstdint>
#include <vector>
#include <string>
#include "Miralis/Core.h"
#include "Miralis/Log.h"
namespace Miralis {
	enum class ShaderDataType : uint8_t
	{
		None = 0,
		Float,
		Float2,
		Float3,
		Float4,
		Mat3,
		Mat4,
		Int,
		Int2,
		Int3,
		Int4,
		Bool
	};

	static uint32_t SahderDataTypeSize(ShaderDataType type) {
		switch (type) {
		case ShaderDataType::Float: return 4;
		case ShaderDataType::Float2: return 4 * 2;
		case ShaderDataType::Float3: return 4 * 3;
		case ShaderDataType::Mat3: return 4 * 3 * 3;
		case ShaderDataType::Mat4: return 4 * 4 * 4;
		case ShaderDataType::Int: return 4;
		case ShaderDataType::Int2: return 4 * 2;
		case ShaderDataType::Int3: return 4 * 3;
		case ShaderDataType::Int4: return 4 * 4;
		case ShaderDataType::Bool: return 1;
		}
		MR_CORE_ASSERT(false, "ShaderDataType UnDefined")
			return 0;
	}


	struct BufferElement {
		std::string Name;
		ShaderDataType Type;
		uint32_t Offset;
		uint32_t Size;
		bool Normalized;
		BufferElement(ShaderDataType type, const std::string& name, bool normolized = false)
			:Name(name), Type(type), Size(SahderDataTypeSize(type)), Offset(0), Normalized(normolized)
		{

		}
		BufferElement() {}
	};



	class VertexLayout {
	public:
		VertexLayout() {};
		VertexLayout(uint16_t Binding, std::initializer_list<BufferElement>const& elemnts)
			:m_Elemnts(elemnts), m_Binding(Binding) {
			CalculateOffsetsAndStride();
		};
		inline uint32_t GetStride() const { return m_Streide; };
		inline uint32_t GetBinding() const { return m_Binding; };

		inline const std::vector<BufferElement>& GetElements() const { return m_Elemnts; }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elemnts.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elemnts.end(); }
		std::vector<BufferElement>::iterator begin() { return m_Elemnts.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elemnts.end(); }

	private:
		std::vector<BufferElement> m_Elemnts;
		uint32_t m_Streide = 0;
		uint32_t m_Binding = 0;



	private:
		void CalculateOffsetsAndStride() {
			uint32_t offset = 0;
			m_Streide = 0;
			for (auto& elemt : m_Elemnts) {
				elemt.Offset = offset;
				offset += elemt.Size;
				m_Streide += elemt.Size;
			}
		}
	};


	class VertexBuffer {
	public:
		virtual ~VertexBuffer() = default;
		virtual void Bind()const = 0;
		virtual void UnBind()const = 0;
		virtual const VertexLayout& GetLayout() const = 0;
		static VertexBuffer* Create(float* vertices, uint32_t size, VertexLayout layout);;
	};


}

