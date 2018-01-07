#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "speedramp.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/player.h"
#include "../toolbox/maths.h"
#include "camera.h"
#include "../collision/collisionmodel.h"
#include "../collision/collisionchecker.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> SpeedRamp::models;
CollisionModel* SpeedRamp::cmOriginal;

SpeedRamp::SpeedRamp()
{

}

SpeedRamp::SpeedRamp(float x, float y, float z, float rotY, float rotZ, float myPower)
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
				float dx = (float)(power*cos(toRadians(getRotY())));
				float dz = (float)(-power*sin(toRadians(getRotY())));
				Global::gamePlayer->increaseGroundSpeed(dx, dz);
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

	std::fprintf(stdout, "Loading SpeedRamp static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/SpeedRamp/", "SpeedRamp.obj");
	for (auto newModel : (*newModels))
	{
		SpeedRamp::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (SpeedRamp::cmOriginal == nullptr)
	{
		SpeedRamp::cmOriginal = loadCollisionModel("Models/SpeedRamp/", "SpeedRamp");
	}
}

void SpeedRamp::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting SpeedRamp static models...\n");
	for (auto model : SpeedRamp::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	SpeedRamp::models.clear();

	if (SpeedRamp::cmOriginal != nullptr)
	{
		SpeedRamp::cmOriginal->deleteMe();
		delete SpeedRamp::cmOriginal;
		SpeedRamp::cmOriginal = nullptr;
	}
}
