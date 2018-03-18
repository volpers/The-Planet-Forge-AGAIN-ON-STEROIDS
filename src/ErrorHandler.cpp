#include "ErrorHandler.h"
#include <GL/glew.h>
#include <iostream>

void ErrorHandler::GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool ErrorHandler::GLLogCall(const char* function, const char* file, int line)
{
	while(GLenum error = glGetError())
	{
		std::cout << "[OpenGL Error] (" << error << "): " << function << "\n in file: " <<file << "\n at line: " << line << std::endl;
		return false;
	}
	return true;
}
