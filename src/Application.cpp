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
using namespace glm;

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

	const float toRadians = glm::pi<float>() / 180.0f;

	/*glm::vec4 pos[] = {
		glm::vec4(-0.5f, -0.5f,0.0f,0.0f),
		glm::vec4(0.5f,-0.5f,1.0f,0.0f),
		glm::vec4(0.5f,0.5f,1.0f,1.0f),
		glm::vec4(-0.5f,0.5f,0.0f,1.0f)
	};*/

	vec3 pos[] = {
		vec3(-1.0f, -1.0f, 0.0f),
		vec3(0.0f,-1.0f,1.0f),
		vec3(1.0f,-1.0f,0.0f),
		vec3(0.0f,1.0f,0.0f)
	};

	unsigned indices[] = {
		0,3,1,
		1,3,2,
		2,3,0,
		0,1,2
	};

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));
	GLCall(glEnable(GL_DEPTH_TEST));

	unsigned vao;
	GLCall(glGenVertexArrays(1, &vao));
	GLCall(glBindVertexArray(vao));

	//Vertex array stuff
	VertexArray va;
	VertexBuffer vb(pos, 4 * sizeof(vec3));
	
	VertexBufferLayout layout;
	layout.Push<float>(3);	
	
	va.AddBuffer(vb, layout);

	//Index Buffer
	IndexBuffer ib(indices, 12);
	
	//glm::mat4 projectionMatrix = glm::ortho(-2.0f, 2.0f, -1.5f, 1.5f, -1.0f, 1.0f);
	
	mat4 projectionMatrix = perspective(45.0f, (GLfloat)640 / (GLfloat)480, 0.1f, 100.0f);
	mat4 modelMatrix;
	

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
	float curAngle = 0.5f;
	float translation = 0.01f;

	modelMatrix *= projectionMatrix;
	modelMatrix = translate(modelMatrix, vec3(0.0f, 0.0f, -5.0f));
	//projectionMatrix *= modelMatrix;
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/* Render here */
		renderer.Clear();

		shader.Bind();

		//projectionMatrix = glm::rotate(projectionMatrix, curAngle, glm::vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = glm::rotate(modelMatrix, curAngle * toRadians, vec3(0.0f, 1.0f, 0.0f));
		modelMatrix = translate(modelMatrix, vec3(translation, 0.0f, 0.0f));
		
		shader.SetUniformMat4F("u_MVP", modelMatrix);
		//shader.SetUniform4f("u_Color", r, 0.3f, 0.8f, 1.0f); 		
		
		renderer.Draw(va, ib, shader);
		
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}																		