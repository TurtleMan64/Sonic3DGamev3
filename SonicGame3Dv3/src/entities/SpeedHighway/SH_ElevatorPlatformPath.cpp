#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "shelevatorplatformpath.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/player.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> SH_ElevatorPlatformPath::models;
CollisionModel* SH_ElevatorPlatformPath::cmOriginal;

SH_ElevatorPlatformPath::SH_ElevatorPlatformPath()
{

}

SH_ElevatorPlatformPath::SH_ElevatorPlatformPath(float x, float y, float z, float rotY)
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

	collideModelOriginal = SH_ElevatorPlatformPath::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/SpeedHighway/", "ElevatorPlatformPath");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void SH_ElevatorPlatformPath::step()
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
}

std::list<TexturedModel*>* SH_ElevatorPlatformPath::getModels()
{
	return &SH_ElevatorPlatformPath::models;
}

void SH_ElevatorPlatformPath::loadStaticModels()
{
	if (SH_ElevatorPlatformPath::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading SH_ElevatorPlatformPath static models...\n");

	std::list<TexturedModel*>* newModels = loadObjModel("res/Models/SpeedHighway/", "ElevatorPlatformPath.obj");
	for (auto newModel : (*newModels))
	{
		SH_ElevatorPlatformPath::models.push_back(newModel);
	}
	delete newModels;
	Global::countDelete++;


	if (SH_ElevatorPlatformPath::cmOriginal == nullptr)
	{
		SH_ElevatorPlatformPath::cmOriginal = loadCollisionModel("Models/SpeedHighway/", "ElevatorPlatformPath");
	}
}

void SH_ElevatorPlatformPath::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting SH_ElevatorPlatformPath static models...\n");
	for (auto model : SH_ElevatorPlatformPath::models)
	{
		model->deleteMe();
		delete model;
		Global::countDelete++;
	}

	SH_ElevatorPlatformPath::models.clear();

	if (SH_ElevatorPlatformPath::cmOriginal != nullptr)
	{
		SH_ElevatorPlatformPath::cmOriginal->deleteMe();
		delete SH_ElevatorPlatformPath::cmOriginal;
		Global::countDelete++;
		SH_ElevatorPlatformPath::cmOriginal = nullptr;
	}
}
