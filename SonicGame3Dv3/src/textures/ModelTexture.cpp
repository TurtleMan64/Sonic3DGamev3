#include <glad/glad.h>
#include <iostream>

#include "textures.h"
#include "../renderEngine/renderEngine.h"

ModelTexture::ModelTexture()
{
	//std::fprintf(stdout, "model texture being constructed wrongly\n");
}

ModelTexture::ModelTexture(GLuint texID)
{
	this->texID = texID;
	this->shineDamper = 1;
	this->reflectivity = 0;
	this->hasTransparency = 0;
	this->useFakeLighting = 0;
	//std::fprintf(stdout, "correct\n");
}

int ModelTexture::getID()
{
	return texID;
}

float ModelTexture::getShineDamper()
{
	return shineDamper;
}
void ModelTexture::setShineDamper(float newShineDamper)
{
	this->shineDamper = newShineDamper;
}

float ModelTexture::getReflectivity()
{
	return reflectivity;
}
void ModelTexture::setReflectivity(float newReflectivity)
{
	this->reflectivity = newReflectivity;
}

int ModelTexture::getHasTransparency()
{
	return hasTransparency;
}
void ModelTexture::setHasTransparency(int newHasTransparency)
{
	this->hasTransparency = newHasTransparency;
}

int ModelTexture::getUsesFakeLighting()
{
	return useFakeLighting;
}
void ModelTexture::setUsesFakeLighting(int newUseFakeLighting)
{
	this->useFakeLighting = newUseFakeLighting;
}

void ModelTexture::deleteMe()
{
	Loader_deleteTexture(texID);
}