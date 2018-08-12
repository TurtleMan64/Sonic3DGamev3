#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "ecraft.h"
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

std::list<TexturedModel*> EC_Raft::models;
CollisionModel* EC_Raft::cmOriginal;

EC_Raft::EC_Raft()
{
	
}

EC_Raft::EC_Raft(float x, float y, float z, float rotY)
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

	collideModelOriginal = EC_Raft::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/EmeraldCoast/", "RaftCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void EC_Raft::step()
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
				setY(getY()-1);

				if (getY() < origHeight - 8)
				{
					setY(origHeight - 8);
				}

				updateTransformationMatrix();
				updateCollisionModel();
			}
			else
			{
				setY(getY() + 1);

				if (getY() > origHeight)
				{
					setY(origHeight);
				}

				float playerY = Global::gamePlayer->getY();
				float playerX = Global::gamePlayer->getX();
				float playerZ = Global::gamePlayer->getZ();
				if (playerY < getY())
				{
					if (playerX < getX() + 82.27 && playerX > getX() - 83 &&
						playerZ < getZ() + 55 && playerZ > getZ() - 55)
					{
						setY(playerY - 1);
					}
				}

				updateTransformationMatrix();
				updateCollisionModel();
			}
			*/
		}
	}
}

std::list<TexturedModel*>* EC_Raft::getModels()
{
	return &EC_Raft::models;
}

void EC_Raft::loadStaticModels()
{
	if (EC_Raft::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading EC_Raft static models...\n");
	#endif

	loadObjModel(&EC_Raft::models, "res/Models/EmeraldCoast/", "Raft.obj");

	if (EC_Raft::cmOriginal == nullptr)
	{
		EC_Raft::cmOriginal = loadCollisionModel("Models/EmeraldCoast/", "RaftCollision");
	}
}

void EC_Raft::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting EC_Raft static models...\n");
	#endif
	
	Entity::deleteModels(&EC_Raft::models);
	Entity::deleteCollisionModel(&EC_Raft::cmOriginal);
}
