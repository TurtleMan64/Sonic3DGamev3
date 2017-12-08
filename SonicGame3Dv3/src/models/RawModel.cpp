#include <glad/glad.h>

#include "models.h"

RawModel::RawModel()
{

}

RawModel::RawModel(GLuint vaoID, int vertexCount)
{
	this->vaoID = vaoID;
	this->vertexCount = vertexCount;
}

int RawModel::getVaoID()
{
	return vaoID;
}

int RawModel::getVertexCount()
{
	return vertexCount;
}
