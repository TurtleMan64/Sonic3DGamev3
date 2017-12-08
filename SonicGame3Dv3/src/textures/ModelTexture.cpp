#include <glad/glad.h>
#include <iostream>

#include "textures.h"

ModelTexture::ModelTexture()
{
	//std::fprintf(stdout, "model texture being constructed wrongly\n");
}

ModelTexture::ModelTexture(GLuint texID)
{
	this->texID = texID;
	this->shineDamper = 1;
	this->reflectivity = 0;
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