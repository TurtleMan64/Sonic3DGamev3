#include <glad/glad.h>

#include "models.h"
#include "../renderEngine/renderEngine.h"

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

void RawModel::deleteMe()
{
	Loader_deleteVAO(vaoID);
	//for (int vbo : vboIDs)
	//{
		//MainGameLoop.gameLoader.deleteVBO(vbo);
	//}
	//vboIDs = null;
}