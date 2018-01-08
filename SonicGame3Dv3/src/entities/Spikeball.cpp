#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "spikeball.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/player.h"
#include "../toolbox/maths.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> Spikeball::models;


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
	float yDiff = Global::gamePlayer->getY()+2 - getY();
	float zDiff = Global::gamePlayer->getZ() - getZ();

	if (sqrt(xDiff*xDiff+yDiff*yDiff+zDiff*zDiff) < 12)
	{
		Global::gamePlayer->takeDamage(getPosition());
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

	std::fprintf(stdout, "Loading Spikeball static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/Spikeball/", "Spikeball.obj");
	for (auto newModel : (*newModels))
	{
		Spikeball::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;
}

void Spikeball::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting Spikeball static models...\n");
	for (auto model : Spikeball::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	Spikeball::models.clear();
}
