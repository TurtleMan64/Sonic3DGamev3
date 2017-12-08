#include <glad/glad.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

#include "objLoader.h"
#include "../models/models.h"
#include "../renderEngine/renderEngine.h"


char ** split(char *, char);
void processVertex(char**, 
	std::vector<int>*, 
	std::vector<Vector2f>*, 
	std::vector<Vector3f>*, 
	float*, 
	float*);

int splitLength = 0;


int nArraySize = 0;
int tArraySize = 0;

RawModel loadObjModel(char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file '%s'\n", fileName);
		file.close();
		RawModel temp;
		return temp;
	}

	std::string line;

	std::vector<Vector3f> vertices;
	std::vector<Vector2f> textures;
	std::vector<Vector3f> normals;
	std::vector<int> indices;

	//float* vArray;
	float* nArray;
	float* tArray;
	//int* iArray;

	int foundFaces = 0;

	while (!file.eof())
	{
		getline(file, line);

		char lineBuf[128]; //Buffer to copy line into
		memset(lineBuf, 0, 128);
		memcpy(lineBuf, line.c_str(), line.size());
		char** lineSplit = split(lineBuf, ' ');

		if (splitLength > 0)
		{
			if (foundFaces == 0)
			{
				if (strcmp(lineSplit[0], "v") == 0)
				{
					std::string p1(lineSplit[1]);
					std::string p2(lineSplit[2]);
					std::string p3(lineSplit[3]);
					Vector3f vertex(std::stof(p1, nullptr), std::stof(p2, nullptr), std::stof(p3, nullptr));
					vertices.push_back(vertex);
					p1.clear();
					p2.clear();
					p3.clear();
				}
				else if (strcmp(lineSplit[0], "vt") == 0)
				{
					std::string t1(lineSplit[1]);
					std::string t2(lineSplit[2]);
					Vector2f texCoord(std::stof(t1, nullptr), std::stof(t2, nullptr));
					textures.push_back(texCoord);
					t1.clear();
					t2.clear();
				}
				else if (strcmp(lineSplit[0], "vn") == 0)
				{
					std::string n1(lineSplit[1]);
					std::string n2(lineSplit[2]);
					std::string n3(lineSplit[3]);
					Vector3f normal(std::stof(n1, nullptr), std::stof(n2, nullptr), std::stof(n3, nullptr));
					normals.push_back(normal);
					n1.clear();
					n2.clear();
					n3.clear();
				}
				else if (strcmp(lineSplit[0], "f") == 0)
				{
					tArray = (float*)malloc(sizeof(float)*(vertices.size()*2));
					nArray = (float*)malloc(sizeof(float)*(vertices.size()*3));

					tArraySize = vertices.size() * 2;
					nArraySize = vertices.size() * 3;

					foundFaces = 1;

					char** vertex1 = split(lineSplit[1], '/');
					char** vertex2 = split(lineSplit[2], '/');
					char** vertex3 = split(lineSplit[3], '/');

					processVertex(vertex1, &indices, &textures, &normals, tArray, nArray);
					processVertex(vertex2, &indices, &textures, &normals, tArray, nArray);
					processVertex(vertex3, &indices, &textures, &normals, tArray, nArray);

					free(vertex1);
					free(vertex2);
					free(vertex3);
				}
			}
			else
			{
				if (strcmp(lineSplit[0], "f") == 0)
				{
					char** vertex1 = split(lineSplit[1], '/');
					char** vertex2 = split(lineSplit[2], '/');
					char** vertex3 = split(lineSplit[3], '/');

					processVertex(vertex1, &indices, &textures, &normals, tArray, nArray);
					processVertex(vertex2, &indices, &textures, &normals, tArray, nArray);
					processVertex(vertex3, &indices, &textures, &normals, tArray, nArray);

					free(vertex1);
					free(vertex2);
					free(vertex3);
				}
			}
		}

		free(lineSplit);
	}

	file.close();

	//vArray = (float*)malloc(sizeof(float)*(vertices.size()*3));
	//iArray = (int*)malloc(sizeof(int)*(indices.size()));
	std::vector<float> vectorVertex;
	int vSize = vertices.size();
	for (int vertexPointer = 0; vertexPointer < vSize; vertexPointer++)
	{
		//vArray[vertexPointer*3]   = vertices[vertexPointer].x;
		//vArray[vertexPointer*3+1] = vertices[vertexPointer].y;
		//vArray[vertexPointer*3+2] = vertices[vertexPointer].z;
		vectorVertex.push_back(vertices[vertexPointer].x);
		vectorVertex.push_back(vertices[vertexPointer].y);
		vectorVertex.push_back(vertices[vertexPointer].z);
	}

	//for (int i = 0; i < indices.size(); i++)
	{
		//iArray[i] = indices[i];
	}

	std::vector<float> vectorTexture;
	int tSize = vertices.size() * 2;
	for (int i = 0; i < tSize; i++)
	{
		vectorTexture.push_back(tArray[i]);
	}

	std::vector<float> vectorNormal;
	int nSize = vertices.size() * 3;
	for (int i = 0; i < nSize; i++)
	{
		vectorNormal.push_back(nArray[i]);
	}

	free(tArray);
	free(nArray);

	RawModel model = loadToVAO(&vectorVertex, &vectorTexture, &vectorNormal, &indices);

	vertices.clear();
	vertices.shrink_to_fit();
	textures.clear();
	textures.shrink_to_fit();
	normals.clear();
	normals.shrink_to_fit();
	indices.clear();
	indices.shrink_to_fit();

	return model;
}

