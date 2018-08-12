#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ffhealpads.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
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

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading FF_HealPads static models...\n");
	#endif

	loadObjModel(&FF_HealPads::models, "res/Models/FireField/", "HealPanel.obj");

	if (FF_HealPads::cmOriginal == nullptr)
	{
		FF_HealPads::cmOriginal = loadCollisionModel("Models/FireField/", "HealPanel");
	}
}

void FF_HealPads::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting FF_HealPads static models...\n");
	#endif

	Entity::deleteModels(&FF_HealPads::models);
	Entity::deleteCollisionModel(&FF_HealPads::cmOriginal);
}
