#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ffhealpads.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> FF_HealPads::models;
CollisionModel* FF_HealPads::cmOriginal;

FF_HealPads::FF_HealPads()
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

	collideModelOriginal = FF_HealPads::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/FireField/", "HealPanel");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void FF_HealPads::step()
{
	if (collideModelTransformed->playerIsOn)
	{
		Global::gamePlayer->boostMe(0.075f);
	}
}

std::list<TexturedModel*>* FF_HealPads::getModels()
{
	return &FF_HealPads::models;
}

void FF_HealPads::loadStaticModels()
{
	if (FF_HealPads::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading FF_HealPads static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/FireField/", "HealPanel.obj");
	for (auto newModel : (*newModels))
	{
		FF_HealPads::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (FF_HealPads::cmOriginal == nullptr)
	{
		FF_HealPads::cmOriginal = loadCollisionModel("Models/FireField/", "HealPanel");
	}
}

void FF_HealPads::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting FF_HealPads static models...\n");
	for (auto model : FF_HealPads::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	FF_HealPads::models.clear();

	if (FF_HealPads::cmOriginal != nullptr)
	{
		FF_HealPads::cmOriginal->deleteMe();
		delete FF_HealPads::cmOriginal;
		Global::countDelete++;
		FF_HealPads::cmOriginal = nullptr;
	}
}