#pragma once

class IndexBuffer
{
public:
	IndexBuffer() = default;
	IndexBuffer(const unsigned* data, unsigned count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	void Init(const unsigned* data, unsigned count);

	inline unsigned GetCount() const
	{
		return m_Count;
	}
	
private:
	unsigned m_RendererID;
	unsigned m_Count;
};
