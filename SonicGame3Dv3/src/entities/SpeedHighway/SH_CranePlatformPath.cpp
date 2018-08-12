#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "shcraneplatformpath.h"
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

std::list<TexturedModel*> SH_CranePlatformPath::models;
CollisionModel* SH_CranePlatformPath::cmOriginal;

SH_CranePlatformPath::SH_CranePlatformPath()
{

}

SH_CranePlatformPath::SH_CranePlatformPath(float x, float y, float z, float rotY)
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

	collideModelOriginal = SH_CranePlatformPath::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/SpeedHighway/", "CranePlatformPath");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void SH_CranePlatformPath::step()
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

std::list<TexturedModel*>* SH_CranePlatformPath::getModels()
{
	return &SH_CranePlatformPath::models;
}

void SH_CranePlatformPath::loadStaticModels()
{
	if (SH_CranePlatformPath::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading SH_CranePlatformPath static models...\n");
	#endif

	loadObjModel(&SH_CranePlatformPath::models, "res/Models/SpeedHighway/", "CranePlatformPath.obj");

	if (SH_CranePlatformPath::cmOriginal == nullptr)
	{
		SH_CranePlatformPath::cmOriginal = loadCollisionModel("Models/SpeedHighway/", "CranePlatformPath");
	}
}

void SH_CranePlatformPath::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting SH_CranePlatformPath static models...\n");
	#endif

	Entity::deleteModels(&SH_CranePlatformPath::models);
	Entity::deleteCollisionModel(&SH_CranePlatformPath::cmOriginal);
}
