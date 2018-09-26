#pragma once
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

class Mesh
{
public:
	Mesh(std::vector<glm::vec3>& positions, std::vector<unsigned>& indices, const glm::mat4& projectionMatrix, std::string shaderPath, std::string texturePath);
	~Mesh() = default;
private:
	glm::mat4 modelMatrix;

	std::vector<glm::vec3>& positions;
	std::vector<unsigned>& indices;

	VertexBuffer vertexBuffer;
	IndexBuffer indexBuffer;
	VertexArray vertexArray;
	VertexBufferLayout bufferLayout;



	
};
