#include <glad/glad.h>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <list>

//#include <ctime>

#include "objLoader.h"
#include "../models/models.h"
#include "../renderEngine/renderEngine.h"
#include "../toolbox/vector.h"
#include "vertex.h"
#include "../engineTester/main.h"
#include "../toolbox/split.h"
#include "../collision/collisionmodel.h"
#include "../collision/triangle3d.h"
#include "fakeTexture.h"

void parseMtl(std::string filePath, std::string fileName);

//void processVertexOLD(char**, 
//	std::vector<int>*, 
//	std::vector<Vector2f>*, 
//	std::vector<Vector3f>*, 
//	float*, 
//	float*);

void processVertex(char** vertex,
	std::vector<Vertex*>* vertices,
	std::vector<int>* indices);

void dealWithAlreadyProcessedVertex(Vertex*, 
	int, 
	int, 
	std::vector<int>*, 
	std::vector<Vertex*>*);

void removeUnusedVertices(std::vector<Vertex*>* vertices);

float convertDataToArrays(std::vector<Vertex*>* vertices, std::vector<Vector2f>* textures,
	std::vector<Vector3f>* normals, std::vector<float>* verticesArray, std::vector<float>* texturesArray,
	std::vector<float>* normalsArray);

std::vector<ModelTexture> modelTextures;

std::vector<ModelTexture> modelTexturesList;
std::vector<std::string> textureNamesList;

std::list<TexturedModel*>* loadObjModel(std::string filePath, std::string fileName)
{
	std::ifstream file(filePath+fileName);
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file '%s'\n", (filePath + fileName).c_str());
		file.close();
		return nullptr;
	}

	std::string line;

	std::vector<Vertex*> vertices;
	std::vector<Vector2f> textures;
	std::vector<Vector3f> normals;
	std::vector<int> indices;

	std::vector<RawModel> rawModelsList;

	int foundFaces = 0;


	//clock_t t;
	//t = clock();
	//printf("Calculating total...\n");

	while (!file.eof())
	{
		getline(file, line);

		char lineBuf[256]; //Buffer to copy line into
		memset(lineBuf, 0, 256);
		memcpy(lineBuf, line.c_str(), line.size());

		int splitLength = 0;
		char** lineSplit = split(lineBuf, ' ', &splitLength);

		if (splitLength > 0)
		{
			if (foundFaces == 0)
			{
				//Find the mtl filename
				if (strcmp(lineSplit[0], "mtllib") == 0)
				{
					parseMtl(filePath, lineSplit[1]);
				}
				else if (strcmp(lineSplit[0], "v") == 0)
				{
					std::string p1(lineSplit[1]);
					std::string p2(lineSplit[2]);
					std::string p3(lineSplit[3]);
					Vector3f vertex(std::stof(p1, nullptr), std::stof(p2, nullptr), std::stof(p3, nullptr));
					Vertex* newVertex = new Vertex(vertices.size(), &vertex);
					Global::countNew++;
					vertices.push_back(newVertex);
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
				else if (strcmp(lineSplit[0], "usemtl") == 0) //first usetml found, before any faces entered
				{
					for (unsigned int i = 0; i < textureNamesList.size(); i++) //search for the right texture to use based off its name
					{
						std::string testName = textureNamesList[i];
						if (testName == lineSplit[1]) //we've found the right texture!
						{
							modelTextures.push_back(modelTexturesList[i]); //put a copy of the texture into modelTextures
						}
					}
				}
				else if (strcmp(lineSplit[0], "f") == 0)
				{
					foundFaces = 1;
				}
			}

			if (foundFaces == 1)
			{
				if (strcmp(lineSplit[0], "f") == 0)
				{
					int dummy = 0;
					char** vertex1 = split(lineSplit[1], '/', &dummy);
					char** vertex2 = split(lineSplit[2], '/', &dummy);
					char** vertex3 = split(lineSplit[3], '/', &dummy);

					processVertex(vertex1, &vertices, &indices);
					processVertex(vertex2, &vertices, &indices);
					processVertex(vertex3, &vertices, &indices);

					free(vertex1);
					free(vertex2);
					free(vertex3);
				}
				else if (strcmp(lineSplit[0], "usemtl") == 0 && (vertices.size() > 0)) //found another new material, so save the previous model and start a new one
				{
					for (unsigned int i = 0; i < textureNamesList.size(); i++) //search for the right texture to use based off its name
					{
						std::string testName = textureNamesList[i];
						if (testName == lineSplit[1]) //we've found the right texture!
						{
							modelTextures.push_back(modelTexturesList[i]); //put a copy of the texture into modelTextures
						}
					}

					//save the model we've been building so far...
					removeUnusedVertices(&vertices);
					std::vector<float> verticesArray;
					std::vector<float> texturesArray;
					std::vector<float> normalsArray;

					float furthest = convertDataToArrays(&vertices, &textures, &normals, &verticesArray, &texturesArray, &normalsArray);
					RawModel newRaw = Loader_loadToVAO(&verticesArray, &texturesArray, &normalsArray, &indices);

					rawModelsList.push_back(newRaw); //put a copy of the model into rawModelsList
					indices.clear();
				}
			}
		}
		free(lineSplit);
	}
	file.close();

	//t = clock() - t;
	//printf("Total: It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

	removeUnusedVertices(&vertices);

	std::vector<float> verticesArray;
	std::vector<float> texturesArray;
	std::vector<float> normalsArray;

	float furthest = convertDataToArrays(&vertices, &textures, &normals, &verticesArray, &texturesArray, &normalsArray);
	RawModel newRaw = Loader_loadToVAO(&verticesArray, &texturesArray, &normalsArray, &indices);

	rawModelsList.push_back(newRaw); //put a copy of the final model into rawModelsList

	//go through rawModelsList and modelTextures to construct the final TexturedModel list
	std::list<TexturedModel*>* tmList = new std::list<TexturedModel*>();
	Global::countNew++;
	for (unsigned int i = 0; i < rawModelsList.size(); i++)
	{
		TexturedModel* tm = new TexturedModel(&rawModelsList[i], &modelTextures[i]);
		Global::countNew++;
		tmList->push_back(tm);
	}

	for (auto vertex : vertices)
	{
		delete vertex;
		Global::countDelete++;
	}

	line.clear();

	vertices.clear();
	textures.clear();
	normals.clear();
	indices.clear();

	rawModelsList.clear();
	modelTextures.clear();
	modelTexturesList.clear();
	textureNamesList.clear();

	return tmList;
}

