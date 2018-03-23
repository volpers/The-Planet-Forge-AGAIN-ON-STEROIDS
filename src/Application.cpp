#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include "Shader.h"
#include "ErrorHandler.h"

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Renderer.h"
#include "Texture.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"


using namespace std;

int main(void)
{
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	GLFWwindow * window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);


	if (glewInit() != GLEW_OK)
	{
		cout << "Error while initializing GLEW" << endl;
	}

	cout << "OpenGL version: " <<  glGetString(GL_VERSION);

	float positions[] = {
		-0.5f, -0.5f, 0.0f, 0.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		0.5f, 0.5f, 1.0f, 1.0f,	
		-0.5f, 0.5f, 0.0f, 1.0f 
	};

	unsigned indices[] = {
		0,1,2,
		2,3,0
	};

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));

	unsigned vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	//Vertex array stuff
	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));
	
	VertexBufferLayout layout;
	layout.Push<float>(2);	
	layout.Push<float>(2);
	va.AddBuffer(vb, layout);

	//Index Buffer
	IndexBuffer ib(indices, 6);
	
	glm::mat4 projectionMatrix = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);

	//Shader
	Shader shader("Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
	shader.SetUniformMat4F("u_MVP", projectionMatrix);


	Texture texture("res/texture.png");
	texture.Bind();
	shader.SetUniform1i("u_Texture", 0);


	//Unbind everything
	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	float r = 0.0f;
	float increment = 0.05f;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		shader.Bind();
		//shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f); 		
		
		renderer.Draw(va, ib, shader);

		
		if(r > 1.0f)
		{
			increment = -0.05f;
		}
		else if(r < 0.0f)
		{
			increment = 0.05f;
		}

		r += increment;

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}																		