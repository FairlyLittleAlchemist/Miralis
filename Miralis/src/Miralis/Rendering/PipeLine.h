#pragma once
#include<string>
#include <vector>
#include "Buffers/Buffer.h"
namespace Miralis {
	class PipeLine {
	public:
		static PipeLine* Create(std::string& VertexPath, std::string& fragmnetPath, const std::vector<VertexLayout>& layouts);
		virtual ~PipeLine() = default;
		virtual void  Bind() const = 0 ;
		virtual void UnBind() const = 0;
	};
}