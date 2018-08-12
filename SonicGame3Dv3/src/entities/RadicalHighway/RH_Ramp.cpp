#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "rhramp.h"
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

std::list<TexturedModel*> RH_Ramp::models;
CollisionModel* RH_Ramp::cmOriginal;

RH_Ramp::RH_Ramp()
{
	
}

RH_Ramp::RH_Ramp(float x, float y, float z, float rotY, float rotZ)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = 1;
	this->visible = true;
	updateTransformationMatrix();

	collideModelOriginal = RH_Ramp::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/RadicalHighway/Objects/", "Ramp");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModelWithZ();
}

void RH_Ramp::step()
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

std::list<TexturedModel*>* RH_Ramp::getModels()
{
	return &RH_Ramp::models;
}

void RH_Ramp::loadStaticModels()
{
	if (RH_Ramp::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading RH_Ramp static models...\n");
	#endif

	loadObjModel(&RH_Ramp::models, "res/Models/RadicalHighway/Objects/", "Ramp.obj");

	if (RH_Ramp::cmOriginal == nullptr)
	{
		RH_Ramp::cmOriginal = loadCollisionModel("Models/RadicalHighway/Objects/", "Ramp");
	}
}

void RH_Ramp::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting RH_Ramp static models...\n");
	#endif

	Entity::deleteModels(&RH_Ramp::models);
	Entity::deleteCollisionModel(&RH_Ramp::cmOriginal);
}

