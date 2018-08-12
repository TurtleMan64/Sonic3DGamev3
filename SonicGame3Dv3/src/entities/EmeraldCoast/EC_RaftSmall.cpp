#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecraftsmall.h"
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

std::list<TexturedModel*> EC_RaftSmall::models;
CollisionModel* EC_RaftSmall::cmOriginal;

EC_RaftSmall::EC_RaftSmall()
{
	
}

EC_RaftSmall::EC_RaftSmall(float x, float y, float z, float rotY)
{
	this->position.x = x;
	this->position.y = y;
	this->origHeight = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = true;
	updateTransformationMatrix();

	collideModelOriginal = EC_RaftSmall::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/EmeraldCoast/", "RaftSmallCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void EC_RaftSmall::step()
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
			/*
			if (collideModelTransformed->playerIsOn)
			{
				setY(getY() - 0.1f);

				if (getY() < origHeight - 1.5f)
				{
					setY(origHeight - 1.5f);
				}

				updateTransformationMatrix();
				updateCollisionModel();
			}
			else
			{
				//float origY = getY();

				setY(getY() + 0.05f);

				if (getY() > origHeight)
				{
					setY(origHeight);
				}

				float playerY = Global::gamePlayer->getY();
				float playerX = Global::gamePlayer->getX();
				float playerZ = Global::gamePlayer->getZ();
				if (playerY < getY())
				{
					if (playerX < getX() + 21.2 && playerX > getX() - 21.4 &&
						playerZ < getZ() + 35 && playerZ > getZ() - 35)
					{
						float mid = (playerY + getY()) / 2;
						Global::gamePlayer->setY(mid);
						setY(mid - 0.25f);
					}
				}

				updateTransformationMatrix();
				updateCollisionModel();
			}
			*/
		}
	}
}

std::list<TexturedModel*>* EC_RaftSmall::getModels()
{
	return &EC_RaftSmall::models;
}

void EC_RaftSmall::loadStaticModels()
{
	if (EC_RaftSmall::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_RaftSmall static models...\n");
	#endif

	loadObjModel(&EC_RaftSmall::models, "res/Models/EmeraldCoast/", "RaftSmall.obj");

	if (EC_RaftSmall::cmOriginal == nullptr)
	{
		EC_RaftSmall::cmOriginal = loadCollisionModel("Models/EmeraldCoast/", "RaftSmallCollision");
	}
}

void EC_RaftSmall::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_RaftSmall static models...\n");
	#endif
	
	Entity::deleteModels(&EC_RaftSmall::models);
	Entity::deleteCollisionModel(&EC_RaftSmall::cmOriginal);
}
