#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "mhrocketbase.h"
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

std::list<TexturedModel*> MH_RocketBase::models;
CollisionModel* MH_RocketBase::cmOriginal;

MH_RocketBase::MH_RocketBase()
{

}

MH_RocketBase::MH_RocketBase(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();

	collideModelOriginal = MH_RocketBase::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/MetalHarbor/", "RocketBase");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void MH_RocketBase::step()
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

std::list<TexturedModel*>* MH_RocketBase::getModels()
{
	return &MH_RocketBase::models;
}

void MH_RocketBase::loadStaticModels()
{
	if (MH_RocketBase::models.size() > 0)
	{
		return;
	}

#ifdef DEV_MODE
	std::fprintf(stdout, "Loading MH_RocketBase static models...\n");
#endif

	loadObjModel(&MH_RocketBase::models, "res/Models/MetalHarbor/", "RocketBase.obj");

	if (MH_RocketBase::cmOriginal == nullptr)
	{
		MH_RocketBase::cmOriginal = loadCollisionModel("Models/MetalHarbor/", "RocketBase");
	}
}

void MH_RocketBase::deleteStaticModels()
{
#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting MH_RocketBase static models...\n");
#endif

	Entity::deleteModels(&MH_RocketBase::models);
	Entity::deleteCollisionModel(&MH_RocketBase::cmOriginal);
}