void parseMtl(std::string filePath, std::string fileName)
{
	//array that obj will fill in, using our generated arrays
	modelTextures.clear();

	//arrays that we fill in, from the mtl file
	modelTexturesList.clear();
	textureNamesList.clear();

	std::ifstream file(filePath+fileName);
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file '%s'\n", (filePath + fileName).c_str());
		file.close();
		return;
	}

	//clock_t t;
	//t = clock();
	//printf("Calculating MTL...\n");

	std::string line;

	//default values
	float currentShineDamperValue = 0.0f;
	float currentReflectivityValue = 0.0f;
	float currentTransparencyValue = 1.0f;
	float currentFakeLightingValue = 1.0f;

	while (!file.eof())
	{
		getline(file, line);

		char lineBuf[256]; //Buffer to copy line into
		memset(lineBuf, 0, 256);
		memcpy(lineBuf, line.c_str(), line.size());

		int splitLength = 0;
		char** lineSplit = split(lineBuf, ' ', &splitLength);

		if (splitLength > 0)
		{
			if (strcmp(lineSplit[0], "newmtl") == 0) //new material found, add its name to array
			{
				textureNamesList.push_back(lineSplit[1]);
				currentShineDamperValue = 0.0f;
				currentReflectivityValue = 0.0f;
				currentTransparencyValue = 1.0f;
				currentFakeLightingValue = 1.0f;
			}
			else if (strcmp(lineSplit[0], "\tmap_Kd") == 0) //end of material found, generate it with all its attrributes
			{
				std::string imageFilenameString = filePath+lineSplit[1];
				char* fname = (char*)imageFilenameString.c_str();
				ModelTexture newTexture(Loader_loadTexture(fname)); //generate new texture
				newTexture.setShineDamper(currentShineDamperValue);
				newTexture.setReflectivity(currentReflectivityValue);
				newTexture.setHasTransparency(0);
				newTexture.setUsesFakeLighting(0);
				if (currentTransparencyValue > 0.5f)
				{
					newTexture.setHasTransparency(1);
				}
				if (currentFakeLightingValue < 1.0f)
				{
					newTexture.setUsesFakeLighting(1);
				}
				modelTexturesList.push_back(newTexture); //put a copy of newTexture into the list
			}
			else if (strcmp(lineSplit[0], "\tNs") == 0)
			{
				currentShineDamperValue = std::stof(lineSplit[1]);
			}
			else if (strcmp(lineSplit[0], "\tNi") == 0)
			{
				currentReflectivityValue = std::stof(lineSplit[1]);
			}
			else if (strcmp(lineSplit[0], "\tTr") == 0)
			{
				currentTransparencyValue = std::stof(lineSplit[1]);
			}
			else if (strcmp(lineSplit[0], "\td") == 0)
			{
				currentFakeLightingValue = std::stof(lineSplit[1]);
			}
		}

		free(lineSplit);
	}
	file.close();

	//t = clock() - t;
	//printf("MTL: It took me %d clicks (%f seconds).\n", t, ((float)t) / CLOCKS_PER_SEC);

}



