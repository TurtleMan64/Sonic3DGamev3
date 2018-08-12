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
#include "playersonic.h"

#include <list>
#include <iostream>
#include <string>

std::list<TexturedModel*> SkySphere::models;

SkySphere::SkySphere()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
	followsY = false;
}

void SkySphere::step()
{
	setRotY(SkyManager::getTimeOfDay());
	//if (Global::gamePlayer != nullptr) 
	{
		//game player was somtimes deallocated but not null? now i just set it in the player
		//position.x = Global::gamePlayer->getX();
		//position.z = Global::gamePlayer->getZ();
	}
	updateTransformationMatrix();
}

void SkySphere::setFollowsY(bool newFollowsY)
{
	followsY = newFollowsY;
}

bool SkySphere::getFollowsY()
{
	return followsY;
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

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading sky sphere models...\n");
	#endif

	std::string path = "res/Models/";
	path = (path + folder) + "/";

	std::string objfilename = objname;
	objfilename = objfilename + ".obj";

	std::string mtlfilename = mtlname;
	mtlfilename = mtlfilename + ".mtl";

	loadObjModelWithMTL(&SkySphere::models, path.c_str(), objfilename.c_str(), mtlfilename.c_str());
}

void SkySphere::deleteModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting sky sphere models...\n");
	#endif

	Entity::deleteModels(&SkySphere::models);
}