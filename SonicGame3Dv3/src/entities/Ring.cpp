#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "ring.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> Ring::models;

Ring::Ring()
{

}

Ring::Ring(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

void Ring::step()
{
	increaseRotation(0, 1, 0);
}

std::list<TexturedModel*>* Ring::getModels()
{
	return &Ring::models;
}

void Ring::loadStaticModels()
{
	if (Ring::models.size() > 0)
	{
		std::fprintf(stdout, "Ring models gone astray");
		return;
	}

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/Ring/", "Ring.obj");
	for (auto newModel : (*newModels))
	{
		Ring::models.push_back(newModel);
	}
	delete newModels;
}

void Ring::deleteStaticModels()
{
	for (auto model : Ring::models)
	{
		model->deleteMe(); //delete opengl ids
		delete model;
	}

	Ring::models.clear();
}