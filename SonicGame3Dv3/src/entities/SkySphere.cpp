#include <glad/glad.h>
#include <string>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "skysphere.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../renderEngine/skymanager.h"
#include "player.h"

#include <list>
#include <iostream>
#include <string>

std::list<TexturedModel*> SkySphere::models;

SkySphere::SkySphere()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;
}

void SkySphere::step()
{
	setRotY(SkyManager::getTimeOfDay());
	if (Global::gamePlayer != nullptr)
	{
		position.x = Global::gamePlayer->getX();
		position.z = Global::gamePlayer->getZ();
	}
}

std::list<TexturedModel*>* SkySphere::getModels()
{
	return &SkySphere::models;
}

void SkySphere::loadModels(char* folder, char* objname, char* mtlname)
{
	if (SkySphere::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading sky sphere models...\n");

	std::string path = "res/Models/";
	path = (path + folder) + "/";

	std::string objfilename = objname;
	objfilename = objfilename + ".obj";

	std::string mtlfilename = mtlname;
	mtlfilename = mtlfilename + ".mtl";

	std::list<TexturedModel*>* newModels = loadObjModelWithMTL(path.c_str(), objfilename.c_str(), mtlfilename.c_str());
	for (auto newModel : (*newModels))
	{
		SkySphere::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void SkySphere::deleteModels()
{
	std::fprintf(stdout, "Deleting sky sphere models...\n");
	for (auto model : SkySphere::models)
	{
		model->deleteMe(); //delete opengl ids
		delete model;
		Global::countDelete++;
	}

	SkySphere::models.clear();
}