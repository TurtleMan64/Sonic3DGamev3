#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "nbwaterplatform.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> NB_WaterPlatform::models;
CollisionModel* NB_WaterPlatform::cmOriginal;

NB_WaterPlatform::NB_WaterPlatform()
{
	
}

NB_WaterPlatform::NB_WaterPlatform(float x, float y, float z, float rotY)
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

	collideModelOriginal = NB_WaterPlatform::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/NokiBay/WaterPlatforms/", "WaterPlatformCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void NB_WaterPlatform::step()
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

std::list<TexturedModel*>* NB_WaterPlatform::getModels()
{
	return &NB_WaterPlatform::models;
}

void NB_WaterPlatform::loadStaticModels()
{
	if (NB_WaterPlatform::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading NB_WaterPlatform static models...\n");
	#endif

	loadObjModel(&NB_WaterPlatform::models, "res/Models/NokiBay/WaterPlatforms/", "WaterPlatform.obj");

	if (NB_WaterPlatform::cmOriginal == nullptr)
	{
		NB_WaterPlatform::cmOriginal = loadCollisionModel("Models/NokiBay/WaterPlatforms/", "WaterPlatformCollision");
	}
}

void NB_WaterPlatform::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting NB_WaterPlatform static models...\n");
	#endif

	Entity::deleteModels(&NB_WaterPlatform::models);
	Entity::deleteCollisionModel(&NB_WaterPlatform::cmOriginal);
}
