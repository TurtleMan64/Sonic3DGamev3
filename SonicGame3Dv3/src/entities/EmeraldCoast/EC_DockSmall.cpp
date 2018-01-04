#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecdocksmall.h"
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

std::list<TexturedModel*> EC_DockSmall::models;
CollisionModel* EC_DockSmall::cmOriginal;

EC_DockSmall::EC_DockSmall()
{
	
}

EC_DockSmall::EC_DockSmall(float x, float y, float z, float rotY)
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

	collideModelOriginal = EC_DockSmall::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/EmeraldCoast/", "SmallDock");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModelWithZ();
}

void EC_DockSmall::step()
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

std::list<TexturedModel*>* EC_DockSmall::getModels()
{
	return &EC_DockSmall::models;
}

void EC_DockSmall::loadStaticModels()
{
	if (EC_DockSmall::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_DockSmall static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "SmallDock.obj");
	for (auto newModel : (*newModels))
	{
		EC_DockSmall::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (EC_DockSmall::cmOriginal == nullptr)
	{
		EC_DockSmall::cmOriginal = loadCollisionModel("Models/EmeraldCoast/", "SmallDock");
	}
}

void EC_DockSmall::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_DockSmall static models...\n");
	for (auto model : EC_DockSmall::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_DockSmall::models.clear();

	if (EC_DockSmall::cmOriginal != nullptr)
	{
		EC_DockSmall::cmOriginal->deleteMe();
		delete EC_DockSmall::cmOriginal;
		EC_DockSmall::cmOriginal = nullptr;
	}
}

