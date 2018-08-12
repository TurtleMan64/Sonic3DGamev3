#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "nbwaterplatformbounce.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../controllableplayer.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"
#include "../../audio/audioplayer.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> NB_WaterPlatformBounce::models;
CollisionModel* NB_WaterPlatformBounce::cmOriginal;

NB_WaterPlatformBounce::NB_WaterPlatformBounce()
{
	
}

NB_WaterPlatformBounce::NB_WaterPlatformBounce(float x, float y, float z, float rotY)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->rotX = 0;
	this->rotY = rotY;
	this->rotZ = 0;
	this->scale = 1;
	this->visible = true;
	updateTransformationMatrix();

	collideModelOriginal = NB_WaterPlatformBounce::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/NokiBay/WaterPlatforms/", "WaterPlatformBounceCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void NB_WaterPlatformBounce::step()
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
				if (Global::gamePlayer->getY() >= getY())
				{
					Global::gamePlayer->increasePosition(0, 1, 0);
					Global::gamePlayer->setOnPlane(false);

					float bounceSpeed = std::fmaxf(9, -Global::gamePlayer->getyVel());
					Global::gamePlayer->setyVel(bounceSpeed);


					Global::gamePlayer->setxVel(0);
					Global::gamePlayer->setzVel(0);
					Global::gamePlayer->setGroundSpeed(0, 0);
					Global::gamePlayer->setHoverCount(0);

					AudioPlayer::play(6, getPosition(), 0.6f);
				}
			}
		}
	}
}

std::list<TexturedModel*>* NB_WaterPlatformBounce::getModels()
{
	return &NB_WaterPlatformBounce::models;
}

void NB_WaterPlatformBounce::loadStaticModels()
{
	if (NB_WaterPlatformBounce::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading NB_WaterPlatformBounce static models...\n");
	#endif

	loadObjModel(&NB_WaterPlatformBounce::models, "res/Models/NokiBay/WaterPlatforms/", "WaterPlatformBounce.obj");

	if (NB_WaterPlatformBounce::cmOriginal == nullptr)
	{
		NB_WaterPlatformBounce::cmOriginal = loadCollisionModel("Models/NokiBay/WaterPlatforms/", "WaterPlatformBounceCollision");
	}
}

void NB_WaterPlatformBounce::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting NB_WaterPlatformBounce static models...\n");
	#endif

	Entity::deleteModels(&NB_WaterPlatformBounce::models);
	Entity::deleteCollisionModel(&NB_WaterPlatformBounce::cmOriginal);
}
