#include <glad/glad.h>

#include "entities.h"
#include "../models/models.h"
#include "../toolbox/vector.h"
#include "capsule.h"
#include "../renderEngine/renderEngine.h"
#include "../objLoader/objLoader.h"
#include "../engineTester/main.h"
#include "../entities/playersonic.h"
#include "../toolbox/maths.h"
#include "camera.h"
#include "../collision/collisionmodel.h"
#include "../collision/collisionchecker.h"
#include "../audio/audioplayer.h"
#include "../animation/body.h"
#include "../guis/guimanager.h"
#include "../particles/particleresources.h"
#include "../particles/particle.h"

#include <list>
#include <iostream>
#include <algorithm>
#include <cmath>

std::list<TexturedModel*> Capsule::modelsBase;
std::list<TexturedModel*> Capsule::modelsBaseBroke;
std::list<TexturedModel*> Capsule::modelsTop;
CollisionModel* Capsule::cmOriginalBase;
CollisionModel* Capsule::cmOriginalTop;

Capsule::Capsule()
{

}

Capsule::Capsule(float x, float y, float z)
{
	if (Global::gameIsChaoMode || Global::gameIsRingMode)
	{
		Main_deleteEntity(this);
		return;
	}

	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = true;
	opened = false;
	openedTimer = 0;
	updateTransformationMatrix();
	
	top = new Body(&Capsule::modelsTop);
	top->setVisible(true);
	INCR_NEW
	Main_addEntity(top);
	top->setPosition(&position);
	top->updateTransformationMatrix();

	collideModelOriginal = Capsule::cmOriginalBase;
	collideModelTransformed = loadCollisionModel("Models/Capsule/", "CollisionBase");
	collideModelTopTransformed = loadCollisionModel("Models/Capsule/", "CollisionTop");

	CollisionChecker::addCollideModel(collideModelTransformed);
	CollisionChecker::addCollideModel(collideModelTopTransformed);

	updateCMJustPosition();
	updateCMJustPosition(Capsule::cmOriginalTop, collideModelTopTransformed);
}

void Capsule::step()
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

			if (opened)
			{
				openedTimer++;
			}

			if (openedTimer == 80)
			{
				Global::finishStageTimer = 0;
			}

			if (collideModelTopTransformed->playerIsOn)
			{
				Global::gamePlayer->setGroundSpeed(0, 0);
				Global::gamePlayer->setCanMoveTimer(80);

				if (!opened)
				{
					opened = true;
				
					top->increasePosition(0, -4, 0);
					top->updateTransformationMatrix();
					increasePosition(0, -4, 0);
					updateCMJustPosition(Capsule::cmOriginalTop, collideModelTopTransformed);

					AudioPlayer::play(26, getPosition());
					GuiManager::stopTimer();

					Vector3f pos(
						getX(),
						getY() + 20,
						getZ());

					Vector3f vel(0, 0, 0);
	
					new Particle(ParticleResources::textureExplosion2, &pos, &vel,
						0, 80, 0, 40, 0, false);
				}
			}
		}
	}
}

std::list<TexturedModel*>* Capsule::getModels()
{
	if (opened)
	{
		return &Capsule::modelsBaseBroke;
	}
	return &Capsule::modelsBase;
}

void Capsule::loadStaticModels()
{
	if (Capsule::modelsBase.size() > 0)
	{
		return;
	}

	#ifdef DEV_MODE
	std::fprintf(stdout, "Loading Capsule static models...\n");
	#endif

	loadObjModel(&Capsule::modelsBase,      "res/Models/Capsule/", "CapsuleBottom.obj");
	loadObjModel(&Capsule::modelsBaseBroke, "res/Models/Capsule/", "CapsuleBroke.obj");
	loadObjModel(&Capsule::modelsTop,       "res/Models/Capsule/", "CapsuleTop.obj");

	if (Capsule::cmOriginalBase == nullptr)
	{
		Capsule::cmOriginalBase = loadCollisionModel("Models/Capsule/", "CollisionBase");
	}
	
	if (Capsule::cmOriginalTop == nullptr)
	{
		Capsule::cmOriginalTop = loadCollisionModel("Models/Capsule/", "CollisionTop");
	}
}

void Capsule::deleteStaticModels()
{
	#ifdef DEV_MODE
	std::fprintf(stdout, "Deleting Capsule static models...\n");
	#endif

	Entity::deleteModels(&Capsule::modelsBase);
	Entity::deleteModels(&Capsule::modelsBaseBroke);
	Entity::deleteModels(&Capsule::modelsTop);
	Entity::deleteCollisionModel(&Capsule::cmOriginalBase);
	Entity::deleteCollisionModel(&Capsule::cmOriginalTop);
}
