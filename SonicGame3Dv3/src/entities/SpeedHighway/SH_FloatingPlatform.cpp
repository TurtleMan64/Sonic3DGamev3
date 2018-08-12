#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "shfloatingplatform.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> SH_FloatingPlatform::models;
CollisionModel* SH_FloatingPlatform::cmOriginal;

SH_FloatingPlatform::SH_FloatingPlatform()
{
	
}

SH_FloatingPlatform::SH_FloatingPlatform(float x, float y, float z, float rotY, float scale)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	this->scale = scale;
	visible = true;
	updateTransformationMatrix();

	collideModelOriginal = SH_FloatingPlatform::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/SpeedHighway/", "FloatingPlatform");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModelWithScale();
}

void SH_FloatingPlatform::step()
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

std::list<TexturedModel*>* SH_FloatingPlatform::getModels()
{
	return &SH_FloatingPlatform::models;
}

void SH_FloatingPlatform::loadStaticModels()
{
	if (SH_FloatingPlatform::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading SH_FloatingPlatform static models...\n");
	#endif

	loadObjModel(&SH_FloatingPlatform::models, "res/Models/SpeedHighway/", "FloatingPlatform.obj");

	if (SH_FloatingPlatform::cmOriginal == nullptr)
	{
		SH_FloatingPlatform::cmOriginal = loadCollisionModel("Models/SpeedHighway/", "FloatingPlatform");
	}
}

void SH_FloatingPlatform::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting SH_FloatingPlatform static models...\n");
	#endif

	Entity::deleteModels(&SH_FloatingPlatform::models);
	Entity::deleteCollisionModel(&SH_FloatingPlatform::cmOriginal);
}
