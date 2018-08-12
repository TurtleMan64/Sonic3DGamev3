#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ghrock.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> GH_Rock::models;
CollisionModel* GH_Rock::cmOriginal;

GH_Rock::GH_Rock()
{
	
}

GH_Rock::GH_Rock(float x, float y, float z, float rotY, float scale)
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

	collideModelOriginal = GH_Rock::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/GreenHillZone/Objects/", "GreenHillRockCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void GH_Rock::step()
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

std::list<TexturedModel*>* GH_Rock::getModels()
{
	return &GH_Rock::models;
}

void GH_Rock::loadStaticModels()
{
	if (GH_Rock::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading GH_Rock static models...\n");
	#endif

	loadObjModel(&GH_Rock::models, "res/Models/GreenHillZone/Objects/", "GreenHillRock.obj");

	if (GH_Rock::cmOriginal == nullptr)
	{
		GH_Rock::cmOriginal = loadCollisionModel("Models/GreenHillZone/Objects/", "GreenHillRockCollision");
	}
}

void GH_Rock::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting GH_Rock static models...\n");
	#endif

	Entity::deleteModels(&GH_Rock::models);
	Entity::deleteCollisionModel(&GH_Rock::cmOriginal);
}