std::list<TexturedModel*>* loadObjModelWithMTL(std::string filePath, std::string fileNameOBJ, std::string fileNameMTL)
{
	std::ifstream file(filePath + fileNameOBJ);
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file '%s'\n", (filePath + fileNameOBJ).c_str());
		file.close();
		return nullptr;
	}

	std::string line;

	std::vector<Vertex*> vertices;
	std::vector<Vector2f> textures;
	std::vector<Vector3f> normals;
	std::vector<int> indices;

	std::vector<RawModel> rawModelsList;

	int foundFaces = 0;

	parseMtl(filePath, fileNameMTL);

	while (!file.eof())
	{
		getline(file, line);

		char lineBuf[256]; //Buffer to copy line into
		memset(lineBuf, 0, 256);
		memcpy(lineBuf, line.c_str(), line.size());

		int splitLength = 0;
		char** lineSplit = split(lineBuf, ' ', &splitLength);

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
					Vertex* newVertex = new Vertex(vertices.size(), &vertex);
					Global::countNew++;
					vertices.push_back(newVertex);
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
				else if (strcmp(lineSplit[0], "usemtl") == 0) //first usetml found, before any faces entered
				{
					for (unsigned int i = 0; i < textureNamesList.size(); i++) //search for the right texture to use based off its name
					{
						std::string testName = textureNamesList[i];
						if (testName == lineSplit[1]) //we've found the right texture!
						{
							modelTextures.push_back(modelTexturesList[i]); //put a copy of the texture into modelTextures
						}
					}
				}
				else if (strcmp(lineSplit[0], "f") == 0)
				{
					foundFaces = 1;
				}
			}

			if (foundFaces == 1)
			{
				if (strcmp(lineSplit[0], "f") == 0)
				{
					int dummy = 0;
					char** vertex1 = split(lineSplit[1], '/', &dummy);
					char** vertex2 = split(lineSplit[2], '/', &dummy);
					char** vertex3 = split(lineSplit[3], '/', &dummy);

					processVertex(vertex1, &vertices, &indices);
					processVertex(vertex2, &vertices, &indices);
					processVertex(vertex3, &vertices, &indices);

					free(vertex1);
					free(vertex2);
					free(vertex3);
				}
				else if (strcmp(lineSplit[0], "usemtl") == 0 && (vertices.size() > 0)) //found another new material, so save the previous model and start a new one
				{
					for (unsigned int i = 0; i < textureNamesList.size(); i++) //search for the right texture to use based off its name
					{
						std::string testName = textureNamesList[i];
						if (testName == lineSplit[1]) //we've found the right texture!
						{
							modelTextures.push_back(modelTexturesList[i]); //put a copy of the texture into modelTextures
						}
					}

					//save the model we've been building so far...
					removeUnusedVertices(&vertices);
					std::vector<float> verticesArray;
					std::vector<float> texturesArray;
					std::vector<float> normalsArray;

					float furthest = convertDataToArrays(&vertices, &textures, &normals, &verticesArray, &texturesArray, &normalsArray);
					RawModel newRaw = Loader_loadToVAO(&verticesArray, &texturesArray, &normalsArray, &indices);

					rawModelsList.push_back(newRaw); //put a copy of the model into rawModelsList
					indices.clear();
				}
			}
		}
		free(lineSplit);
	}
	file.close();

	removeUnusedVertices(&vertices);

	std::vector<float> verticesArray;
	std::vector<float> texturesArray;
	std::vector<float> normalsArray;

	float furthest = convertDataToArrays(&vertices, &textures, &normals, &verticesArray, &texturesArray, &normalsArray);
	RawModel newRaw = Loader_loadToVAO(&verticesArray, &texturesArray, &normalsArray, &indices);

	rawModelsList.push_back(newRaw); //put a copy of the final model into rawModelsList

	//go through rawModelsList and modelTextures to construct the final TexturedModel list
	std::list<TexturedModel*>* tmList = new std::list<TexturedModel*>();
	Global::countNew++;
	for (unsigned int i = 0; i < rawModelsList.size(); i++)
	{
		TexturedModel* tm = new TexturedModel(&rawModelsList[i], &modelTextures[i]);
		Global::countNew++;
		tmList->push_back(tm);
	}

	for (auto vertex : vertices)
	{
		delete vertex;
		Global::countDelete++;
	}

	line.clear();

	vertices.clear();
	textures.clear();
	normals.clear();
	indices.clear();

	rawModelsList.clear();
	modelTextures.clear();
	modelTexturesList.clear();
	textureNamesList.clear();

	return tmList;
}

