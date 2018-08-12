#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecchair.h"
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

std::list<TexturedModel*> EC_Chair::models;
CollisionModel* EC_Chair::cmOriginal;

EC_Chair::EC_Chair()
{
	
}

EC_Chair::EC_Chair(float x, float y, float z, float rotY, float rotZ)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = 1;
	this->visible = true;
	updateTransformationMatrix();

	collideModelOriginal = EC_Chair::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/EmeraldCoast/", "ChairCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModelWithZ();
}

void EC_Chair::step()
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

std::list<TexturedModel*>* EC_Chair::getModels()
{
	return &EC_Chair::models;
}

void EC_Chair::loadStaticModels()
{
	if (EC_Chair::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_Chair static models...\n");
	#endif

	loadObjModel(&EC_Chair::models, "res/Models/EmeraldCoast/", "Chair.obj");

	if (EC_Chair::cmOriginal == nullptr)
	{
		EC_Chair::cmOriginal = loadCollisionModel("Models/EmeraldCoast/", "ChairCollision");
	}
}

void EC_Chair::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_Chair static models...\n");
	#endif

	Entity::deleteModels(&EC_Chair::models);
	Entity::deleteCollisionModel(&EC_Chair::cmOriginal);
}

