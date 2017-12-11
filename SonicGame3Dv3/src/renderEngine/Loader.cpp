#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <SOIL/SOIL.h>

#include <vector>  //for std::vector
#include <list>
#include <string>  //for std::string
#include <iostream>
#include <cmath>

#include "renderEngine.h"

#include "../models/models.h"

std::list<GLuint> vaos;
std::list<GLuint> vbos;
std::list<GLuint> textures;

GLuint createVAO();
void storeDataInAttributeList(int, int, std::vector<float>*);
void unbindVAO();
void bindIndiciesBuffer(std::vector<int>*);
float* storeDataInFloatBuffer(std::vector<float>*);
int* storeDataInIntBuffer(std::vector<int>*);

RawModel Loader_loadToVAO(std::vector<float>* positions, std::vector<float>* textureCoords, std::vector<float>* normals, std::vector<int>* indicies)
{
	GLuint vaoID = createVAO();
	bindIndiciesBuffer(indicies);
	storeDataInAttributeList(0, 3, positions);
	storeDataInAttributeList(1, 2, textureCoords);
	storeDataInAttributeList(2, 3, normals);
	unbindVAO();
	return RawModel(vaoID, (*indicies).size());
}

GLuint Loader_loadTexture(char* fileName)
{
	GLuint textureID = 0;
	glGenTextures(1, &textureID);
	textures.push_back(textureID);
	//std::fprintf(stdout, "	generated tex id #%d\n", textureID);

	int width, height;
	unsigned char* image = SOIL_load_image(fileName, &width, &height, 0, SOIL_LOAD_RGBA);

	if (image == 0)
	{
		const char* err = SOIL_last_result();
		std::fprintf(stdout, "Error loading image '%s', because '%s'\n", fileName, err);
		return 0;
	}

	glBindTexture(GL_TEXTURE_2D, textureID);

	//Texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	//Texel interpolation
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//create
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

	//create mipmap
	glGenerateMipmap(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, 0.0f); //set to 0 if using anisotropic, around -0.4f if not

	if (glfwExtensionSupported("GL_EXT_texture_filter_anisotropic"))
	{
		//Not sure why these aren't defined... but I've spent too much time trying to fix it.
		const GLuint GL_TEXTURE_MAX_ANISOTROPY_EXT  = 0x84FE;
		const GLuint GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT = 0x84FF;

		float maxAnisotropyLevel;
		glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &maxAnisotropyLevel);
		float amountToUse = fmin(4.0f, maxAnisotropyLevel);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, amountToUse);
	}

	SOIL_free_image_data(image);

	glBindTexture(GL_TEXTURE_2D, 0);
	

	return textureID;
}

GLuint Loader_loadTextureWORKS(char* fileName)
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
	glGenBuffers(1, &vboID);
	vbos.push_back(vboID);
	glBindBuffer(GL_ARRAY_BUFFER, vboID);

	//float buffer
	float* buffer = storeDataInFloatBuffer(data);

	glBufferData(GL_ARRAY_BUFFER, (*data).size() * sizeof(float), (GLvoid *)buffer, GL_STATIC_DRAW); //std::fprintf(stdout, "glBufferData(GL_ARRAY_BUFFER, data.size(), (GLvoid *)buffer, GL_STATIC_DRAW);\n"); //this might not work 
	glVertexAttribPointer(attributeNumber, coordinateSize, GL_FLOAT, GL_FALSE, 0, 0); //std::fprintf(stdout, "glVertexAttribPointer(attributeNumber, 3, GL_FLOAT, false, 0, 0);\n");
	glBindBuffer(GL_ARRAY_BUFFER, 0); //std::fprintf(stdout, "glBindBuffer(GL_ARRAY_BUFFER, 0);\n");

	free(buffer);
}

void unbindVAO()
{
	glBindVertexArray(0);
}

void Loader_cleanUp()
{
	for (auto vaoID : vaos)
	{
		glDeleteVertexArrays(1, &vaoID);
	}
	vaos.clear();

	for (auto vboID : vbos)
	{
		glDeleteBuffers(1, &vboID);
	}
	vbos.clear();

	for (auto texID : textures)
	{
		glDeleteTextures(1, &texID);
	}
	textures.clear();
}

void Loader_deleteVAO(GLuint vaoID)
{
	glDeleteVertexArrays(1, &vaoID);
	vaos.remove(vaoID);
}

void Loader_deleteVBO(GLuint vboID)
{
	glDeleteBuffers(1, &vboID);
	vbos.remove(vboID);
}

void Loader_deleteTexture(GLuint texID)
{
	glDeleteTextures(1, &texID);
	textures.remove(texID);
}

void Loader_deleteTexturedModels(std::list<TexturedModel*>* tm)
{
	for (auto model : (*tm))
	{
		model->deleteMe();
	}
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