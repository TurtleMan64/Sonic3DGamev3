#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecpole.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
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

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_Pole static models...\n");
	#endif

	loadObjModel(&EC_Pole::models, "res/Models/EmeraldCoast/", "Pole.obj");

	if (EC_Pole::cmOriginal == nullptr)
	{
		EC_Pole::cmOriginal = loadCollisionModel("Models/EmeraldCoast/", "Pole");
	}
}

void EC_Pole::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_Pole static models...\n");
	#endif
	
	Entity::deleteModels(&EC_Pole::models);
	Entity::deleteCollisionModel(&EC_Pole::cmOriginal);
}

