#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecrockplatform.h"
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

std::list<TexturedModel*> EC_RockPlatform::models;
CollisionModel* EC_RockPlatform::cmOriginal;

EC_RockPlatform::EC_RockPlatform()
{
	
}

EC_RockPlatform::EC_RockPlatform(float x, float y, float z, float rotY)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = true;
	updateTransformationMatrix();

	collideModelOriginal = EC_RockPlatform::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/EmeraldCoast/", "RockPlatform");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void EC_RockPlatform::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
		}
		else
		{
			setVisible(true);
		}
	}
}

std::list<TexturedModel*>* EC_RockPlatform::getModels()
{
	return &EC_RockPlatform::models;
}

void EC_RockPlatform::loadStaticModels()
{
	if (EC_RockPlatform::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_RockPlatform static models...\n");
	#endif

	loadObjModel(&EC_RockPlatform::models, "res/Models/EmeraldCoast/", "RockPlatform.obj");

	if (EC_RockPlatform::cmOriginal == nullptr)
	{
		EC_RockPlatform::cmOriginal = loadCollisionModel("Models/EmeraldCoast/", "RockPlatform");
	}
}

void EC_RockPlatform::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_RockPlatform static models...\n");
	#endif

	Entity::deleteModels(&EC_RockPlatform::models);
	Entity::deleteCollisionModel(&EC_RockPlatform::cmOriginal);
}
