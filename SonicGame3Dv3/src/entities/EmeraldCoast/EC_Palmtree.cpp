#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecpalmtree.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
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

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_Palmtree static models...\n");
	#endif

	loadObjModel(&EC_Palmtree::models1, "res/Models/EmeraldCoast/", "Palmtree.obj");
	loadObjModel(&EC_Palmtree::models2, "res/Models/EmeraldCoast/", "Palmtree.obj");
	loadObjModel(&EC_Palmtree::models3, "res/Models/EmeraldCoast/", "Palmtree.obj");
	loadObjModel(&EC_Palmtree::modelsHorizontal, "res/Models/EmeraldCoast/", "PalmtreeHorizontal.obj");
}

void EC_Palmtree::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_Palmtree static models...\n");
	#endif

	Entity::deleteModels(&EC_Palmtree::models1);
	Entity::deleteModels(&EC_Palmtree::models2);
	Entity::deleteModels(&EC_Palmtree::models3);
	Entity::deleteModels(&EC_Palmtree::modelsHorizontal);
}
