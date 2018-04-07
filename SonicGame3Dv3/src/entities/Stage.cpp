#include <glad/glad.h>
#include <string>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "stage.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"

#include <list>
#include <iostream>
#include <string>

std::list<TexturedModel*> Stage::models;

Stage::Stage()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;
	updateTransformationMatrix();
}

void Stage::step()
{

}

std::list<TexturedModel*>* Stage::getModels()
{
	return &Stage::models;
}

void Stage::loadModels(char* folder, char* name)
{
	if (Stage::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading stage models...\n");

	std::string path = "res/Models/";
	path = (path + folder) + "/";

	std::string filename = name;
	filename = filename + ".obj";

	loadObjModel(&Stage::models, path.c_str(), filename.c_str());
}

void Stage::deleteModels()
{
	std::fprintf(stdout, "Deleting stage models...\n");

	Entity::deleteModels(&Stage::models);
}

std::string Stage::getName()
{
	return "stage";
}