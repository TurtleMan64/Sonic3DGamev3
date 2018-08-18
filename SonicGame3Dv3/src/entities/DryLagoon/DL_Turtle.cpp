#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "dlturtle.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"
#include "../controllableplayer.h"
#include "../../particles/particle.h"
#include "../../particles/particleresources.h"
#include "../../toolbox/input.h"

#include <list>
#include <iostream>
#include <algorithm>

std::list<TexturedModel*> DL_Turtle::models;
CollisionModel* DL_Turtle::cmOriginal;

extern InputStruct Inputs;

DL_Turtle::DL_Turtle()
{
	
}

DL_Turtle::DL_Turtle(float x, float y, float z, float rotY, 
			  float xt, float yt, float zt, float camYt)
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

	this->xt = xt;
	this->yt = yt;
	this->zt = zt;
	this->camYt = camYt;
	warpTimer = 0;

	collideModelOriginal = DL_Turtle::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/DryLagoon/Objects/", "TurtleCollision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCollisionModel();
}

void DL_Turtle::step()
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
				if (Global::gamePlayer->getY() >= position.y)
				{
					if ((Inputs.INPUT_ACTION  && !Inputs.INPUT_PREVIOUS_ACTION) ||
						(Inputs.INPUT_ACTION2 && !Inputs.INPUT_PREVIOUS_ACTION2))
					{
						warpTimer = warpTimerMax;
						Global::gamePlayer->setCanMoveTimer(warpTimerMax*2+10);

						Vector3f partVel(0, 0, 0);
						new Particle(ParticleResources::textureBlackFadeOutAndIn, Global::gameCamera->getFadePosition1(), &partVel, 0, warpTimerMax*2+10, 0, 400, 0, true);
					}
				}
			}
		}
	}

	if (warpTimer > 0)
	{
		warpTimer--;
		Global::gamePlayer->stopMoving();
		Global::gamePlayer->setPosition(getPosition());
		Global::gamePlayer->increasePosition(0, 5, 0);

		if (warpTimer == 0)
		{
			Global::gamePlayer->setPosition(xt, yt, zt);
			Global::gamePlayer->setCameraTargetYaw(camYt);
			Global::gamePlayer->setCameraTargetPitch(10);
		}
	}
}

std::list<TexturedModel*>* DL_Turtle::getModels()
{
	return &DL_Turtle::models;
}

void DL_Turtle::loadStaticModels()
{
	if (DL_Turtle::models.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading DL_Turtle static models...\n");
	#endif

	loadObjModel(&DL_Turtle::models, "res/Models/DryLagoon/Objects/", "Turtle.obj");

	if (DL_Turtle::cmOriginal == nullptr)
	{
		DL_Turtle::cmOriginal = loadCollisionModel("Models/DryLagoon/Objects/", "TurtleCollision");
	}
}

void DL_Turtle::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting DL_Turtle static models...\n");
	#endif

	Entity::deleteModels(&DL_Turtle::models);
	Entity::deleteCollisionModel(&DL_Turtle::cmOriginal);
}
