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

std::list<TexturedModel*> EC_Palmtree::models1;
std::list<TexturedModel*> EC_Palmtree::models2;
std::list<TexturedModel*> EC_Palmtree::models3;
std::list<TexturedModel*> EC_Palmtree::modelsHorizontal;

EC_Palmtree::EC_Palmtree()
{
	
}

EC_Palmtree::EC_Palmtree(float x, float y, float z, float rotX, float rotY, float rotZ, float scale, int kind)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = scale;
	this->visible = true;
	this->kind = kind;
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
	switch (kind)
	{
		case 0: return &EC_Palmtree::models1;

		case 1: return &EC_Palmtree::models2;

		case 2: return &EC_Palmtree::models3;

		default: break;
	}

	return &EC_Palmtree::modelsHorizontal;
}

void EC_Palmtree::loadStaticModels()
{
	if (EC_Palmtree::models1.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_Palmtree static models...\n");

	std::list<TexturedModel*>* newModels1 = loadObjModel("res/Models/EmeraldCoast/", "Palmtree.obj");
	for (auto newModel : (*newModels1))
	{
		EC_Palmtree::models1.push_back(newModel);
	}
	delete newModels1;
	Global::countDelete++;



	std::list<TexturedModel*>* newModels2 = loadObjModel("res/Models/EmeraldCoast/", "Palmtree.obj");
	for (auto newModel : (*newModels2))
	{
		EC_Palmtree::models2.push_back(newModel);
	}
	delete newModels2;
	Global::countDelete++;




	std::list<TexturedModel*>* newModels3 = loadObjModel("res/Models/EmeraldCoast/", "Palmtree.obj");
	for (auto newModel : (*newModels3))
	{
		EC_Palmtree::models3.push_back(newModel);
	}
	delete newModels3;
	Global::countDelete++;




	std::list<TexturedModel*>* newModels4 = loadObjModel("res/Models/EmeraldCoast/", "PalmtreeHorizontal.obj");
	for (auto newModel : (*newModels4))
	{
		EC_Palmtree::modelsHorizontal.push_back(newModel);
	}
	delete newModels4;
	Global::countDelete++;
}

void EC_Palmtree::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_Palmtree static models...\n");

	for (auto model : EC_Palmtree::models1)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}
	EC_Palmtree::models1.clear();

	for (auto model : EC_Palmtree::models2)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}
	EC_Palmtree::models2.clear();

	for (auto model : EC_Palmtree::models3)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}
	EC_Palmtree::models3.clear();

	for (auto model : EC_Palmtree::modelsHorizontal)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}
	EC_Palmtree::modelsHorizontal.clear();
}
