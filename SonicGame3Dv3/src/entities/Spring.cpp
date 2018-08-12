#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "spring.h"
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

std::list<TexturedModel*> Spring::models;

Spring::Spring()
{

}

Spring::Spring(float x, float y, float z, float rotY, float rotZ, float myPower, int cooldownMax)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = rotZ;
	this->springRadius = 7.8f;
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
		Global::gamePlayer->getY() > getY() - springRadius - Global::gamePlayer->getHitboxVertical()   && Global::gamePlayer->getY() < getY() + springRadius)
	{
		if (cooldownTimer == 0)
		{
			float xOff =  cosf(toRadians(getRotY()))*cosf(toRadians(getRotZ()));
			float zOff = -sinf(toRadians(getRotY()))*cosf(toRadians(getRotZ()));
			float yOff =  sinf(toRadians(getRotZ()));

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

			Global::gamePlayer->setCanMoveTimer(cooldownTimerMax);

			AudioPlayer::play(6, getPosition(), 1 + (springPower*0.008f));

			cooldownTimer = cooldownTimerMax;
		}
	}

	increaseRotation(1, 0, 0);
	updateTransformationMatrix();
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

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading spring static models...\n");
	#endif

	loadObjModel(&Spring::models, "res/Models/Spring/", "Spring.obj");
}

void Spring::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting spring static models...\n");
	#endif

	Entity::deleteModels(&Spring::models);
}

std::string Spring::getName()
{
	return "spring";
}

bool Spring::canHomingAttackOn()
{
	return true;
}

Vector3f Spring::getHomingCenter()
{
	return Vector3f(getPosition());
}
