#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecflatwater.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
#include "../../toolbox/maths.h"
#include "../camera.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> EC_FlatWater::models;

EC_FlatWater::EC_FlatWater()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = false;
	updateTransformationMatrix();
}


void EC_FlatWater::step()
{
	if (Global::gameCamera->getPosition()->z > 2000)
	{
		visible = true;

		if (Global::gamePlayer->getX() > -721.26f  && Global::gamePlayer->getX() < 378.71f    &&
			Global::gamePlayer->getZ() > 14567.68f && Global::gamePlayer->getZ() < 15667.667f &&
			Global::gamePlayer->getY() < 576)
		{
			Global::gamePlayer->setInWater(581);
		}
		else if (Global::gamePlayer->getX() > 420.37f  && Global::gamePlayer->getX() < 1212.35f &&
				 Global::gamePlayer->getZ() > 15713.0f && Global::gamePlayer->getZ() < 16505.0f &&
			     Global::gamePlayer->getY() < 586)
		{
			Global::gamePlayer->setInWater(590);
		}
	}
	else
	{
		visible = false;
	}
}

std::list<TexturedModel*>* EC_FlatWater::getModels()
{
	return &EC_FlatWater::models;
}

void EC_FlatWater::loadStaticModels()
{
	if (EC_FlatWater::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_FlatWater static models...\n");
	#endif

	loadObjModel(&EC_FlatWater::models, "res/Models/EmeraldCoast/", "FlatWater.obj");
}

void EC_FlatWater::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_FlatWater static models...\n");
	#endif

	Entity::deleteModels(&EC_FlatWater::models);
}

std::string EC_FlatWater::getName()
{
	return "EC_FlatWater";
}