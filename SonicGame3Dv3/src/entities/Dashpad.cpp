#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "dashpad.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../toolbox/maths.h"
#include "../audio/audioplayer.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> Dashpad::models;

Dashpad::Dashpad()
{

}

Dashpad::Dashpad(float x, float y, float z, float rotX, float rotY, float rotZ, float myPower, float myCamYawTarget, int time)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = rotX;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->hitRadius = 6.5f;
	this->power = myPower;
	this->cooldownTimer = 0;
	this->cooldownTimerMax = time;
	this->scale = 1;
	this->visible = true;
	this->camYawTarget = myCamYawTarget;
	updateTransformationMatrixSADX();
}

void Dashpad::step()
{
	cooldownTimer = std::max(cooldownTimer - 1, 0);

	if (Global::gamePlayer->getX() > getX() - hitRadius - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getX() < getX() + hitRadius + Global::gamePlayer->getHitboxHorizontal() &&
		Global::gamePlayer->getZ() > getZ() - hitRadius - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getZ() < getZ() + hitRadius + Global::gamePlayer->getHitboxHorizontal() &&
		Global::gamePlayer->getY() > getY() - hitRadius - Global::gamePlayer->getHitboxVertical()   && Global::gamePlayer->getY() < getY() + hitRadius)
	{
		if (cooldownTimer == 0 && Global::gamePlayer->isOnGround())
		{
			float dx =  cosf(toRadians(getRotY()));
			float dz = -sinf(toRadians(getRotY()));

			float spindashPower = 0;

			Global::gamePlayer->setX(getX());
			Global::gamePlayer->setY(getY());
			Global::gamePlayer->setZ(getZ());

			Global::gamePlayer->setyVel(0);
			Global::gamePlayer->setxVel(0);
			Global::gamePlayer->setzVel(0);
			Global::gamePlayer->setHoverCount(0);
			Global::gamePlayer->setCameraTargetYaw(-(camYawTarget)+90);

			AudioPlayer::play(1, getPosition());

			cooldownTimer = cooldownTimerMax;

			Global::gamePlayer->setCanMoveTimer(cooldownTimerMax);

			if (Global::gamePlayer->isChargingSpindash())
			{
				spindashPower = Global::gamePlayer->calculateSpindashSpeed(Global::gamePlayer->getSpindashTimer());
				Global::gamePlayer->setIsBall(true);
				Global::gamePlayer->setSpindashTimer(0);

				//TODO: get stored spindash speed and set if < that?
			}

			Global::gamePlayer->setxVelAir(dx*power + dx*spindashPower);
			Global::gamePlayer->setzVelAir(dz*power + dz*spindashPower);
			Global::gamePlayer->setGroundSpeed(dx*power + dx*spindashPower, dz*power + dz*spindashPower);
		}
	}
}

std::list<TexturedModel*>* Dashpad::getModels()
{
	return &Dashpad::models;
}

void Dashpad::loadStaticModels()
{
	if (Dashpad::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading Dashpad static models...\n");
	#endif

	loadObjModel(&Dashpad::models, "res/Models/Dashpad/", "Dashpad.obj");
}

void Dashpad::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting Dashpad static models...\n");
	#endif

	Entity::deleteModels(&Dashpad::models);
}
