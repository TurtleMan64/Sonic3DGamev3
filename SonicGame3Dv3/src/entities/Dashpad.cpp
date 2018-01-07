#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "dashpad.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/player.h"
#include "../toolbox/maths.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> Dashpad::models;

Dashpad::Dashpad()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	this->hitRadius = 0;
	this->power = 0;
	this->cooldownTimer = 0;
	this->cooldownTimerMax = 20;
	this->scale = 1;
	this->visible = true;
}

Dashpad::Dashpad(float x, float y, float z, float rotY, float rotZ, float myPower, float myCamYawTarget, int time)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->hitRadius = 5;
	this->power = myPower;
	this->cooldownTimer = 0;
	this->cooldownTimerMax = time;
	this->scale = 1;
	this->visible = true;
	this->camYawTarget = myCamYawTarget;
	updateTransformationMatrix();
}

void Dashpad::step()
{
	cooldownTimer = std::max(cooldownTimer - 1, 0);

	if (Global::gamePlayer->getX() > getX() - hitRadius - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getX() < getX() + hitRadius + Global::gamePlayer->getHitboxHorizontal() &&
		Global::gamePlayer->getZ() > getZ() - hitRadius - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getZ() < getZ() + hitRadius + Global::gamePlayer->getHitboxHorizontal() &&
		Global::gamePlayer->getY() > getY() - hitRadius - Global::gamePlayer->getHitboxVertical() && Global::gamePlayer->getY() < getY() + hitRadius)
	{
		if (cooldownTimer == 0)
		{
			float xOff = (float)(cos(toRadians(getRotY()))*cos(toRadians(getRotZ())));
			float zOff = (float)(-sin(toRadians(getRotY()))*cos(toRadians(getRotZ())));

			Global::gamePlayer->setX(getX());
			Global::gamePlayer->setY(getY());
			Global::gamePlayer->setZ(getZ());

			Global::gamePlayer->setxVelAir(xOff*power);
			Global::gamePlayer->setzVelAir(zOff*power);
			Global::gamePlayer->setyVel(0);
			Global::gamePlayer->setxVel(0);
			Global::gamePlayer->setzVel(0);
			Global::gamePlayer->setGroundSpeed(xOff*power, zOff*power);
			Global::gamePlayer->setHoverCount(0);
			Global::gamePlayer->setCameraTargetYaw(-(camYawTarget)+90);

			//AudioSources.play(12, getPosition());

			cooldownTimer = cooldownTimerMax;

			Global::gamePlayer->setCanMove(false);
		}
	}

	if (cooldownTimer == 1)
	{
		Global::gamePlayer->setCanMove(true);
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

	std::fprintf(stdout, "Loading Dashpad static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/Dashpad/", "Dashpad.obj");
	for (auto newModel : (*newModels))
	{
		Dashpad::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void Dashpad::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting Dashpad static models...\n");
	for (auto model : Dashpad::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	Dashpad::models.clear();
}
