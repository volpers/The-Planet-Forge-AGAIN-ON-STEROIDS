#include "Shader.h"
#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

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