void processVertex(char** vertexData, 
	std::vector<int>* indices, 
	std::vector<Vector2f>* textures, 
	std::vector<Vector3f>* normals, 
	float* textureArray, 
	float* normalsArray)
{
	int vd0 = atoi(vertexData[0]) - 1;
	int vd1 = atoi(vertexData[1]) - 1;
	int vd2 = atoi(vertexData[2]) - 1;

	int currentVertexPointer = vd0;
	(*indices).push_back(currentVertexPointer);

	Vector2f currentTex = (*textures)[vd1];
	textureArray[currentVertexPointer*2]     =     currentTex.x;
	textureArray[currentVertexPointer*2 + 1] = 1 - currentTex.y;

	Vector3f currentNorm = (*normals)[vd2];
	normalsArray[currentVertexPointer*3]     = currentNorm.x;
	normalsArray[currentVertexPointer*3 + 1] = currentNorm.y;
	normalsArray[currentVertexPointer*3 + 2] = currentNorm.z;
}

/* Parse a line and return an array of the
individual tokens */

char ** split(char *line, char delim)
{
	/* Scan through line to find the number of tokens */
	int numTokens = 0;
	int index = 0;
	int inToken = 0;

	while (line[index] != 0)
	{
		if (line[index] != delim && inToken == 0)
		{
			inToken = 1;
			numTokens += 1;
		}
		else if (line[index] == delim)
		{
			inToken = 0;
		}
		index += 1;
	}

	/* Get memory to store the data */
	char ** parsedData = (char**)malloc(sizeof(char*)*(numTokens + 1));

	/* Scan through line to fill parsedData
	and set 0 characters after tokens*/
	index = 0;
	inToken = 0;
	int tokenNum = 0;

	while (line[index] != 0)
	{
		if (line[index] != delim && inToken == 0)
		{
			parsedData[tokenNum] = &line[index];
			tokenNum += 1;
			inToken = 1;
		}
		else if (line[index] == delim)
		{
			if (inToken == 1)
			{
				line[index] = 0;
			}
			inToken = 0;
		}
		index += 1;
	}

	parsedData[numTokens] = NULL;

	splitLength = numTokens;

	return parsedData;
}
