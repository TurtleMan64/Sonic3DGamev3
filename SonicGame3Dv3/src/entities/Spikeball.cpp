#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "spikeball.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../toolbox/maths.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> Spikeball::models;

Spikeball::Spikeball()
{

}

Spikeball::Spikeball(float x, float y, float z, float radius, float angVel)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->centerX = x;
	this->centerY = y;
	this->centerZ = z;
	this->rotX = 0;
	this->rotY = 0;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = true;
	this->radius = radius;
	this->angVel = angVel;
	updateTransformationMatrix();
}

void Spikeball::step()
{
	increaseRotation(0, angVel, 0);

	setX(centerX + radius*cosf(toRadians(getRotY())));
	setZ(centerZ - radius*sinf(toRadians(getRotY())));

	float xDiff = Global::gamePlayer->getX() - getX();
	float yDiff = Global::gamePlayer->getY() + (Global::gamePlayer->getHitboxVertical() * 0.25f) - getY();
	float zDiff = Global::gamePlayer->getZ() - getZ();

	float diffRadSquared = Global::gamePlayer->getHitboxHorizontal() + 10.0f;
	diffRadSquared = diffRadSquared*diffRadSquared;

	if (xDiff*xDiff + yDiff*yDiff + zDiff*zDiff < diffRadSquared)
	{
		Global::gamePlayer->takeDamage(getPosition());
	}
	else
	{
		xDiff = Global::gamePlayer->getX() - getX();
		yDiff = Global::gamePlayer->getY() + (Global::gamePlayer->getHitboxVertical() * 0.75f) - getY();
		zDiff = Global::gamePlayer->getZ() - getZ();

		if (xDiff*xDiff + yDiff*yDiff + zDiff*zDiff < diffRadSquared)
		{
			Global::gamePlayer->takeDamage(getPosition());
		}
	}

	updateTransformationMatrix();
}


std::list<TexturedModel*>* Spikeball::getModels()
{
	return &Spikeball::models;
}

void Spikeball::loadStaticModels()
{
	if (Spikeball::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading Spikeball static models...\n");
	#endif

	loadObjModel(&Spikeball::models, "res/Models/Spikeball/", "Spikeball.obj");
}

void Spikeball::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting Spikeball static models...\n");
	#endif

	Entity::deleteModels(&Spikeball::models);
}
