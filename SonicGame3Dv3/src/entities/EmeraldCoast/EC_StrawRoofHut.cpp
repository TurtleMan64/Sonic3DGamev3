#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecstrawroofhut.h"
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

std::list<TexturedModel*> EC_StrawRoofHut::models;
CollisionModel* EC_StrawRoofHut::cmOriginal;

EC_StrawRoofHut::EC_StrawRoofHut()
{
	
}

EC_StrawRoofHut::EC_StrawRoofHut(float x, float y, float z, float rotY)
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

	collideModelOriginal = EC_StrawRoofHut::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/EmeraldCoast/", "StrawRoofHut");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModelWithZ();
}

void EC_StrawRoofHut::step()
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

std::list<TexturedModel*>* EC_StrawRoofHut::getModels()
{
	return &EC_StrawRoofHut::models;
}

void EC_StrawRoofHut::loadStaticModels()
{
	if (EC_StrawRoofHut::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_StrawRoofHut static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "StrawRoofHut.obj");
	for (auto newModel : (*newModels))
	{
		EC_StrawRoofHut::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (EC_StrawRoofHut::cmOriginal == nullptr)
	{
		EC_StrawRoofHut::cmOriginal = loadCollisionModel("Models/EmeraldCoast/", "StrawRoofHut");
	}
}

void EC_StrawRoofHut::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_StrawRoofHut static models...\n");
	for (auto model : EC_StrawRoofHut::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_StrawRoofHut::models.clear();

	if (EC_StrawRoofHut::cmOriginal != nullptr)
	{
		EC_StrawRoofHut::cmOriginal->deleteMe();
		delete EC_StrawRoofHut::cmOriginal;
		EC_StrawRoofHut::cmOriginal = nullptr;
	}
}

