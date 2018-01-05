#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecdockcorner.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EC_DockCorner::models;
CollisionModel* EC_DockCorner::cmOriginal;

EC_DockCorner::EC_DockCorner()
{
	
}

EC_DockCorner::EC_DockCorner(float x, float y, float z, float rotY)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = true;
	updateTransformationMatrix();

	collideModelOriginal = EC_DockCorner::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/EmeraldCoast/", "DockCornerCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModelWithZ();
}

void EC_DockCorner::step()
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

std::list<TexturedModel*>* EC_DockCorner::getModels()
{
	return &EC_DockCorner::models;
}

void EC_DockCorner::loadStaticModels()
{
	if (EC_DockCorner::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_DockCorner static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "DockCorner.obj");
	for (auto newModel : (*newModels))
	{
		EC_DockCorner::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (EC_DockCorner::cmOriginal == nullptr)
	{
		EC_DockCorner::cmOriginal = loadCollisionModel("Models/EmeraldCoast/", "DockCornerCollision");
	}
}

void EC_DockCorner::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_DockCorner static models...\n");
	for (auto model : EC_DockCorner::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_DockCorner::models.clear();

	if (EC_DockCorner::cmOriginal != nullptr)
	{
		EC_DockCorner::cmOriginal->deleteMe();
		delete EC_DockCorner::cmOriginal;
		EC_DockCorner::cmOriginal = nullptr;
	}
}
