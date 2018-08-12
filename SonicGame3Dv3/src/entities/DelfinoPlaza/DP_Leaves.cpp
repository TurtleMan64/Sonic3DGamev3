#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "dpleaves.h"
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

std::list<TexturedModel*> DP_Leaves::models;
CollisionModel* DP_Leaves::cmOriginal;

DP_Leaves::DP_Leaves()
{
	
}

DP_Leaves::DP_Leaves(float x, float y, float z, float rotY)
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

	collideModelOriginal = DP_Leaves::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/DelfinoPlaza/Leaves/", "Leaves");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void DP_Leaves::step()
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

std::list<TexturedModel*>* DP_Leaves::getModels()
{
	return &DP_Leaves::models;
}

void DP_Leaves::loadStaticModels()
{
	if (DP_Leaves::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading DP_Leaves static models...\n");
	#endif

	loadObjModel(&DP_Leaves::models, "res/Models/DelfinoPlaza/Leaves/", "Leaves.obj");

	if (DP_Leaves::cmOriginal == nullptr)
	{
		DP_Leaves::cmOriginal = loadCollisionModel("Models/DelfinoPlaza/Leaves/", "Leaves");
	}
}

void DP_Leaves::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting DP_Leaves static models...\n");
	#endif

	Entity::deleteModels(&DP_Leaves::models);
	Entity::deleteCollisionModel(&DP_Leaves::cmOriginal);
}
