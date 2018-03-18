#pragma once

#include <string>

enum class ShaderType
{
	NONE = -1, VERTEX = 0, FRAGMENT = 1
};

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader() = default;
	static unsigned CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	static ShaderProgramSource ParseShader(const std::string& filepath);

private:
	static unsigned CompileShader(unsigned type, const std::string& source);
};
