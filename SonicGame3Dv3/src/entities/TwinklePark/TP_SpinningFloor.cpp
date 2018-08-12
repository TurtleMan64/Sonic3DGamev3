#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "tpspinningfloor.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../entities/playersonic.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> TP_SpinningFloor::models;
CollisionModel* TP_SpinningFloor::cmOriginal;

TP_SpinningFloor::TP_SpinningFloor()
{
	
}

TP_SpinningFloor::TP_SpinningFloor(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = false;
	updateTransformationMatrix();

	collideModelOriginal = TP_SpinningFloor::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/TwinklePark/", "SpinningFloor");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void TP_SpinningFloor::step()
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

			float turnRate = 1.0f;
			float turnRateRad = -toRadians(turnRate);
			increaseRotation(0, turnRate, 0);

			if (collideModelTransformed->playerIsOn)
			{
				float dx = Global::gamePlayer->getX() - getX();
				float dz = Global::gamePlayer->getZ() - getZ();

				float newX =  dx*cosf(turnRateRad) - dz*sinf(turnRateRad);
				float newZ =  dz*cosf(turnRateRad) + dx*sinf(turnRateRad);

				float offX = newX - dx;
				float offZ = newZ - dz;

				//Global::gamePlayer->setX(Global::gamePlayer->getX() + offX);
				//Global::gamePlayer->setZ(Global::gamePlayer->getZ() + offZ);

				Global::gamePlayer->setDisplacement(offX, 0, offZ);
			}

			//updateCollisionModel();
			updateTransformationMatrix();
		}
	}
}

std::list<TexturedModel*>* TP_SpinningFloor::getModels()
{
	return &TP_SpinningFloor::models;
}

void TP_SpinningFloor::loadStaticModels()
{
	if (TP_SpinningFloor::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading TP_SpinningFloor static models...\n");
	#endif

	loadObjModel(&TP_SpinningFloor::models, "res/Models/TwinklePark/", "SpinningFloor.obj");

	if (TP_SpinningFloor::cmOriginal == nullptr)
	{
		TP_SpinningFloor::cmOriginal = loadCollisionModel("Models/TwinklePark/", "SpinningFloor");
	}
}

void TP_SpinningFloor::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting TP_SpinningFloor static models...\n");
	#endif

	Entity::deleteModels(&TP_SpinningFloor::models);
	Entity::deleteCollisionModel(&TP_SpinningFloor::cmOriginal);
}
