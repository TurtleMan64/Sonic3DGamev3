#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "mhpathflatsmall.h"
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

std::list<TexturedModel*> MH_PathFlatSmall::models;
CollisionModel* MH_PathFlatSmall::cmOriginal;

MH_PathFlatSmall::MH_PathFlatSmall()
{

}

MH_PathFlatSmall::MH_PathFlatSmall(float x, float y, float z, float rotY)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();

	collideModelOriginal = MH_PathFlatSmall::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/MetalHarbor/", "PathFlatSmallCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void MH_PathFlatSmall::step()
{
	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST * 2)
	{
		setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST * 2)
		{
			setVisible(false);
		}
		else
		{
			setVisible(true);
		}
	}
}

std::list<TexturedModel*>* MH_PathFlatSmall::getModels()
{
	return &MH_PathFlatSmall::models;
}

void MH_PathFlatSmall::loadStaticModels()
{
	if (MH_PathFlatSmall::models.size() > 0)
	{
		return;
	}

#ifdef DEV_MODE
	std::fprintf(stdout, "Loading MH_PathFlatSmall static models...\n");
#endif

	loadObjModel(&MH_PathFlatSmall::models, "res/Models/MetalHarbor/", "PathFlatSmall.obj");

	if (MH_PathFlatSmall::cmOriginal == nullptr)
	{
		MH_PathFlatSmall::cmOriginal = loadCollisionModel("Models/MetalHarbor/", "PathFlatSmallCollision");
	}
}

void MH_PathFlatSmall::deleteStaticModels()
{
#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting MH_PathFlatSmall static models...\n");
#endif

	Entity::deleteModels(&MH_PathFlatSmall::models);
	Entity::deleteCollisionModel(&MH_PathFlatSmall::cmOriginal);
}
