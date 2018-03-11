#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "shcraneplatform.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"
#include "../point.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> SH_CranePlatform::models;
CollisionModel* SH_CranePlatform::cmOriginal;

SH_CranePlatform::SH_CranePlatform()
{

}

SH_CranePlatform::SH_CranePlatform(float x, float y, float z, float rotY, float speed, int point1, int point2)
{
	position.x = x;
	position.y = y;
	origHeight = y;
	position.z = z;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();

	isMoving = false;
	canMove = true;

	point2GreaterX = 1; //used for keeping track of if the initial position is greater than or less than the final position on that axis
	point2GreaterY = 1; 
	point2GreaterZ = 1;

	collideModelOriginal = SH_CranePlatform::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/SpeedHighway/", "CranePlatform1");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();

	extern std::list<Entity*> gameEntitiesToAdd;

	for (auto e : gameEntitiesToAdd)
	{
		if (e->isPoint()) 
		{
			Point* thisPoint = (Point*)e;
			if (thisPoint->getid() == point1)
			{
				pointPos1 = thisPoint->getPosition();
			}
			else
			{
				pointPos2 = thisPoint->getPosition();
			}
		}
	}

	moveDir = pointPos2 - pointPos1;
	moveDir.scale(0.01);
	moveDir.x = moveDir.x / speed;
	moveDir.y = moveDir.y / speed;
	moveDir.z = moveDir.z / speed;

	if (pointPos2.x > pointPos1.x)
	{
		point2GreaterX = -1; //comparisons are flipped for negatives, -2 < -1, but 1 < 2
	}
	if (pointPos2.y > pointPos1.y)
	{
		point2GreaterY = -1;
	}
	if (pointPos2.z > pointPos1.z)
	{
		point2GreaterZ = -1;
	}
}

void SH_CranePlatform::step()
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

	if (collideModelTransformed->playerIsOn && canMove)
	{
		isMoving = true;
	}

	if (!(position.x * point2GreaterX >= pointPos2.x * point2GreaterX &&
		position.y * point2GreaterY >= pointPos2.y * point2GreaterY &&
		position.z * point2GreaterZ >= pointPos2.z * point2GreaterZ))
	{
		isMoving = false;
		canMove = false;
	}

	if (isMoving)
	{
		newPos = position + moveDir;
		position = newPos;
		//move the player only if the player is standing on the platform
		if (collideModelTransformed->playerIsOn) Global::gamePlayer->setPosition(Global::gamePlayer->getX() + moveDir.x, Global::gamePlayer->getY() + moveDir.y, Global::gamePlayer->getZ() + moveDir.z);
		//Global::gamePlayer->setDisplacement(moveDir.x, moveDir.y, moveDir.z);
	}

	updateCMJustPosition();
	updateTransformationMatrix();
}

std::list<TexturedModel*>* SH_CranePlatform::getModels()
{
	return &SH_CranePlatform::models;
}

void SH_CranePlatform::loadStaticModels()
{
	if (SH_CranePlatform::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading SH_CranePlatform static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/SpeedHighway/", "CranePlatform1.obj");
	for (auto newModel : (*newModels))
	{
		SH_CranePlatform::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (SH_CranePlatform::cmOriginal == nullptr)
	{
		SH_CranePlatform::cmOriginal = loadCollisionModel("Models/SpeedHighway/", "CranePlatform1");
	}
}

void SH_CranePlatform::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting SH_CranePlatform static models...\n");
	for (auto model : SH_CranePlatform::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	SH_CranePlatform::models.clear();

	if (SH_CranePlatform::cmOriginal != nullptr)
	{
		SH_CranePlatform::cmOriginal->deleteMe();
		delete SH_CranePlatform::cmOriginal;
		Global::countDelete++;
		SH_CranePlatform::cmOriginal = nullptr;
	}
}
