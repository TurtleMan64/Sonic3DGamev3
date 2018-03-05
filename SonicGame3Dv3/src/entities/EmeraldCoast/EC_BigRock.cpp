#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecbigrock.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EC_BigRock::modelsA;
std::list<TexturedModel*> EC_BigRock::modelsB;

EC_BigRock::EC_BigRock()
{
	
}

EC_BigRock::EC_BigRock(float x, float y, float z, float rotX, float rotY, float rotZ, float scale, int kind)
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
	baseYrot = rotY;
}

void EC_BigRock::step()
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

	//rotY++;
	updateTransformationMatrix();

	//fprintf(stdout, "%f\n", rotY - baseYrot);
}

std::list<TexturedModel*>* EC_BigRock::getModels()
{
	switch (kind)
	{
		case 0: return &EC_BigRock::modelsA;

		default: break;
	}

	return &EC_BigRock::modelsB;
}

void EC_BigRock::loadStaticModels()
{
	if (EC_BigRock::modelsA.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading EC_BigRock static models...\n");

	std::list<TexturedModel*>* newModels1 = loadObjModel("res/Models/EmeraldCoast/", "BigRockA.obj");
	for (auto newModel : (*newModels1))
	{
		EC_BigRock::modelsA.push_back(newModel);
	}
	delete newModels1;
	Global::countDelete++;



	std::list<TexturedModel*>* newModels2 = loadObjModel("res/Models/EmeraldCoast/", "BigRockB.obj");
	for (auto newModel : (*newModels2))
	{
		EC_BigRock::modelsB.push_back(newModel);
	}
	delete newModels2;
	Global::countDelete++;
}

void EC_BigRock::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting EC_BigRock static models...\n");

	for (auto model : EC_BigRock::modelsA)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}
	EC_BigRock::modelsA.clear();

	for (auto model : EC_BigRock::modelsB)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}
	EC_BigRock::modelsB.clear();
}
