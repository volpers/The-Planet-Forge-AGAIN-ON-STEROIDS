#include "Mesh.h"

Mesh::Mesh(std::vector<glm::vec3>& positions, std::vector<unsigned>& indices, const glm::mat4& projectionMatrix) : positions(positions), indices(indices) 
{
	vertexBuffer.Init(positions.data(), positions.size() * sizeof(glm::vec3));
	indexBuffer.Init(indices.data(), indices.size());
	modelMatrix *= projectionMatrix;
	bufferLayout.Push<float>(3);
	vertexArray.AddBuffer(vertexBuffer, bufferLayout);
}
