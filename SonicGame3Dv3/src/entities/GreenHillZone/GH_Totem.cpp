#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ghtotem.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> GH_Totem::models;
CollisionModel* GH_Totem::cmOriginal;

GH_Totem::GH_Totem()
{
	
}

GH_Totem::GH_Totem(float x, float y, float z, float rotY, float scale)
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

	collideModelOriginal = GH_Totem::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/GreenHillZone/Objects/", "GreenHillTotemCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void GH_Totem::step()
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

std::list<TexturedModel*>* GH_Totem::getModels()
{
	return &GH_Totem::models;
}

void GH_Totem::loadStaticModels()
{
	if (GH_Totem::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading GH_Totem static models...\n");
	#endif

	loadObjModel(&GH_Totem::models, "res/Models/GreenHillZone/Objects/", "GreenHillTotem.obj");

	if (GH_Totem::cmOriginal == nullptr)
	{
		GH_Totem::cmOriginal = loadCollisionModel("Models/GreenHillZone/Objects/", "GreenHillTotemCollision");
	}
}

void GH_Totem::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting GH_Totem static models...\n");
	#endif

	Entity::deleteModels(&GH_Totem::models);
	Entity::deleteCollisionModel(&GH_Totem::cmOriginal);
}
