#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecstagetransparent.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EC_StageTransparent::models;

EC_StageTransparent::EC_StageTransparent()
{
	position.x = 0;
	position.y = 0;
	position.z = 0;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();
}

void EC_StageTransparent::step()
{

}

std::list<TexturedModel*>* EC_StageTransparent::getModels()
{
	return &EC_StageTransparent::models;
}

void EC_StageTransparent::loadStaticModels()
{
	if (EC_StageTransparent::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_StageTransparent static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "EmeraldCoastTransparent.obj");
	for (auto newModel : (*newModels))
	{
		EC_StageTransparent::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void EC_StageTransparent::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_StageTransparent static models...\n");
	for (auto model : EC_StageTransparent::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_StageTransparent::models.clear();
}
