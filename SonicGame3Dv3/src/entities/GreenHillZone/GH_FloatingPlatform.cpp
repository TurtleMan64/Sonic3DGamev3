#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ghfloatingplatform.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> GH_FloatingPlatform::models;
CollisionModel* GH_FloatingPlatform::cmOriginal;

GH_FloatingPlatform::GH_FloatingPlatform()
{
	
}

GH_FloatingPlatform::GH_FloatingPlatform(float x, float y, float z, float rotY, float scale)
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

	collideModelOriginal = GH_FloatingPlatform::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/GreenHillZone/Objects/", "GreenHillFallingPlatform");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void GH_FloatingPlatform::step()
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

std::list<TexturedModel*>* GH_FloatingPlatform::getModels()
{
	return &GH_FloatingPlatform::models;
}

void GH_FloatingPlatform::loadStaticModels()
{
	if (GH_FloatingPlatform::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading GH_FloatingPlatform static models...\n");
	#endif

	loadObjModel(&GH_FloatingPlatform::models, "res/Models/GreenHillZone/Objects/", "GreenHillFallingPlatform.obj");

	if (GH_FloatingPlatform::cmOriginal == nullptr)
	{
		GH_FloatingPlatform::cmOriginal = loadCollisionModel("Models/GreenHillZone/Objects/", "GreenHillFallingPlatform");
	}
}

void GH_FloatingPlatform::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting GH_FloatingPlatform static models...\n");
	#endif

	Entity::deleteModels(&GH_FloatingPlatform::models);
	Entity::deleteCollisionModel(&GH_FloatingPlatform::cmOriginal);
}
