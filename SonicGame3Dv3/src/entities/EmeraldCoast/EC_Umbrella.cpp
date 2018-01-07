#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecumbrella.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EC_Umbrella::models1;
std::list<TexturedModel*> EC_Umbrella::models2;

EC_Umbrella::EC_Umbrella()
{
	
}

EC_Umbrella::EC_Umbrella(float x, float y, float z, float rotX, float rotY, float rotZ, float type)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = 0.8f;
	this->visible = true;
	updateTransformationMatrix();

	if (type != 0)
	{
		this->type = 1;
	}
	else
	{
		this->type = 0;
	}
}

void EC_Umbrella::step()
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

std::list<TexturedModel*>* EC_Umbrella::getModels()
{
	if (type == 0)
	{
		return &EC_Umbrella::models1;
	}
	
	return &EC_Umbrella::models2;
}

void EC_Umbrella::loadStaticModels()
{
	if (EC_Umbrella::models1.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_Umbrella static models...\n");


	{
		std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "Umbrella.obj");
		for (auto newModel : (*newModels))
		{
			EC_Umbrella::models1.push_back(newModel);
		}
		delete newModels;
		Global::countDelete++;
	}

	{
		std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "Umbrella2.obj");
		for (auto newModel : (*newModels))
		{
			EC_Umbrella::models2.push_back(newModel);
		}
		delete newModels;
		Global::countDelete++;
	}
}

void EC_Umbrella::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_Umbrella static models...\n");
	for (auto model : EC_Umbrella::models1)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_Umbrella::models1.clear();

	for (auto model : EC_Umbrella::models2)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_Umbrella::models2.clear();
}
