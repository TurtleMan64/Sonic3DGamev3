#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "speedramp.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../toolbox/maths.h"
#include "camera.h"
#include "../collision/collisionmodel.h"
#include "../collision/collisionchecker.h"
#include "../audio/audioplayer.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> SpeedRamp::models;
CollisionModel* SpeedRamp::cmOriginal;

SpeedRamp::SpeedRamp()
{

}

SpeedRamp::SpeedRamp(float x, float y, float z, float rotY, float rotZ, float myPower, int inputLockDuration)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->scale = 1;
	this->visible = true;
	this->power = myPower;
	this->inputLockDuration = inputLockDuration;
	updateTransformationMatrix();

	collideModelOriginal = SpeedRamp::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/SpeedRamp/", "SpeedRamp");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModelWithZ();
}

void SpeedRamp::step()
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

			if (collideModelTransformed->playerIsOn)
			{
				//float dx =  power*cosf(toRadians(getRotY()));
				//float dz = -power*sinf(toRadians(getRotY()));
				//Global::gamePlayer->increaseGroundSpeed(dx, dz);

				Vector3f newSpeeds = spherePositionFromAngles(-toRadians(getRotY()), toRadians(getRotZ()+10), power);

				Global::gamePlayer->setOnPlane(false);
				Global::gamePlayer->setOnPlanePrevious(false);
				Global::gamePlayer->increasePosition(0, 4, 0);
				Global::gamePlayer->setxVelAir(newSpeeds.x);
				Global::gamePlayer->setzVelAir(newSpeeds.z);
				Global::gamePlayer->setyVel(newSpeeds.y);
				Global::gamePlayer->setxVel(0);
				Global::gamePlayer->setzVel(0);
				Global::gamePlayer->setCanMoveTimer(inputLockDuration);
				Global::gamePlayer->setGroundSpeed(0, 0);

				AudioPlayer::play(21, getPosition());
			}
		}
	}
}

std::list<TexturedModel*>* SpeedRamp::getModels()
{
	return &SpeedRamp::models;
}

void SpeedRamp::loadStaticModels()
{
	if (SpeedRamp::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading SpeedRamp static models...\n");
	#endif

	loadObjModel(&SpeedRamp::models, "res/Models/SpeedRamp/", "SpeedRamp.obj");

	if (SpeedRamp::cmOriginal == nullptr)
	{
		SpeedRamp::cmOriginal = loadCollisionModel("Models/SpeedRamp/", "SpeedRamp");
	}
}

void SpeedRamp::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting SpeedRamp static models...\n");
	#endif

	Entity::deleteModels(&SpeedRamp::models);
	Entity::deleteCollisionModel(&SpeedRamp::cmOriginal);
}
