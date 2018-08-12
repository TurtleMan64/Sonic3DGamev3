#include <glad/glad.h>
#include <string>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "lowqualitywater.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> LowQualityWater::models;

LowQualityWater::LowQualityWater()
{

}

LowQualityWater::LowQualityWater(float x, float z)
{
	this->position.x = x;
	this->position.y = -1;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = true;
	updateTransformationMatrix();
}

void LowQualityWater::step()
{

}

std::list<TexturedModel*>* LowQualityWater::getModels()
{
	return &LowQualityWater::models;
}

void LowQualityWater::loadStaticModels()
{
	if (LowQualityWater::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading LowQualityWater static models...\n");
	#endif

	loadObjModel(&LowQualityWater::models, "res/Models/Water/", "LowQualityWater.obj");
}

void LowQualityWater::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting LowQualityWater models...\n");
	#endif

	Entity::deleteModels(&LowQualityWater::models);
}

std::string LowQualityWater::getName()
{
	return "low quality water";
}