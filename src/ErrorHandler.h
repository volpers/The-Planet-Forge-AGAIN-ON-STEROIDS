#pragma once

#define ASSERT(x) if(!(x)) __debugbreak();
#define GLCall(x) ErrorHandler::GLClearError();\
	x;\
	ASSERT(ErrorHandler::GLLogCall(#x, __FILE__, __LINE__))

class ErrorHandler
{
public:
	static void GLClearError();
	static bool GLLogCall(const char* function, const char* file, int line);
};
