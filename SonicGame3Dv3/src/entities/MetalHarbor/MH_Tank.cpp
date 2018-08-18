#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "mhtank.h"
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

std::list<TexturedModel*> MH_Tank::models;
CollisionModel* MH_Tank::cmOriginal;

MH_Tank::MH_Tank()
{

}

MH_Tank::MH_Tank(float x, float y, float z)
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

	collideModelOriginal = MH_Tank::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/MetalHarbor/", "TankCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void MH_Tank::step()
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

std::list<TexturedModel*>* MH_Tank::getModels()
{
	return &MH_Tank::models;
}

void MH_Tank::loadStaticModels()
{
	if (MH_Tank::models.size() > 0)
	{
		return;
	}

#ifdef DEV_MODE
	std::fprintf(stdout, "Loading MH_Tank static models...\n");
#endif

	loadObjModel(&MH_Tank::models, "res/Models/MetalHarbor/", "Tank.obj");

	if (MH_Tank::cmOriginal == nullptr)
	{
		MH_Tank::cmOriginal = loadCollisionModel("Models/MetalHarbor/", "TankCollision");
	}
}

void MH_Tank::deleteStaticModels()
{
#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting MH_Tank static models...\n");
#endif

	Entity::deleteModels(&MH_Tank::models);
	Entity::deleteCollisionModel(&MH_Tank::cmOriginal);
}
