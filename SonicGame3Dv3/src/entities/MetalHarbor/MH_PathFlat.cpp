#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "mhpathflat.h"
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

std::list<TexturedModel*> MH_PathFlat::models;
CollisionModel* MH_PathFlat::cmOriginal;

MH_PathFlat::MH_PathFlat()
{

}

MH_PathFlat::MH_PathFlat(float x, float y, float z, float rotY)
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

	collideModelOriginal = MH_PathFlat::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/MetalHarbor/", "PathFlatCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void MH_PathFlat::step()
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

std::list<TexturedModel*>* MH_PathFlat::getModels()
{
	return &MH_PathFlat::models;
}

void MH_PathFlat::loadStaticModels()
{
	if (MH_PathFlat::models.size() > 0)
	{
		return;
	}

#ifdef DEV_MODE
	std::fprintf(stdout, "Loading MH_PathFlat static models...\n");
#endif

	loadObjModel(&MH_PathFlat::models, "res/Models/MetalHarbor/", "PathFlat.obj");

	if (MH_PathFlat::cmOriginal == nullptr)
	{
		MH_PathFlat::cmOriginal = loadCollisionModel("Models/MetalHarbor/", "PathFlatCollision");
	}
}

void MH_PathFlat::deleteStaticModels()
{
#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting MH_PathFlat static models...\n");
#endif

	Entity::deleteModels(&MH_PathFlat::models);
	Entity::deleteCollisionModel(&MH_PathFlat::cmOriginal);
}
