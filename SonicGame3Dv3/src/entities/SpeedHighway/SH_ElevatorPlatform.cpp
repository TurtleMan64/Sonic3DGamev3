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
#include "../soundemitter.h"
#include "../../animation/body.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> SH_ElevatorPlatform::modelsPlatform;
std::list<TexturedModel*> SH_ElevatorPlatform::modelsRotate;
CollisionModel* SH_ElevatorPlatform::cmOriginal;

SH_ElevatorPlatform::SH_ElevatorPlatform()
{

}

SH_ElevatorPlatform::SH_ElevatorPlatform(float x, float y, float z, float rotY, float speed, int point1ID, int point2ID, int point3ID, int point4ID, float timeOffset)
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

	this->timeOffset = timeOffset;

	rotate = new Body(&SH_ElevatorPlatform::modelsRotate);
	rotate->setVisible(true);
	Global::countNew++;
	Main_addEntity(rotate);
	rotate->setPosition(&position);

	pointIDs[0] = point1ID;
	pointIDs[1] = point2ID;
	pointIDs[2] = point3ID;
	pointIDs[3] = point4ID;

	collideModelOriginal = SH_ElevatorPlatform::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/SpeedHighway/", "ElevatorPlatform");
	collideModelTransformed2 = loadCollisionModel("Models/SpeedHighway/", "ElevatorPlatform");

	CollisionChecker::addCollideModel(collideModelTransformed);
	CollisionChecker::addCollideModel(collideModelTransformed2);

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
		pointDifferences[i] = pointPos[i] - pointPos[(i + 4 - 1) % 4];
		pointLengths[i] = pointDifferences[i].length();
	}


}

void SH_ElevatorPlatform::step()
{
	//second collision model so that if the player falls through the platform, they land on this, and don't actually fall through
	updateCollisionModel(cmOriginal, collideModelTransformed2);

	if (collideModelTransformed2->playerIsOn)
	{
		Global::gamePlayer->setDisplacement(position.x - oldPos.x, position.y - oldPos.y, position.z - oldPos.z);
	}

	if (abs(getX() - Global::gameCamera->getPosition()->x) > ENTITY_RENDER_DIST)
	{
		setVisible(false);
		rotate->setVisible(false);
	}
	else
	{
		if (abs(getZ() - Global::gameCamera->getPosition()->z) > ENTITY_RENDER_DIST)
		{
			setVisible(false);
			rotate->setVisible(false);
		}
		else
		{
			setVisible(true);
			rotate->setVisible(true);
			rotate->setPosition(&position);
			rotate->increaseRotation(0, 0, -2.5f);
			rotate->updateTransformationMatrix();
		}
	}

	/*  
		idea behind this is that time is incremented based on the length of the current path the platform is traveling on,
		and the position of the platform is the time mulitplied by the length of the path, in other words, the platform is being placed
		exactly where it should be in relation to the points based on the amount of time it should take to travel across the two points
	*/

	timeOffset += speed / pointLengths[(int) timeOffset];
	timeOffset = fmod(timeOffset, 4.0f);
	
	oldPos = position;

	int timeOffsetInt = (int)timeOffset;

	position.x = pointPos[(timeOffsetInt + 4 - 1) % 4].x + (pointDifferences[timeOffsetInt].x * fmod(timeOffset, 1));
	position.y = pointPos[(timeOffsetInt + 4 - 1) % 4].y + (pointDifferences[timeOffsetInt].y * fmod(timeOffset, 1));
	position.z = pointPos[(timeOffsetInt + 4 - 1) % 4].z + (pointDifferences[timeOffsetInt].z * fmod(timeOffset, 1));

	//move the player only if the player is standing on the platform
	if (collideModelTransformed->playerIsOn)
	{
		Global::gamePlayer->setDisplacement(position.x - oldPos.x, position.y - oldPos.y, position.z - oldPos.z);
	}

	updateCollisionModel();
	updateTransformationMatrix();
}

std::list<TexturedModel*>* SH_ElevatorPlatform::getModels()
{
	return &SH_ElevatorPlatform::modelsPlatform;
}

void SH_ElevatorPlatform::loadStaticModels()
{
	if (SH_ElevatorPlatform::modelsPlatform.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading SH_ElevatorPlatform static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/SpeedHighway/", "ElevatorPlatform.obj");
	for (auto newModel : (*newModels))
	{
		SH_ElevatorPlatform::modelsPlatform.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;

	std::list<TexturedModel*>* newModels2 = loadObjModel("res/Models/SpeedHighway/", "ElevatorPlatformRotate.obj");
	for (auto newModel : (*newModels2))
	{
		SH_ElevatorPlatform::modelsRotate.push_back(newModel);
	}
	delete newModels2;
	Global::countDelete++;


	if (SH_ElevatorPlatform::cmOriginal == nullptr)
	{
		SH_ElevatorPlatform::cmOriginal = loadCollisionModel("Models/SpeedHighway/", "ElevatorPlatform");
	}

}

void SH_ElevatorPlatform::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting SH_ElevatorPlatform static models...\n");
	for (auto model : SH_ElevatorPlatform::modelsPlatform)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	SH_ElevatorPlatform::modelsPlatform.clear();

	for (auto model : SH_ElevatorPlatform::modelsRotate)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	SH_ElevatorPlatform::modelsRotate.clear();

	if (SH_ElevatorPlatform::cmOriginal != nullptr)
	{
		SH_ElevatorPlatform::cmOriginal->deleteMe();
		delete SH_ElevatorPlatform::cmOriginal;
		Global::countDelete++;
		SH_ElevatorPlatform::cmOriginal = nullptr;
	}
}
