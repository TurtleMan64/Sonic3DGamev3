#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "spring.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/player.h"
#include "../toolbox/maths.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> Spring::models;

Spring::Spring()
{
	this->position.x = 0;
	this->position.y = 0;
	this->position.z = 0;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	this->springRadius = 0;
	this->springPower = 0;
	this->cooldownTimer = 0;
	this->cooldownTimerMax = 0;
	this->scale = 1;
	this->visible = true;
}

Spring::Spring(float x, float y, float z, float rotY, float rotZ, float myPower, int cooldownMax)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->springRadius = 5;
	this->springPower = myPower;
	this->cooldownTimer = 0;
	this->cooldownTimerMax = cooldownMax;
	this->scale = 1;
	this->visible = true;
	updateTransformationMatrix();
}

void Spring::step()
{
	cooldownTimer = std::max(cooldownTimer - 1, 0);

	if (Global::gamePlayer->getX() > getX() - springRadius - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getX() < getX() + springRadius + Global::gamePlayer->getHitboxHorizontal() &&
		Global::gamePlayer->getZ() > getZ() - springRadius - Global::gamePlayer->getHitboxHorizontal() && Global::gamePlayer->getZ() < getZ() + springRadius + Global::gamePlayer->getHitboxHorizontal() &&
		Global::gamePlayer->getY() > getY() - springRadius - Global::gamePlayer->getHitboxVertical() && Global::gamePlayer->getY() < getY() + springRadius)
	{
		if (cooldownTimer == 0)
		{
			float xOff = (float)(cos(toRadians(getRotY()))*cos(toRadians(getRotZ())));
			float zOff = (float)(-sin(toRadians(getRotY()))*cos(toRadians(getRotZ())));
			float yOff = (float)(sin(toRadians(getRotZ())));

			Global::gamePlayer->setX(getX() + xOff * 2);
			Global::gamePlayer->setY(getY() + yOff * 2);
			Global::gamePlayer->setZ(getZ() + zOff * 2);
			Global::gamePlayer->setOnPlane(false);

			Global::gamePlayer->setxVelAir(xOff*springPower);
			Global::gamePlayer->setzVelAir(zOff*springPower);
			Global::gamePlayer->setyVel(yOff*springPower);
			Global::gamePlayer->setxVel(0);
			Global::gamePlayer->setzVel(0);
			Global::gamePlayer->setGroundSpeed(0, 0);
			Global::gamePlayer->setHoverCount(0);

			Global::gamePlayer->setCanMove(false);

			//AudioSources.play(10, getPosition(), 1 + (springPower*0.008f));

			cooldownTimer = cooldownTimerMax;
		}
	}

	if (cooldownTimer == 1)
	{
		Global::gamePlayer->setCanMove(true);
	}
}

float Spring::getSpringPower()
{
	return springPower;
}

std::list<TexturedModel*>* Spring::getModels()
{
	return &Spring::models;
}

void Spring::loadStaticModels()
{
	if (Spring::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading spring static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/Spring/", "Spring.obj");
	for (auto newModel : (*newModels))
	{
		Spring::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void Spring::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting spring static models...\n");
	for (auto model : Spring::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	Spring::models.clear();
}

std::string Spring::getName()
{
	return "spring";
}