/*
RawModel loadObjModelOG(char* fileName)
{
	std::ifstream file(fileName);
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file '%s'\n", fileName);
		file.close();
		//ModelData temp(nullptr, nullptr, nullptr, nullptr, 0);
		RawModel temp;
		return temp;
	}

	std::string line;

	std::vector<Vertex*> vertices;
	std::vector<Vector2f> textures;
	std::vector<Vector3f> normals;
	std::vector<int> indices;

	int foundFaces = 0;

	while (!file.eof())
	{
		getline(file, line);

		char lineBuf[256]; //Buffer to copy line into
		memset(lineBuf, 0, 256);
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
					Vertex* newVertex = new Vertex(vertices.size(), &vertex);
					vertices.push_back(newVertex);
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
					foundFaces = 1;
				}
			}

			if (foundFaces == 1)
			{
				//std::fprintf(stdout, "'%s'\n", lineSplit[1]);
				if (strcmp(lineSplit[0], "f") == 0)
				{
					char** vertex1 = split(lineSplit[1], '/');
					char** vertex2 = split(lineSplit[2], '/');
					char** vertex3 = split(lineSplit[3], '/');

					processVertex(vertex1, &vertices, &indices);
					processVertex(vertex2, &vertices, &indices);
					processVertex(vertex3, &vertices, &indices);

					free(vertex1);
					free(vertex2);
					free(vertex3);
				}
			}
		}
		free(lineSplit);
	}
	file.close();

	removeUnusedVertices(&vertices);

	std::vector<float> verticesArray;
	std::vector<float> texturesArray;
	std::vector<float> normalsArray;

	float furthest = convertDataToArrays(&vertices, &textures, &normals, &verticesArray, &texturesArray, &normalsArray);
	//ModelData data(&verticesArray, &texturesArray, &normalsArray, &indices, furthest);
	RawModel raaaw = Loader_loadToVAO(&verticesArray, &texturesArray, &normalsArray, &indices);

	for (auto vertex : vertices)
	{
		delete vertex;
	}

	return raaaw;
}
*/

void processVertex(char** vertex,
	std::vector<Vertex*>* vertices,
	std::vector<int>* indices)
{
	int index = atoi(vertex[0]) - 1;
	int textureIndex = atoi(vertex[1]) - 1;
	int normalIndex = atoi(vertex[2]) - 1;

	Vertex* currentVertex = (*vertices)[index]; //check bounds on this?
	if (currentVertex->isSet() == 0)
	{
		currentVertex->setTextureIndex(textureIndex);
		currentVertex->setNormalIndex(normalIndex);
		indices->push_back(index);
	}
	else
	{
		dealWithAlreadyProcessedVertex(currentVertex, textureIndex, normalIndex, indices, vertices);
	}
}



