#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "ring.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> models;

Ring::Ring()
{

}

Ring::Ring(float x, float y, float z)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
}

//Override
void Ring::step()
{
	increaseRotation(0, 1, 0);
}

std::list<TexturedModel*>* Ring::getModels()
{
	return &models;
}

void Ring::loadStaticModels()
{
	if (models.size() > 0)
	{
		std::fprintf(stdout, "Ring models gone astray");
	}

	RawModel model = loadObjModel("res/Ring/Ring.obj");
	ModelTexture texture(Loader_loadTexture("res/Ring/Ring.png"));

	TexturedModel* texturedModel = new TexturedModel(&model, &texture);
	models.push_back(texturedModel);
}

void Ring::deleteStaticModels()
{
	for (auto model : models)
	{
		model->deleteMe(); //delete opengl ids
		delete model;
	}

	models.clear();
}