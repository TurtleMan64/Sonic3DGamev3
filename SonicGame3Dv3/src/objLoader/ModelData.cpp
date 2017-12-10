#include <glad/glad.h>

#include <vector>
#include "modeldata.h"

ModelData::ModelData(std::vector<float>* vertices, std::vector<float>* textureCoords, std::vector<float>* normals, std::vector<int>* indices, float furthestPoint)
{
	for (auto entry : (*vertices)) { this->vertices.push_back(entry); }
	for (auto entry : (*textureCoords)) { this->textureCoords.push_back(entry); }
	for (auto entry : (*normals)) { this->normals.push_back(entry); }
	for (auto entry : (*indices)) { this->indices.push_back(entry); }
	this->furthestPoint = furthestPoint;
}

std::vector<float>* ModelData::getVertices()
{
	return &vertices;
}

std::vector<float>* ModelData::getTextureCoords()
{
	return &textureCoords;
}

std::vector<float>* ModelData::getNormals()
{
	return &normals;
}

std::vector<int>* ModelData::getIndices()
{
	return &indices;
}

float ModelData::getFurthestPoint()
{
	return furthestPoint;
}
