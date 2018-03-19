#pragma once
#include <vector>
#include <GL/glew.h>
#include "ErrorHandler.h"

struct VertexBufferElement
{
	unsigned type;
	unsigned count;	
	bool normalized;

	static unsigned GetSizeOfType(unsigned type)
	{
		switch (type)
		{
		case GL_FLOAT: return 4;
		case GL_UNSIGNED_INT: return 4;
		case GL_UNSIGNED_BYTE: return 1;
		default:
			ASSERT(false);
		} 
		return 0;
	}
};

class VertexBufferLayout
{
private:
	unsigned m_Stride;
	std::vector<VertexBufferElement> m_Elements;
public:
	VertexBufferLayout() : m_Stride(0) {};
	~VertexBufferLayout() = default;

	template<typename T>
	void Push(unsigned count)
	{
		static_assert(false);
	}

	template<>
	void Push<float>(unsigned count) {
		m_Elements.push_back({ GL_FLOAT, count, false });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_FLOAT);
	};

	template<>
	void Push<unsigned>(unsigned count) {
		m_Elements.push_back({ GL_UNSIGNED_INT, count, false });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT);
	}

	template<>
	void Push<unsigned char>(unsigned count){
		m_Elements.push_back({ GL_UNSIGNED_BYTE, count, true });
		m_Stride += count * VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE);
	}

	inline unsigned GetStride() const { return m_Stride; }
	inline const std::vector<VertexBufferElement>& GetElements() const
	{
		return m_Elements;
	}
};
