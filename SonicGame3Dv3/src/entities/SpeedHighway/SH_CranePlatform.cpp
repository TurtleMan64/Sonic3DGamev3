<<<<<<< HEAD
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
#include "../../audio/audioplayer.h"
#include "../../audio/source.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> SH_CranePlatform::models;
CollisionModel* SH_CranePlatform::cmOriginal;

SH_CranePlatform::SH_CranePlatform()
{

}

SH_CranePlatform::SH_CranePlatform(float x, float y, float z, float rotY, float speed, int point1ID, int point2ID)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	this->rotY = rotY;
	rotZ = 0;
	scale = 1;
	visible = true;
	updateTransformationMatrix();
	this->speed = speed;

	isMoving = false;
	canMove = true;

	timeOffset = 0;

	collideModelOriginal = SH_CranePlatform::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/SpeedHighway/", "CranePlatform");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();

	extern std::list<Entity*> gameEntitiesToAdd;

	for (auto e : gameEntitiesToAdd)
	{
		if (e->isPoint()) 
		{
			Point* thisPoint = (Point*)e;
			if (thisPoint->getID() == point1ID)
			{
				pointPos1 = thisPoint->getPosition();
			}
			else if(thisPoint->getID() == point2ID)
			{
				pointPos2 = thisPoint->getPosition();
			}
		}
	}

	pointDifference = pointPos2 - pointPos1;
	pointLength = pointDifference.length();
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


	if (collideModelTransformed->playerIsOn && canMove && !isMoving && Global::gamePlayer->getY() > position.y - 10) //start moving
	{
		isMoving = true;
		canMove = false;
		cranePlatSource = AudioPlayer::play(22, getPosition());
	}

	if (timeOffset > 1 && isMoving) //stop moving
	{
		isMoving = false;
		if (cranePlatSource != nullptr)
		{
			if (cranePlatSource->isPlaying())
			{
				cranePlatSource->stop();
			}
		}
	}

	if (isMoving)
	{
		oldPos = position;
		position.x = pointPos1.x + (pointDifference.x * fmod(timeOffset, 1));
		position.y = pointPos1.y + (pointDifference.y * fmod(timeOffset, 1));
		position.z = pointPos1.z + (pointDifference.z * fmod(timeOffset, 1));
		//move the player only if the player is standing on the platform
		if (collideModelTransformed->playerIsOn)
		{
			Global::gamePlayer->setDisplacement(position.x - oldPos.x, position.y - oldPos.y, position.z - oldPos.z);
		}
		timeOffset += speed / pointLength;
	}

	if (cranePlatSource != nullptr)
	{
		if (!cranePlatSource->isPlaying() && isMoving && !canMove)
		{
			cranePlatSource = AudioPlayer::play(22, getPosition());
		}
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

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/SpeedHighway/", "CranePlatform.obj");
	for (auto newModel : (*newModels))
	{
		SH_CranePlatform::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (SH_CranePlatform::cmOriginal == nullptr)
	{
		SH_CranePlatform::cmOriginal = loadCollisionModel("Models/SpeedHighway/", "CranePlatform");
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
=======
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
#include "../../audio/audioplayer.h"
#include "../../audio/source.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> SH_CranePlatform::models;
CollisionModel* SH_CranePlatform::cmOriginal;

SH_CranePlatform::SH_CranePlatform()
{

}

SH_CranePlatform::SH_CranePlatform(float x, float y, float z, float rotY, float speed, int point1ID, int point2ID)
{
	position.x = x;
	position.y = y;
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
	collideModelTransformed = loadCollisionModel("Models/SpeedHighway/", "CranePlatform");
	collideModelTransformed2 = loadCollisionModel("Models/SpeedHighway/", "CranePlatform");

	CollisionChecker::addCollideModel(collideModelTransformed);
	CollisionChecker::addCollideModel(collideModelTransformed2);

	updateCollisionModel();

	extern std::list<Entity*> gameEntitiesToAdd;

	for (auto e : gameEntitiesToAdd)
	{
		if (e->isPoint()) 
		{
			Point* thisPoint = (Point*)e;
			if (thisPoint->getID() == point1ID)
			{
				pointPos1 = thisPoint->getPosition();
			}
			else if(thisPoint->getID() == point2ID)
			{
				pointPos2 = thisPoint->getPosition();
			}
		}
	}

	moveDir = pointPos2 - pointPos1;
	moveDir.scale(0.01f);
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
	if (collideModelTransformed2->playerIsOn)
	{
		float dx = moveDir.x;
		float dy = moveDir.y;
		float dz = moveDir.z;
		Global::gamePlayer->increasePosition(dx, dy, dz);
	}
	updateCMJustPosition(collideModelTransformed2);

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

	if (collideModelTransformed->playerIsOn && canMove && !isMoving) //start moving
	{
		isMoving = true;
		canMove = false;
	}

	if (!(position.x * point2GreaterX >= pointPos2.x * point2GreaterX &&
		  position.y * point2GreaterY >= pointPos2.y * point2GreaterY &&
		  position.z * point2GreaterZ >= pointPos2.z * point2GreaterZ) && isMoving == true) //stop moving
	{
		isMoving = false;
	}

	if (isMoving)
	{
		newPos = position + moveDir;
		position = newPos;
		//move the player only if the player is standing on the platform
		if (collideModelTransformed->playerIsOn)
		{
			//Global::gamePlayer->setPosition(Global::gamePlayer->getX() + moveDir.x, Global::gamePlayer->getY() + moveDir.y, Global::gamePlayer->getZ() + moveDir.z);
			Global::gamePlayer->setDisplacement(moveDir.x, moveDir.y, moveDir.z);
		}

		if (cranePlatSource == nullptr)
		{
			cranePlatSource = AudioPlayer::play(22, getPosition(), 1, true);
		}

		if (cranePlatSource != nullptr)
		{
			cranePlatSource->setPosition(getX(), getY(), getZ());
		}
	}
	else
	{
		if (cranePlatSource != nullptr)
		{
			cranePlatSource->stop();
			cranePlatSource = nullptr;
		}
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

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/SpeedHighway/", "CranePlatform.obj");
	for (auto newModel : (*newModels))
	{
		SH_CranePlatform::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (SH_CranePlatform::cmOriginal == nullptr)
	{
		SH_CranePlatform::cmOriginal = loadCollisionModel("Models/SpeedHighway/", "CranePlatform");
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
>>>>>>> upstream/master
