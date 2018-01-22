#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecpole.h"
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

std::list<TexturedModel*> EC_Pole::models;
CollisionModel* EC_Pole::cmOriginal;

EC_Pole::EC_Pole()
{
	
}

EC_Pole::EC_Pole(float x, float y, float z, float rotY)
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

	collideModelOriginal = EC_Pole::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/EmeraldCoast/", "Pole");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModelWithZ();
}

void EC_Pole::step()
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

std::list<TexturedModel*>* EC_Pole::getModels()
{
	return &EC_Pole::models;
}

void EC_Pole::loadStaticModels()
{
	if (EC_Pole::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_Pole static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "Pole.obj");
	for (auto newModel : (*newModels))
	{
		EC_Pole::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (EC_Pole::cmOriginal == nullptr)
	{
		EC_Pole::cmOriginal = loadCollisionModel("Models/EmeraldCoast/", "Pole");
	}
}

void EC_Pole::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_Pole static models...\n");
	for (auto model : EC_Pole::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_Pole::models.clear();

	if (EC_Pole::cmOriginal != nullptr)
	{
		EC_Pole::cmOriginal->deleteMe();
		delete EC_Pole::cmOriginal;
		Global::countDelete++;
		EC_Pole::cmOriginal = nullptr;
	}
}