void dealWithAlreadyProcessedVertex(Vertex* previousVertex,
	int newTextureIndex,
	int newNormalIndex,
	std::vector<int>* indices,
	std::vector<Vertex*>* vertices)
{
	if (previousVertex->hasSameTextureAndNormal(newTextureIndex, newNormalIndex))
	{
		indices->push_back(previousVertex->getIndex());
	}
	else
	{
		Vertex* anotherVertex = previousVertex->getDuplicateVertex();
		if (anotherVertex != nullptr)
		{
			dealWithAlreadyProcessedVertex(anotherVertex, newTextureIndex, newNormalIndex, indices, vertices);
		}
		else
		{
			Vertex* duplicateVertex = new Vertex(vertices->size(), previousVertex->getPosition());
			Global::countNew++;
			duplicateVertex->setTextureIndex(newTextureIndex);
			duplicateVertex->setNormalIndex(newNormalIndex);

			previousVertex->setDuplicateVertex(duplicateVertex);
			vertices->push_back(duplicateVertex);
			indices->push_back(duplicateVertex->getIndex());
		}
	}
}


float convertDataToArrays(std::vector<Vertex*>* vertices, std::vector<Vector2f>* textures,
	std::vector<Vector3f>* normals, std::vector<float>* verticesArray, std::vector<float>* texturesArray,
	std::vector<float>* normalsArray)
{
	float furthestPoint = 0;
	for (auto currentVertex : (*vertices))
	{
		//Vertex currentVertex = (*vertices)[i];
		if (currentVertex->getLength() > furthestPoint)
		{
			furthestPoint = currentVertex->getLength();
		}
		Vector3f* position = currentVertex->getPosition();
		Vector2f* textureCoord = &(*textures)[currentVertex->getTextureIndex()];
		Vector3f* normalVector = &(*normals)[currentVertex->getNormalIndex()];
		verticesArray->push_back(position->x);
		verticesArray->push_back(position->y);
		verticesArray->push_back(position->z);
		texturesArray->push_back(textureCoord->x);
		texturesArray->push_back(1 - textureCoord->y);
		normalsArray->push_back(normalVector->x);
		normalsArray->push_back(normalVector->y);
		normalsArray->push_back(normalVector->z);
	}
	return furthestPoint;
}


/*
RawModel loadObjModelOLD(char* fileName)
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

					processVertexOLD(vertex1, &indices, &textures, &normals, tArray, nArray);
					processVertexOLD(vertex2, &indices, &textures, &normals, tArray, nArray);
					processVertexOLD(vertex3, &indices, &textures, &normals, tArray, nArray);

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

					processVertexOLD(vertex1, &indices, &textures, &normals, tArray, nArray);
					processVertexOLD(vertex2, &indices, &textures, &normals, tArray, nArray);
					processVertexOLD(vertex3, &indices, &textures, &normals, tArray, nArray);

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

	RawModel model = Loader_loadToVAO(&vectorVertex, &vectorTexture, &vectorNormal, &indices);

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
*/




void removeUnusedVertices(std::vector<Vertex*>* vertices)
{
	for (auto vertex : (*vertices))
	{
		if ((*vertex).isSet() == 0)
		{
			(*vertex).setTextureIndex(0);
			(*vertex).setNormalIndex(0);
		}
	}
}


/*
void processVertexOLD(char** vertexData, 
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
*/


