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
	this->position.x = 0;
	this->position.y = -1;
	this->position.z = 0;
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

	std::fprintf(stdout, "Loading LowQualityWater static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/Water/", "LowQualityWater.obj");
	for (auto newModel : (*newModels))
	{
		LowQualityWater::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void LowQualityWater::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting LowQualityWater models...\n");
	for (auto model : LowQualityWater::models)
	{
		model->deleteMe(); //delete opengl ids
		delete model;
		Global::countDelete++;
	}

	LowQualityWater::models.clear();
}

std::string LowQualityWater::getName()
{
	return "low quality water";
}