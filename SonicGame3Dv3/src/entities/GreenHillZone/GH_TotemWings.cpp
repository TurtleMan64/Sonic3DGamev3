#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ghtotemwings.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> GH_TotemWings::models;
CollisionModel* GH_TotemWings::cmOriginal;

GH_TotemWings::GH_TotemWings()
{
	
}

GH_TotemWings::GH_TotemWings(float x, float y, float z, float rotY, float scale)
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

	collideModelOriginal = GH_TotemWings::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/GreenHillZone/Objects/", "GreenHillTotemCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void GH_TotemWings::step()
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

std::list<TexturedModel*>* GH_TotemWings::getModels()
{
	return &GH_TotemWings::models;
}

void GH_TotemWings::loadStaticModels()
{
	if (GH_TotemWings::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading GH_TotemWings static models...\n");
	#endif

	loadObjModel(&GH_TotemWings::models, "res/Models/GreenHillZone/Objects/", "GreenHillTotemWings.obj");

	if (GH_TotemWings::cmOriginal == nullptr)
	{
		GH_TotemWings::cmOriginal = loadCollisionModel("Models/GreenHillZone/Objects/", "GreenHillTotemCollision");
	}
}

void GH_TotemWings::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting GH_TotemWings static models...\n");
	#endif

	Entity::deleteModels(&GH_TotemWings::models);
	Entity::deleteCollisionModel(&GH_TotemWings::cmOriginal);
}
