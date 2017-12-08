#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <vector>  //for std::vector
#include <string>  //for std::string
#include <iostream>

#include "renderEngine.h"

#include "../models/models.h"

std::vector<GLuint> vaos;
std::vector<GLuint> vbos;
std::vector<GLuint> textures;

GLuint createVAO();
void storeDataInAttributeList(int, int, std::vector<float>*);
void unbindVAO();
void bindIndiciesBuffer(std::vector<int>*);
float* storeDataInFloatBuffer(std::vector<float>*);
int* storeDataInIntBuffer(std::vector<int>*);

RawModel loadToVAO(std::vector<float>* positions, std::vector<float>* textureCoords, std::vector<float>* normals, std::vector<int>* indicies)
{
	GLuint vaoID = createVAO();
	bindIndiciesBuffer(indicies);
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
	storeDataInAttributeList(2, 3, normals);
	unbindVAO();
	return RawModel(vaoID, (*indicies).size());
}

GLuint loadTexture(char* fileName)
{
	GLuint textureID = 0;
	glGenTextures(1, &textureID);
	textures.push_back(textureID);
	//std::fprintf(stdout, "	generated tex id #%d\n", textureID);

	int width, height;
	unsigned char* image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGB);

	if (image == 0)
	{
		const char* err = SOIL_last_result();
		std::fprintf(stdout, "Error loading image: '%s'\n", err);
		return 0;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);
	// WRAP OR NOT TO WRAP, THAT IS THE QUESTION
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// ME DOEST SMOOTH OR SHARP? SHARP!
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	// MIP MAP!
	//glGenerateMipmap(textureID); //caused a gl error 1280

	// MAKE!
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);

	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);
	

	return textureID;
}

GLuint loadTextureWORKS(char* fileName)
{
	std::string name = "res/img_test.png";
	GLuint tex_ID;
	tex_ID = SOIL_load_OGL_texture(
		name.c_str(),
		SOIL_LOAD_AUTO,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_POWER_OF_TWO
		| SOIL_FLAG_MIPMAPS
		//| SOIL_FLAG_MULTIPLY_ALPHA
		//| SOIL_FLAG_COMPRESS_TO_DXT
		| SOIL_FLAG_DDS_LOAD_DIRECT
		//| SOIL_FLAG_NTSC_SAFE_RGB
		//| SOIL_FLAG_CoCg_Y
		//| SOIL_FLAG_TEXTURE_RECTANGLE
	);

	return tex_ID;
}

GLuint createVAO()
{
	GLuint vaoID = 0;
	glGenVertexArrays(1, &vaoID); //std::fprintf(stdout, "glGenVertexArrays(1, &vaoID);\n");
	vaos.push_back(vaoID);
	glBindVertexArray(vaoID); //std::fprintf(stdout, "glBindVertexArray(vaoID);\n");
	return vaoID;
}

void storeDataInAttributeList(int attributeNumber, int coordinateSize, std::vector<float>* data)
{
	GLuint vboID = 0;
	glGenBuffers(1, &vboID); //std::fprintf(stdout, "glGenBuffers(1, &vboID);\n");
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID); //std::fprintf(stdout, "glBindBuffer(GL_ARRAY_BUFFER, vboID);\n");

	//float buffer
	float* buffer = storeDataInFloatBuffer(data);

	//std::fprintf(stdout, "size:  %d\n", data.size());
	glBufferData(GL_ARRAY_BUFFER, (*data).size() * sizeof(float), (GLvoid *)buffer, GL_STATIC_DRAW); //std::fprintf(stdout, "glBufferData(GL_ARRAY_BUFFER, data.size(), (GLvoid *)buffer, GL_STATIC_DRAW);\n"); //this might not work 
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0); //std::fprintf(stdout, "glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, false, 0, 0);\n");
	glBindBuffer(GL_ARRAY_BUFFER, 0); //std::fprintf(stdout, "glBindBuffer(GL_ARRAY_BUFFER, 0);\n");

	free(buffer);
}

void unbindVAO()
{
	glBindVertexArray(0); //std::fprintf(stdout, "glBindVertexArray(0);\n");
}

void cleanUp()
{
	glDeleteVertexArrays(vaos.size(), &vaos[0]); //std::fprintf(stdout, "glDeleteVertexArrays(vaos.size(), &vaos[0]);\n");
	vaos.clear();
	vaos.shrink_to_fit();

	glDeleteBuffers(vbos.size(), &vbos[0]); //std::fprintf(stdout, "glDeleteVertexArrays(vbos.size(), &vbos[0]);\n");
	vbos.clear();
	vbos.shrink_to_fit();

	glDeleteTextures(textures.size(), &textures[0]); //std::fprintf(stdout, "glDeleteVertexArrays(vbos.size(), &vbos[0]);\n");
	textures.clear();
	textures.shrink_to_fit();
}

void bindIndiciesBuffer(std::vector<int>* indicies)
{
	GLuint vboID = 0;
	glGenBuffers(1, &vboID); //std::fprintf(stdout, "glGenBuffers(1, &vboID);\n");
	vbos.push_back(vboID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID); //std::fprintf(stdout, "glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vboID);\n");

	int* buffer = storeDataInIntBuffer(indicies);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, (*indicies).size() * sizeof(int), buffer, GL_STATIC_DRAW); //std::fprintf(stdout, "glBufferData(GL_ELEMENT_ARRAY_BUFFER, indicies.size(), buffer, GL_STATIC_DRAW);\n");

	free(buffer);
}

float* storeDataInFloatBuffer(std::vector<float>* data)
{
	float* buffer = (float *)malloc(sizeof(float)*(*data).size());
	for (size_t i = 0; i < (*data).size(); i++)
	{
		buffer[i] = (*data)[i];
	}
	
	return buffer;
}

int* storeDataInIntBuffer(std::vector<int>* data)
{
	int* buffer = (int *)malloc(sizeof(int)*(*data).size());
	for (size_t i = 0; i < (*data).size(); i++)
	{
		buffer[i] = (*data)[i];
	}

	return buffer;
}