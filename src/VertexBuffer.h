#pragma once

class VertexBuffer
{
public:
	VertexBuffer(const void* data, unsigned size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;
	
private:
	unsigned m_RendererID = 0;
};
