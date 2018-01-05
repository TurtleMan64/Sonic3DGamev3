#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecraftsmall.h"
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

std::list<TexturedModel*> EC_RaftSmall::models;
CollisionModel* EC_RaftSmall::cmOriginal;

EC_RaftSmall::EC_RaftSmall()
{
	
}

EC_RaftSmall::EC_RaftSmall(float x, float y, float z, float rotY)
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

	collideModelOriginal = EC_RaftSmall::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/EmeraldCoast/", "RaftSmall");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModelWithZ();
}

void EC_RaftSmall::step()
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

std::list<TexturedModel*>* EC_RaftSmall::getModels()
{
	return &EC_RaftSmall::models;
}

void EC_RaftSmall::loadStaticModels()
{
	if (EC_RaftSmall::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_RaftSmall static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "RaftSmall.obj");
	for (auto newModel : (*newModels))
	{
		EC_RaftSmall::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (EC_RaftSmall::cmOriginal == nullptr)
	{
		EC_RaftSmall::cmOriginal = loadCollisionModel("Models/EmeraldCoast/", "RaftSmall");
	}
}

void EC_RaftSmall::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_RaftSmall static models...\n");
	for (auto model : EC_RaftSmall::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_RaftSmall::models.clear();

	if (EC_RaftSmall::cmOriginal != nullptr)
	{
		EC_RaftSmall::cmOriginal->deleteMe();
		delete EC_RaftSmall::cmOriginal;
		EC_RaftSmall::cmOriginal = nullptr;
	}
}
