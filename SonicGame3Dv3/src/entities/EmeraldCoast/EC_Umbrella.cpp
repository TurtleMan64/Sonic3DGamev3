#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecumbrella.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
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

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_Umbrella static models...\n");
	#endif

	loadObjModel(&EC_Umbrella::models1, "res/Models/EmeraldCoast/", "Umbrella.obj");
	loadObjModel(&EC_Umbrella::models2, "res/Models/EmeraldCoast/", "Umbrella2.obj");
}

void EC_Umbrella::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_Umbrella static models...\n");
	#endif

	Entity::deleteModels(&EC_Umbrella::models1);
	Entity::deleteModels(&EC_Umbrella::models2);
}
