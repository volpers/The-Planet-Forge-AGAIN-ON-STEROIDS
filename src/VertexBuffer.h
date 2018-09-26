#pragma once

class VertexBuffer
{
public:
	VertexBuffer() =default;
	VertexBuffer(const void* data, unsigned size);
	~VertexBuffer();

	void Init(const void* data, unsigned size);

	void Bind() const;
	void Unbind() const;
	
private:
	unsigned m_RendererID = 0;
};
