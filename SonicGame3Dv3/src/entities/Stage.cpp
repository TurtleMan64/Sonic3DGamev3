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

std::string Stage::stageName = "";

Stage::Stage()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;
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
		//std::fprintf(stdout, "stage models gone astray");
		return;
	}

	std::fprintf(stdout, "Loading stage models...\n");

	std::string path = "res/Models/";
	path = (path + folder) + "/";

	std::string filename = name;
	filename = filename + ".obj";

	std::list<TexturedModel*>* newModels = loadObjModel(path.c_str(), filename.c_str());
	for (auto newModel : (*newModels))
	{
		Stage::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void Stage::deleteModels()
{
	std::fprintf(stdout, "Deleting stage models...\n");
	for (auto model : Stage::models)
	{
		model->deleteMe(); //delete opengl ids
		delete model;
		Global::countDelete++;
	}

	Stage::models.clear();
}