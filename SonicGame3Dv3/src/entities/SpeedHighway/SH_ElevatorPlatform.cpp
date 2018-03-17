#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "shelevatorplatform.h"
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

std::list<TexturedModel*> SH_ElevatorPlatform::models;
CollisionModel* SH_ElevatorPlatform::cmOriginal;

SH_ElevatorPlatform::SH_ElevatorPlatform()
{

}

SH_ElevatorPlatform::SH_ElevatorPlatform(float x, float y, float z, float rotY, float speed, int point1ID, int point2ID, int point3ID, int point4ID)
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

	pointIDs[0] = point1ID;
	pointIDs[1] = point2ID;
	pointIDs[2] = point3ID;
	pointIDs[3] = point4ID;

	currentState = 0;

	for (int i = 0; i < 4; i++)
	{
		pointGreaterPos[i].x = 1; //used for keeping track of if the initial position is greater than or less than the final position on that axis
		pointGreaterPos[i].y = 1;
		pointGreaterPos[i].z = 1;
	}

	collideModelOriginal = SH_ElevatorPlatform::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/SpeedHighway/", "ElevatorPlatform");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();

	extern std::list<Entity*> gameEntitiesToAdd;

	for (auto e : gameEntitiesToAdd)
	{
		if (e->isPoint()) 
		{
			Point* thisPoint = (Point*)e;
			for (int i = 0; i < 4; i++)
			{
				if (thisPoint->getID() == pointIDs[i])
				{
					pointPos[i] = thisPoint->getPosition();
					break;
				}
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		moveDir[i] = pointPos[i] - pointPos[(i + 1) % 4]; //% 4 is to prevent index going out of bounds
		moveDir[i].scale(0.01f);
		moveDir[i].x = moveDir[i].x / speed;
		moveDir[i].y = moveDir[i].y / speed;
		moveDir[i].z = moveDir[i].z / speed;
	}

	for (int i = 0; i < 4; i++)
	{
		if (pointPos[(i - 1 + 4) % 4].x > pointPos[i].x)
		{
			pointGreaterPos[i].x = -1; //comparisons are flipped for negatives, -2 < -1, but 1 < 2
		}
		if (pointPos[(i - 1 + 4) % 4].y > pointPos[i].y)
		{
			pointGreaterPos[i].y = -1;
		}
		if (pointPos[(i - 1 + 4) % 4].z > pointPos[i].z)
		{
			pointGreaterPos[i].z = -1;
		}
	}
}

void SH_ElevatorPlatform::step()
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

	if ((position.x * pointGreaterPos[currentState].x >= pointPos[currentState].x * pointGreaterPos[currentState].x &&
		  position.y * pointGreaterPos[currentState].y >= pointPos[currentState].y * pointGreaterPos[currentState].y &&
		  position.z * pointGreaterPos[currentState].z >= pointPos[currentState].z * pointGreaterPos[currentState].z)) //change direction
	{
		position = pointPos[currentState];
		currentState = (currentState + 1) % 4;
	}

	newPos = position + moveDir[(currentState + 1) % 4];
	position = newPos;

	//move the player only if the player is standing on the platform
	if (collideModelTransformed->playerIsOn)
	{
		Global::gamePlayer->setDisplacement(moveDir[(currentState + 1) % 4].x, moveDir[(currentState + 1) % 4].y, moveDir[(currentState + 1) % 4].z);
	}
	
	updateCollisionModel();
	updateTransformationMatrix();
}

std::list<TexturedModel*>* SH_ElevatorPlatform::getModels()
{
	return &SH_ElevatorPlatform::models;
}

void SH_ElevatorPlatform::loadStaticModels()
{
	if (SH_ElevatorPlatform::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading SH_ElevatorPlatform static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/SpeedHighway/", "ElevatorPlatform.obj");
	for (auto newModel : (*newModels))
	{
		SH_ElevatorPlatform::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (SH_ElevatorPlatform::cmOriginal == nullptr)
	{
		SH_ElevatorPlatform::cmOriginal = loadCollisionModel("Models/SpeedHighway/", "ElevatorPlatform");
	}
}

void SH_ElevatorPlatform::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting SH_ElevatorPlatform static models...\n");
	for (auto model : SH_ElevatorPlatform::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	SH_ElevatorPlatform::models.clear();

	if (SH_ElevatorPlatform::cmOriginal != nullptr)
	{
		SH_ElevatorPlatform::cmOriginal->deleteMe();
		delete SH_ElevatorPlatform::cmOriginal;
		Global::countDelete++;
		SH_ElevatorPlatform::cmOriginal = nullptr;
	}
}
