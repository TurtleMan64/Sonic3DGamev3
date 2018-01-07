#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecpalmtree.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EC_Palmtree::models;

EC_Palmtree::EC_Palmtree()
{
	
}

EC_Palmtree::EC_Palmtree(float x, float y, float z, float rotX, float rotY, float rotZ, float scale)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
	this->visible = true;
	updateTransformationMatrix();
}

void EC_Palmtree::step()
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

std::list<TexturedModel*>* EC_Palmtree::getModels()
{
	return &EC_Palmtree::models;
}

void EC_Palmtree::loadStaticModels()
{
	if (EC_Palmtree::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_Palmtree static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/EmeraldCoast/", "Palmtree.obj");
	for (auto newModel : (*newModels))
	{
		EC_Palmtree::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void EC_Palmtree::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_Palmtree static models...\n");
	for (auto model : EC_Palmtree::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	EC_Palmtree::models.clear();
}
