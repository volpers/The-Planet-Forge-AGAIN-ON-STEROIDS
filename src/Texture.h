#pragma once
#include <string>

class Texture
{
private:
	unsigned m_RendererID;
	std::string m_FilePath;
	unsigned char* m_localBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string& filePath);
	~Texture();

	void Bind(unsigned slot = 0) const;
	void Unbind() const;

	int GetWidth() const
	{
		return m_Width;
	}

	int GetHeight() const
	{
		return m_Height;
	}

};