CollisionModel* loadCollisionModel(std::string filePath, std::string fileName)
{
	CollisionModel* collisionModel = new CollisionModel();
	Global::countNew++;
	std::list<FakeTexture*> fakeTextures;

	char currType = 0;
	int currSound = 0;
	char currParticle = 0;

	std::ifstream file("res/" + filePath + fileName + ".obj");
	if (!file.is_open())
	{
		std::fprintf(stdout, "Error: Cannot load file '%s'\n", ("res/" + filePath + fileName + ".obj").c_str());
		file.close();
		return collisionModel;
	}

	std::string line;

	std::vector<Vector3f> vertices;



	while (!file.eof())
	{
		getline(file, line);

		char lineBuf[256]; //Buffer to copy line into
		memset(lineBuf, 0, 256);
		memcpy(lineBuf, line.c_str(), line.size());

		int splitLength = 0;
		char** lineSplit = split(lineBuf, ' ', &splitLength);

		if (splitLength > 0)
		{
			if (strcmp(lineSplit[0], "v") == 0)
			{
				Vector3f vertex;
				vertex.x = std::stof(lineSplit[1]);
				vertex.y = std::stof(lineSplit[2]);
				vertex.z = std::stof(lineSplit[3]);
				vertices.push_back(vertex);
			}
			else if (strcmp(lineSplit[0], "f") == 0)
			{
				int len = 0;
				char** vertex1 = split(lineSplit[1], '/', &len);
				char** vertex2 = split(lineSplit[2], '/', &len);
				char** vertex3 = split(lineSplit[3], '/', &len);

				Vector3f* vert1 = &vertices[std::stoi(vertex1[0]) - 1];
				Vector3f* vert2 = &vertices[std::stoi(vertex2[0]) - 1];
				Vector3f* vert3 = &vertices[std::stoi(vertex3[0]) - 1];

				Triangle3D* tri = new Triangle3D(vert1, vert2, vert3, currType, currSound, currParticle);
				Global::countNew++;

				collisionModel->triangles.push_back(tri);

				free(vertex1);
				free(vertex2);
				free(vertex3);
			}
			else if (strcmp(lineSplit[0], "usemtl") == 0)
			{
				currType = 0;
				currSound = -1;
				currParticle = 0;

				for (FakeTexture* dummy : fakeTextures)
				{
					if (dummy->name == lineSplit[1])
					{
						currType = dummy->type;
						currType = dummy->sound;
						currType = dummy->particle;
					}
				}
			}
			else if (strcmp(lineSplit[0], "mtllib") == 0)
			{
				std::ifstream fileMTL("res/" + filePath + lineSplit[1]);
				if (!fileMTL.is_open())
				{
					std::fprintf(stdout, "Error: Cannot load file '%s'\n", ("res/" + filePath + lineSplit[1]).c_str());
					fileMTL.close();
					file.close();
					return collisionModel;
				}

				std::string lineMTL;

				while (!fileMTL.eof())
				{
					getline(fileMTL, lineMTL);

					char lineBufMTL[256]; //Buffer to copy line into
					memset(lineBufMTL, 0, 256);
					memcpy(lineBufMTL, lineMTL.c_str(), lineMTL.size());

					int splitLengthMTL = 0;
					char** lineSplitMTL = split(lineBufMTL, ' ', &splitLengthMTL);

					if (splitLengthMTL > 0)
					{
						if (strcmp(lineSplitMTL[0], "newmtl") == 0)
						{
							FakeTexture* fktex = new FakeTexture();
							Global::countNew++;
							fktex->name = lineSplitMTL[1];
							fakeTextures.push_back(fktex);
						}
						else if (strcmp(lineSplitMTL[0], "type") == 0 ||
								 strcmp(lineSplitMTL[0], "\ttype") == 0)
						{
							fakeTextures.back()->type = (char)round(std::stof(lineSplitMTL[1]));
						}
						else if (strcmp(lineSplitMTL[0], "sound") == 0 ||
								 strcmp(lineSplitMTL[0], "\tsound") == 0)
						{
							fakeTextures.back()->sound = (int)round(std::stof(lineSplitMTL[1]));
						}
						else if (strcmp(lineSplitMTL[0], "particle") == 0 ||
								 strcmp(lineSplitMTL[0], "\tparticle") == 0)
						{
							fakeTextures.back()->particle = (char)round(std::stof(lineSplitMTL[1]));
						}
					}
					free(lineSplitMTL);
				}
				fileMTL.close();
			}
		}
		free(lineSplit);
	}
	file.close();

	collisionModel->generateMinMaxValues();

	for (FakeTexture* dummy : fakeTextures)
	{
		delete dummy;
		Global::countDelete++;
	}

	return collisionModel;
}