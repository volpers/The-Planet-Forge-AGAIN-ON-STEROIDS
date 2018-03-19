#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ErrorHandler.h"

Shader::Shader(const std::string& filepath)	 : m_RendererID(0), m_FilePath(filepath)
{  
	ShaderProgramSource source = Shader::ParseShader(filepath);
	m_RendererID = Shader::CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	GLCall(glDeleteProgram(m_RendererID));
}




void Shader::Bind() const
{
	GLCall(glUseProgram(m_RendererID));
}

void Shader::Unbind() const
{
	GLCall(glUseProgram(0));
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	GLCall(glUniform4f(GetUniformLocation(name), v0, v1, v2, v3));
}

int Shader::GetUniformLocation(const std::string& name)
{
	if(m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}

	GLCall(int location = glGetUniformLocation(m_RendererID, name.c_str()));
	if(location == -1)
	{
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	}
		
	m_UniformLocationCache[name] = location;
	return location;

}

unsigned Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned program = glCreateProgram();
	unsigned vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	unsigned fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	std::string line;
	std::stringstream stringStream[2];
	ShaderType type = ShaderType::NONE;

	while(getline(stream, line))
	{
		if(line.find("#shader") != std::string::npos)
		{
			if(line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			stringStream[int(type)] << line << '\n';
		}
	}

	return {stringStream[int(ShaderType::VERTEX)].str(), stringStream[int(ShaderType::FRAGMENT)].str()};
}

unsigned Shader::CompileShader(unsigned type, const std::string& source)
{
	const unsigned id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);

	if(result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = static_cast<char*>(alloca(length * sizeof(char)));
		glGetShaderInfoLog(id, length, &length, message);

		std::cout << "Failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "-shader!" << std::endl;
		std::cout << message << std::endl;
		
		glDeleteShader(id);
	}

	return id;
}  

