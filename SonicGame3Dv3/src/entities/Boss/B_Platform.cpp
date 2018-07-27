#include <glad/glad.h>

#include "../entities.h"
#include "../../models/models.h"
#include "../../toolbox/vector.h"
#include "bplatform.h"
#include "../../renderEngine/renderEngine.h"
#include "../../objLoader/objLoader.h"
#include "../../engineTester/main.h"
#include "../../toolbox/maths.h"
#include "../camera.h"
#include "../../collision/collisionmodel.h"
#include "../../collision/collisionchecker.h"
#include "../../audio/audioplayer.h"
#include "../controllableplayer.h"

#include <list>
#include <iostream>

std::list<TexturedModel*> B_Platform::models;
CollisionModel* B_Platform::cmOriginal;

B_Platform::B_Platform()
{
	
}

B_Platform::B_Platform(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	scale = 1;
	visible = true;
	timer = timerMax;
	updateTransformationMatrix();

	collideModelOriginal = B_Platform::cmOriginal;
	collideModelTransformed = loadCollisionModel("Models/Boss/", "Collision");

	CollisionChecker::addCollideModel(collideModelTransformed);

	updateCMJustPosition();
}

void B_Platform::step()
{
	if (Global::gamePlayer->getX()-1500 > getX())
	{
		CollisionChecker::deleteCollideModel(collideModelTransformed);
		Main_deleteEntity(this);
		return;
	}

	if (collideModelTransformed->playerIsOn && timer == timerMax)
	{
		timer = timerMax-1;
	}
				
	if (timer < timerMax)
	{
		timer--;
	}
				
	if (timer == 0)
	{
		AudioPlayer::play(0, getPosition());
	}
				
	if (timer < 0)
	{
		increasePosition(0, -0.25f, 0);
		updateCMJustPosition();
		updateTransformationMatrix();
	}
}

std::list<TexturedModel*>* B_Platform::getModels()
{
	return &B_Platform::models;
}

void B_Platform::loadStaticModels()
{
	if (B_Platform::models.size() > 0)
	{
		return;
	}

	std::fprintf(stdout, "Loading B_Platform static models...\n");

	loadObjModel(&B_Platform::models, "res/Models/Boss/", "Platform.obj");

	if (B_Platform::cmOriginal == nullptr)
	{
		B_Platform::cmOriginal = loadCollisionModel("Models/Boss/", "Collision");
	}
}

void B_Platform::deleteStaticModels()
{
	std::fprintf(stdout, "Deleting B_Platform static models...\n");

	Entity::deleteModels(&B_Platform::models);
	Entity::deleteCollisionModel(&B_Platform::cmOriginal);
}
